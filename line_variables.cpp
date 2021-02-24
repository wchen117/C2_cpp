//
// Created by wchen on 2/18/21.
//

#include "variables/line_variables.hpp"
LineVariables::LineVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name): VariableSet(-1, name)
{
    local_input_ptr = data_ptr;

    if (!local_input_ptr->E_k0.empty())
    {
        size_E_k0 = local_input_ptr->E_k0.size();
        Ns = local_input_ptr->new_data.sup.scblocks.size();

        s_enk_plus = Eigen::MatrixXd::Zero(Ns, size_E_k0);
        c_n_s = Eigen::MatrixXd::Zero(Ns, size_E_k0);
        t_n_s_over = Eigen::MatrixXd::Zero(Ns, size_E_k0);
        r_e_over_eigen =Eigen::MatrixXd::Zero(Ns, size_E_k0);

        c_e_sw = Eigen::VectorXd::Zero(size_E_k0);
        ref_desbus = Eigen::VectorXd::Zero(size_E_k0);
        ref_oribus = Eigen::VectorXd::Zero(size_E_k0);
        x_ek_sw = Eigen::VectorXd::Zero(size_E_k0);
        x_e_sw0 = Eigen::VectorXd::Zero(size_E_k0);

        size_t var_counter = 0;

        for (size_t idx=0; idx <local_input_ptr->E_k0.size(); idx++)
        {
            int oribus_num;
            int destbus_num;
            std::string bus_i;
            auto e_key= local_input_ptr->E_k0.at(idx);
            std::tie (oribus_num, destbus_num, bus_i) = e_key;
            // there are extra '' around the bus_id string read from E_k0
            bus_i.erase(std::remove(bus_i.begin(), bus_i.end(), '\''), bus_i.end());
            for (auto n: local_input_ptr->new_data.sup.lines)
            {
                if (oribus_num == n.origbus && destbus_num == n.destbus &&  bus_i==n.id)
                {
                    key_iis tmp_e;
                    //reconstruct the key
                    tmp_e = std::make_tuple(n.origbus, n.destbus, n.id);
                    // fetched origbus and desbus are not ordered, use ref_origbus and ref_desbus to help keep track
                    ref_oribus(idx) = n.origbus;
                    ref_desbus(idx) = n.destbus;
                    c_e_sw(idx) = n.csw;

                    for(size_t jdx=0; jdx<Ns; jdx++)
                    {
                        c_n_s(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).c * local_input_ptr->s_tilde;
                        t_n_s_over(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).tmax;
                        r_e_over_eigen(jdx, idx) = local_input_ptr->r_e_ct_over[tmp_e];
                    }

                }
            }

        }
        if (size_E_k0 && Ns)
        {
            line_var_len = size_E_k0 * Ns + size_E_k0;
            SetRows(line_var_len);
        }
        else{
            std::cout<<"null size for size_E_k0 or Ns, quit"<<std::endl;
            exit(0);
        }

    }
    else{
        exit(0);
    }

}

LineVariables::~LineVariables() {}

Eigen::VectorXd LineVariables::GetValues() const
{
    // S_enk_plus, each col: index n in Ns, each row: index e in E_k0

    if(GetRows())
    {

        Eigen::VectorXd tmp_x(GetRows());
        // this flatten s_enk_plus col by col
        // why must declare const here???? it says s_enk_plus a const double*, why?
        Eigen::Map<const Eigen::VectorXd> flat_s_enk(s_enk_plus.data(), s_enk_plus.size());
        tmp_x << flat_s_enk, x_ek_sw;
        assert(tmp_x.size() == GetRows());
        return tmp_x;
    }
    else{
        exit(0);
    }


}
void LineVariables::SetVariables(const Eigen::VectorXd &x)
{
    size_t flat_len = size_E_k0 * Ns;
    auto tmp_flat = x.segment(0, flat_len);
    x_ek_sw = x.segment(flat_len, size_E_k0);
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>> tmp_mat(tmp_flat.data(), Ns, size_E_k0);
    s_enk_plus = tmp_mat;
}

LineVariables::VecBound  LineVariables::GetBounds() const
{

    VecBound line_bounds(GetRows());
    Eigen::VectorXd upper_bound(GetRows());

    // convert to array for in-place multiplication, then convert by to matrix (may not need to )
    Eigen::MatrixXd tmp_prod = (t_n_s_over.array() * r_e_over_eigen.array()).matrix();
    // flat the tmp_prod col wise, same as the s_enk_plus
    Eigen::Map<const Eigen::VectorXd> tmp_flat_prod(tmp_prod.data(), tmp_prod.size());


    Eigen::VectorXd up_bound_1(size_E_k0);
    for (size_t idx=0; idx<size_E_k0; idx++)
    {
        up_bound_1(idx) = 1.0;
    }

    // x_ek_sw  is binary varialble, for now we put them as real number between 0 and 1
    upper_bound << tmp_flat_prod, up_bound_1;
    for (size_t idx=0; idx<GetRows(); idx++)
    {
        line_bounds.at(idx).upper_ = upper_bound(idx);
        line_bounds.at(idx).lower_ = 0.0;

    }


    return line_bounds;


}
