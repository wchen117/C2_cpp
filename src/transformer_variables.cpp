//
// Created by wchen on 2/24/21.
//

#include "variables/transformer_variables.hpp"

TransformerVariables::TransformerVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name): VariableSet(-1, name)
{

    local_input_ptr = data_ptr;

    if (!local_input_ptr->F_k0.empty())
    {
        size_F_k0 = local_input_ptr->F_k0.size();
        Ns = local_input_ptr->new_data.sup.scblocks.size();
        // zero initialize all variables
        s_fnk_plus = Eigen::MatrixXd::Zero(Ns, size_F_k0);
        x_fk_sw = Eigen::VectorXd::Zero(size_F_k0);

        // zero initialize all parameters for now
        c_n_s = Eigen::MatrixXd::Zero(Ns, size_F_k0);
        t_n_s_over = Eigen::MatrixXd::Zero(Ns, size_F_k0);
        s_f_over_eigen = Eigen::MatrixXd::Zero(Ns, size_F_k0);

        c_f_sw = Eigen::VectorXd::Zero(size_F_k0);
        x_f_sw0 = Eigen::VectorXd::Zero(size_F_k0);
        ref_desbus = Eigen::VectorXd::Zero(size_F_k0);
        ref_oribus = Eigen::VectorXd::Zero(size_F_k0);

        for (size_t idx=0; idx <local_input_ptr->F_k0.size(); idx++)
        {
            int oribus_num;
            int destbus_num;
            std::string bus_i;
            auto e_key= local_input_ptr->F_k0.at(idx);
            std::tie (oribus_num, destbus_num, bus_i) = e_key;

            bus_i.erase(std::remove(bus_i.begin(), bus_i.end(), '\''), bus_i.end());
            for (auto n: local_input_ptr->new_data.sup.transformers)
            {
                if (oribus_num == n.origbus && destbus_num == n.destbus &&  bus_i==n.id)
                {
                    key_iis tmp_f;
                    //reconstruct the key
                    tmp_f = std::make_tuple(n.origbus, n.destbus, n.id);
                    // fetched origbus and desbus are not ordered, use ref_origbus and ref_desbus to help keep track
                    ref_oribus(idx) = n.origbus;
                    ref_desbus(idx) = n.destbus;
                    c_f_sw(idx) = n.csw;
                    x_f_sw0(idx) = local_input_ptr->x_f_sw_0[tmp_f];
                    for(size_t jdx=0; jdx<Ns; jdx++)
                    {
                        c_n_s(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).c * local_input_ptr->s_tilde;
                        t_n_s_over(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).tmax;
                        s_f_over_eigen(jdx, idx) = local_input_ptr->s_f_over[tmp_f];
                    }
                }
            }

        }
        if(size_F_k0 && Ns)
        {
            trans_var_len = size_F_k0 * Ns + size_F_k0;
            SetRows(trans_var_len);
        }

    } else{
        exit(0);
    }


}
TransformerVariables::~TransformerVariables() {}

Eigen::VectorXd TransformerVariables::GetValues() const
{

    if(GetRows())
    {

        Eigen::VectorXd tmp_x(GetRows());
        // this flatten s_enk_plus col by col
        // const is needed here because the current function is read only?
        Eigen::Map<const Eigen::VectorXd> flat_s_fnk(s_fnk_plus.data(), s_fnk_plus.size());
        tmp_x << flat_s_fnk, x_fk_sw;
        assert(tmp_x.size() == GetRows());
        return tmp_x;
    }
    else{
        exit(0);
    }


}
void TransformerVariables::SetVariables(const Eigen::VectorXd &x)
{

    size_t flat_len = size_F_k0 * Ns;
    auto tmp_flat = x.segment(0, flat_len);
    x_fk_sw = x.segment(flat_len, size_F_k0);
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>> tmp_mat(tmp_flat.data(), Ns, size_F_k0);
    s_fnk_plus = tmp_mat;


}

TransformerVariables::VecBound  TransformerVariables::GetBounds() const
{
    VecBound trans_bounds(GetRows());
    return trans_bounds;

}