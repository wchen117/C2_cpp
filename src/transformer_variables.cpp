//
// Created by wchen on 2/24/21.
//

#include "variables/transformer_variables.hpp"

TransformerVariables::TransformerVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::shared_ptr<BusVariables> bus_var_ptr, const std::string& name): VariableSet(-1, name)
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
        tau_f_0 = Eigen::VectorXd::Zero(size_F_k0);

        theta_fk = Eigen::VectorXd::Zero(size_F_k0);
        theta_fk_over = Eigen::VectorXd::Zero(size_F_k0);
        theta_fk_under = Eigen::VectorXd::Zero(size_F_k0);
        theta_f_st = Eigen::VectorXd::Zero(size_F_k0);
        theta_f_mid = Eigen::VectorXd::Zero(size_F_k0);
        theta_f_0 = Eigen::VectorXd::Zero(size_F_k0);

        g_fk = Eigen::VectorXd::Zero(size_F_k0);
        b_fk = Eigen::VectorXd::Zero(size_F_k0);
        eta_fk = Eigen::VectorXd::Zero(size_F_k0);
        g_f_0 = Eigen::VectorXd::Zero(size_F_k0);
        b_f_0 = Eigen::VectorXd::Zero(size_F_k0);

        //variables in eqn(72) - eqn(75)
        p_fk_o = Eigen::VectorXd::Zero(size_F_k0);
        q_fk_o = Eigen::VectorXd::Zero(size_F_k0);
        p_fk_d = Eigen::VectorXd::Zero(size_F_k0);
        q_fk_d = Eigen::VectorXd::Zero(size_F_k0);

        // coefficients in eqn(77) and eqn(78)
        s_f_over = Eigen::VectorXd::Zero(size_F_k0);

        // zero initialize all parameters for now
        c_n_s = Eigen::MatrixXd::Zero(Ns, size_F_k0);
        t_n_s_over = Eigen::MatrixXd::Zero(Ns, size_F_k0);
        s_f_over_eigen = Eigen::MatrixXd::Zero(Ns, size_F_k0);

        c_f_sw = Eigen::VectorXd::Zero(size_F_k0);
        x_f_sw0 = Eigen::VectorXd::Zero(size_F_k0);
        ref_desbus = Eigen::VectorXd::Zero(size_F_k0);
        ref_oribus = Eigen::VectorXd::Zero(size_F_k0);

        // F_k0 or F_k is an vector (ordered), so we bound to have orders in all
        // Eigen::VectorXd read this way
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
                    //eqn(61) - eqn(63), record x_f_st_over first
                    x_fk_st_bound(idx) = local_input_ptr->x_f_st_over[f_key];
                    tau_fk_over(idx) = local_input_ptr->tau_f_over[f_key];
                    tau_fk_under(idx) = local_input_ptr->tau_f_under[f_key];
                    tau_f_st(idx) = local_input_ptr->tau_f_st[f_key];
                    tau_f_mid(idx) = local_input_ptr->tau_f_any[f_key];
                    tau_f_0(idx) =  local_input_ptr->tau_f_0[f_key];

                    //eqn(64) - eqn(65)
                    theta_fk_over(idx) = local_input_ptr->theta_f_over[f_key];
                    theta_fk_under(idx) = local_input_ptr->theta_f_under[f_key];
                    theta_f_st(idx) = local_input_ptr->theta_f_st[f_key];
                    theta_f_mid(idx) = local_input_ptr->theta_f_any[f_key];
                    theta_f_0(idx) = local_input_ptr->theta_f_0[f_key];

                    //eqn(66) - eqn(68)
                    b_f_0(idx) = local_input_ptr->b_f_0[f_key];
                    g_f_0(idx) = local_input_ptr->g_f_0[f_key];

                    //eqn(77) and eqn(78)
                    s_f_over(idx) = local_input_ptr->s_f_over[f_key];

                    for(size_t jdx=0; jdx<Ns; jdx++)
                    {
                        c_n_s(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).c * local_input_ptr->s_tilde;
                        t_n_s_over(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).tmax;
                        s_f_over_eigen(jdx, idx) = local_input_ptr->s_f_over[f_key];
                    }
                }
            }

        }

        // to formulate  p_fk_o, q_fk_o, p_fk_d, q_fk_d
        for (size_t fkdx=0; fkdx<local_input_ptr->F_k0.size(); fkdx++)
        {
            auto fk = local_input_ptr->F_k0.at(fkdx);
            auto idx = local_input_ptr->i_f_o.at(fk);
            auto ipdx = local_input_ptr->i_f_d.at(fk);
            auto g_f_m = local_input_ptr->g_f_m.at(fk);
            auto b_f_m = local_input_ptr->b_f_m.at(fk);
            // findInVector located in typedefinition.hpp
            auto bus_idx_pair = findInVector(bus_var_ptr->sorted_bus_ID, idx);
            auto bus_ipdx_pair = findInVector(bus_var_ptr->sorted_bus_ID, ipdx);
            auto diff = local_input_ptr->theta_0.at(idx) - local_input_ptr->theta_0.at(ipdx) - theta_fk(fkdx);
            // can't use tmp_x_fk_sw to change x_fk_sw(fkdx)
            const auto &tmp_x_fk_sw = x_fk_sw(fkdx);
            const auto &tmp_g_fk = g_fk(fkdx);
            const auto &tmp_b_fk = b_fk(fkdx);
            const auto &tmp_theta_fk = theta_fk(fkdx);
            const auto &tmp_tau_fk = tau_fk(fkdx);
            if (bus_idx_pair.first && bus_ipdx_pair.first)
            {
                auto bus_idx = bus_idx_pair.second;
                auto bus_ipdx = bus_ipdx_pair.second;
                auto vik = bus_var_ptr->v_ik(bus_idx);
                auto vipk = bus_var_ptr->v_ik(bus_ipdx);
                // eqn(72) - eqn(75)
                auto tmp_p_fk_o = tmp_x_fk_sw * ((tmp_g_fk/tmp_tau_fk/tmp_tau_fk + g_f_m) * vik * vik - (tmp_g_fk * cos(diff) + tmp_b_fk*sin(diff)) * vik * vipk / tmp_tau_fk);
                auto tmp_q_fk_o = tmp_x_fk_sw * (-(tmp_b_fk/tmp_tau_fk/tmp_tau_fk + b_f_m)* vik * vik - (tmp_b_fk * cos(diff) - tmp_g_fk*sin(diff)) * vik * vipk / tmp_tau_fk);
                auto tmp_p_fk_d = tmp_x_fk_sw * (tmp_g_fk * vipk * vipk - (tmp_g_fk * cos(-diff) + tmp_b_fk * sin(-diff)) * vik * vipk / tmp_tau_fk);
                auto tmp_q_fk_d = tmp_x_fk_sw * (-tmp_b_fk * vipk * vipk + (tmp_b_fk * cos(-diff) - tmp_g_fk * sin(-diff)) * vik * vipk / tmp_tau_fk);
                p_fk_o(fkdx) = tmp_p_fk_o;
                q_fk_o(fkdx) = tmp_q_fk_o;
                p_fk_d(fkdx) = tmp_p_fk_d;
                q_fk_d(fkdx) = tmp_q_fk_d;
            }

        }


        if(size_F_k0 && Ns)
        {
            trans_var_len = size_F_k0 * Ns + 11 * size_F_k0;

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

        tmp_x << flat_s_fnk, x_fk_sw, x_fk_st, tau_fk, theta_fk, b_fk, g_fk, eta_fk, p_fk_o, q_fk_o, p_fk_d, q_fk_d;
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
    tau_fk = x.segment(flat_len + 2 * size_F_k0, size_F_k0);
    theta_fk = x.segment(flat_len + 3 * size_F_k0, size_F_k0);
    b_fk = x.segment(flat_len + 4 * size_F_k0, size_F_k0);
    g_fk = x.segment(flat_len + 5 * size_F_k0, size_F_k0);
    eta_fk =  x.segment(flat_len + 6 * size_F_k0, size_F_k0);
    p_fk_o = x.segment(flat_len + 7 * size_F_k0, size_F_k0);
    q_fk_o = x.segment(flat_len + 8 * size_F_k0, size_F_k0);
    p_fk_d = x.segment(flat_len + 9 * size_F_k0, size_F_k0);
    q_fk_d = x.segment(flat_len + 10 * size_F_k0, size_F_k0);



}

