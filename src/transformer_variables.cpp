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
        x_fk_st = Eigen::VectorXd::Zero(size_F_k0);
        x_fk_st_bound = Eigen::VectorXd::Zero(size_F_k0);
        tau_fk = Eigen::VectorXd::Zero(size_F_k0);
        tau_fk_over = Eigen::VectorXd::Zero(size_F_k0);
        tau_fk_under = Eigen::VectorXd::Zero(size_F_k0);
        tau_f_st = Eigen::VectorXd::Zero(size_F_k0);
        tau_f_mid = Eigen::VectorXd::Zero(size_F_k0);

        // zero initialize all parameters for now
        c_n_s = Eigen::MatrixXd::Zero(Ns, size_F_k0);
        t_n_s_over = Eigen::MatrixXd::Zero(Ns, size_F_k0);
        s_f_over_eigen = Eigen::MatrixXd::Zero(Ns, size_F_k0);

        c_f_sw = Eigen::VectorXd::Zero(size_F_k0);
        x_f_sw0 = Eigen::VectorXd::Zero(size_F_k0);
        ref_desbus = Eigen::VectorXd::Zero(size_F_k0);
        ref_oribus = Eigen::VectorXd::Zero(size_F_k0);

        for (size_t idx=0; idx <size_F_k0; idx++)
        {
            int oribus_num;
            int destbus_num;
            std::string bus_i;
            auto f_key= local_input_ptr->F_k0.at(idx);
            std::tie (oribus_num, destbus_num, bus_i) = f_key;

            bus_i.erase(std::remove(bus_i.begin(), bus_i.end(), '\''), bus_i.end());
            for (auto n: local_input_ptr->new_data.sup.transformers)
            {
                if (oribus_num == n.origbus && destbus_num == n.destbus &&  bus_i==n.id)
                {
                    // fetched origbus and desbus are not ordered, use ref_origbus and ref_desbus to help keep track
                    ref_oribus(idx) = n.origbus;
                    ref_desbus(idx) = n.destbus;
                    c_f_sw(idx) = n.csw;
                    x_f_sw0(idx) = local_input_ptr->x_f_sw_0[f_key];
                    // eqn(60)
                    if (n.swqual == 0)
                    {
                        x_fk_sw(idx) = local_input_ptr->x_f_sw_0[f_key];
                    }
                    //eqn(61), record x_f_st_over first
                    x_fk_st_bound(idx) = local_input_ptr->x_f_st_over[f_key];
                    tau_fk_over(idx) = local_input_ptr->tau_f_over[f_key];
                    tau_fk_under(idx) = local_input_ptr->tau_f_under[f_key];
                    tau_f_st(idx) = local_input_ptr->tau_f_st[f_key];
                    tau_f_mid(idx) = local_input_ptr->tau_f_any[f_key];

                    for(size_t jdx=0; jdx<Ns; jdx++)
                    {
                        c_n_s(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).c * local_input_ptr->s_tilde;
                        t_n_s_over(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).tmax;
                        s_f_over_eigen(jdx, idx) = local_input_ptr->s_f_over[f_key];
                    }
                }
            }

        }


        if(size_F_k0 && Ns)
        {
            trans_var_len = size_F_k0 * Ns + 3* size_F_k0;

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
        tmp_x << flat_s_fnk, x_fk_sw, x_fk_st, tau_fk;
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
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>> tmp_mat(tmp_flat.data(), Ns, size_F_k0);
    s_fnk_plus = tmp_mat;
    x_fk_sw = x.segment( flat_len, size_F_k0);
    x_fk_st = x.segment(flat_len + size_F_k0, size_F_k0);
    tau_fk = x.segment(flat_len + 2* size_F_k0, size_F_k0);



}

TransformerVariables::VecBound  TransformerVariables::GetBounds() const
{
    VecBound line_bounds(GetRows());
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());

    Eigen::MatrixXd tmp_prod = (t_n_s_over.array() * s_f_over_eigen.array()).matrix();
    // individual upper bounds
    Eigen::Map<const Eigen::VectorXd> s_fnk_up_bound(tmp_prod.data(), tmp_prod.size());
    Eigen::VectorXd x_fk_sw_up_bound(size_F_k0);
    Eigen::VectorXd x_fk_st_up_bound = x_fk_st_bound;

    // individual lower bounds
    Eigen::VectorXd s_fnk_lo_bound = Eigen::VectorXd::Zero(s_fnk_up_bound.size());
    Eigen::VectorXd x_fk_sw_lo_bound = Eigen::VectorXd::Zero(size_F_k0);
    Eigen::VectorXd x_fk_st_lo_bound = -1 * x_fk_st_bound;


    for (size_t idx=0; idx<size_F_k0; idx++)
    {
        x_fk_sw_up_bound(idx) = 1.0;
    }

    upper_bound << s_fnk_up_bound, x_fk_sw_up_bound, x_fk_st_up_bound, tau_fk_over;
    lower_bound << s_fnk_lo_bound, x_fk_sw_lo_bound, x_fk_st_lo_bound, tau_fk_under;

    for (size_t idx=0; idx<GetRows(); idx++)
    {
        line_bounds.at(idx).upper_ = upper_bound(idx);
        line_bounds.at(idx).lower_ = lower_bound(idx);

    }

    return line_bounds;

}