TransformerVariables::VecBound  TransformerVariables::GetBounds() const
{
    VecBound line_bounds(GetRows());
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());

    Eigen::MatrixXd tmp_prod = (t_n_s_over.array() * s_f_over_eigen.array()).matrix();
    // individual upper bounds
    Eigen::Map<const Eigen::VectorXd> s_fnk_up_bound(tmp_prod.data(), tmp_prod.size());
    Eigen::VectorXd x_fk_sw_up_bound = Eigen::VectorXd::Zero(size_F_k0);
    Eigen::VectorXd x_fk_st_up_bound = x_fk_st_bound;
    Eigen::VectorXd b_fk_up_bound = Eigen::VectorXd::Zero(size_F_k0);
    Eigen::VectorXd g_fk_up_bound = Eigen::VectorXd::Zero(size_F_k0);
    Eigen::VectorXd eta_fk_up_bound =  Eigen::VectorXd::Zero(size_F_k0);
    // no bound defined for pq_fk_od
    Eigen::VectorXd  pg_fk_od_up = Eigen::VectorXd::Zero(4 * size_F_k0);


    x_fk_sw_up_bound.setConstant(1.0);
    // no apparent upper bound from document
    b_fk_up_bound.setConstant(1e20);
    g_fk_up_bound.setConstant(1e20);
    // from eqn(280), its requirement is to be strictly positive
    eta_fk_up_bound.setConstant(1e20);
    pg_fk_od_up.setConstant(1e20);

    // individual lower bounds
    Eigen::VectorXd s_fnk_lo_bound = Eigen::VectorXd::Zero(s_fnk_up_bound.size());
    Eigen::VectorXd x_fk_sw_lo_bound = Eigen::VectorXd::Zero(size_F_k0);
    Eigen::VectorXd x_fk_st_lo_bound = -1 * x_fk_st_bound;
    Eigen::VectorXd b_fk_lo_bound = Eigen::VectorXd::Zero(size_F_k0);
    Eigen::VectorXd g_fk_lo_bound = Eigen::VectorXd::Zero(size_F_k0);
    Eigen::VectorXd eta_fk_lo_bound = Eigen::VectorXd::Zero(size_F_k0);
    // no bound defined for pq_fk_od
    Eigen::VectorXd  pg_fk_od_lo = Eigen::VectorXd::Zero(4 * size_F_k0);

    b_fk_lo_bound.setConstant(-1e20);
    g_fk_up_bound.setConstant(-1e20);
    pg_fk_od_lo.setConstant(-1e20);
    // no need to modify eta_fk_lo_bound since it's all zeros
    upper_bound << s_fnk_up_bound, x_fk_sw_up_bound, x_fk_st_up_bound, tau_fk_over, theta_fk_over, b_fk_up_bound, g_fk_up_bound, eta_fk_up_bound, pg_fk_od_up;
    lower_bound << s_fnk_lo_bound, x_fk_sw_lo_bound, x_fk_st_lo_bound, tau_fk_under, theta_fk_under, b_fk_lo_bound, g_fk_up_bound, eta_fk_lo_bound, pg_fk_od_lo;

    for (size_t idx=0; idx<GetRows(); idx++)
    {
        line_bounds.at(idx).upper_ = upper_bound(idx);
        line_bounds.at(idx).lower_ = lower_bound(idx);

    }

    return line_bounds;

}