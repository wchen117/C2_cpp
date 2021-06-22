//
// Created by wchen on 2/18/21.
//

#include "variables/line_variables.hpp"
LineVariables::LineVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::shared_ptr<BusVariables> bus_var_ptr, const std::string& name): VariableSet(-1, name)
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
        ref_id = Eigen::VectorXi::Zero(size_E_k0);
        // so what's their initial value
        // x_ek_sw and x_e_sw0 are ordered by E_k's order
        x_ek_sw = Eigen::VectorXd::Zero(size_E_k0);
        x_ek_sw_bound = Eigen::VectorXd::Zero(size_E_k0);
        x_e_sw0 = Eigen::VectorXd::Zero(size_E_k0);
        // assume all on constraints to start with
        swqual_state = Eigen::VectorXd::Ones(size_E_k0);



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
                // this is equal to comparing two tuples e_key and (n.origbus, n.destbus, n.id), I think?
                if (oribus_num == n.origbus && destbus_num == n.destbus &&  bus_i==n.id)
                {

                    // fetched origbus and desbus are not ordered, use ref_origbus and ref_desbus to help keep track
                    ref_oribus(idx) = n.origbus;
                    ref_desbus(idx) = n.destbus;

                    ref_id(idx) = stoi(n.id);
                    c_e_sw(idx) = n.csw;
                    // eq(153)

                    x_e_sw0(idx) = local_input_ptr->x_e_sw_0.at(e_key);



                    // Eq(49, e \in E_sw if n.swqual == 1 is taken care of this way)
                    // shall we use n.swqual < 1?
                    if (n.swqual == 0)
                    {
                        swqual_state(idx) = 0;
                    }



                    for(size_t jdx=0; jdx<Ns; jdx++)
                    {
                        c_n_s(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).c * local_input_ptr->s_tilde;
                        t_n_s_over(jdx, idx) = local_input_ptr->new_data.sup.scblocks.at(jdx).tmax;
                        r_e_over_eigen(jdx, idx) = local_input_ptr->r_e_over.at(e_key);

                    }

                }
            }

        }

        // now to deal with x_ek_sw masked by


        p_ek_o = Eigen::VectorXd::Zero(local_input_ptr->E_k0.size());
        q_ek_o = Eigen::VectorXd::Zero(local_input_ptr->E_k0.size());
        p_ek_d = Eigen::VectorXd::Zero(local_input_ptr->E_k0.size());
        q_ek_d = Eigen::VectorXd::Zero(local_input_ptr->E_k0.size());
        bus_vik = Eigen::VectorXd::Zero(local_input_ptr->E_k0.size());
        bus_vipk = Eigen::VectorXd::Zero(local_input_ptr->E_k0.size());
        for (size_t ekdx=0; ekdx< local_input_ptr->E_k0.size(); ekdx++)
        {
            auto ek = local_input_ptr->E_k0.at(ekdx);
            // i \in i_e_o for e \in E_k, i_p \in i_e_d for e \in E_k
            auto idx = local_input_ptr->i_e_o.at(ek);
            auto ipdx = local_input_ptr->i_e_d.at(ek);
            auto ge = local_input_ptr->g_e.at(ek);
            auto be = local_input_ptr->b_e.at(ek);
            auto be_ch = local_input_ptr->b_e_ch.at(ek);
            //auto diff = local_input_ptr->theta_0.at(idx) - local_input_ptr->theta_0.at(ipdx);
            // now figure out the where bus idx and ipdx locate in v_ik
            // findInVector located in typedefinition.hpp
            auto bus_idx_pair = findInVector(bus_var_ptr->sorted_bus_ID, idx);
            auto bus_ipdx_pair = findInVector(bus_var_ptr->sorted_bus_ID, ipdx);
            auto tmp_x_ek_sw = x_ek_sw(ekdx);
            if (bus_idx_pair.first && bus_ipdx_pair.first)
            {
                auto bus_idx = bus_idx_pair.second;
                auto bus_ipdx = bus_ipdx_pair.second;
                auto vik = bus_var_ptr->v_ik(bus_idx);
                auto vipk = bus_var_ptr->v_ik(bus_ipdx);
                auto thetaik = bus_var_ptr->theta_ik(bus_idx);
                auto thetaipk = bus_var_ptr->theta_ik(bus_ipdx);
                auto diff = thetaik - thetaipk;
                bus_vik(ekdx) = bus_var_ptr->v_ik(bus_idx);
                bus_vipk(ekdx) = bus_var_ptr->v_ik(bus_idx);

                // eq 50 - 53
                auto tmp_p_ek_o = tmp_x_ek_sw * (ge * vik * vik - (ge * cos(diff) + be * sin(diff)) * vik * vipk);
                auto tmp_q_ek_o = tmp_x_ek_sw * (-(be + be_ch * 0.5) * vik * vik + (be * cos(diff) - ge * sin(diff)) * vik * vipk);
                auto tmp_p_ek_d = tmp_x_ek_sw * (ge * vipk * vipk - (ge * cos(-diff) + be * sin(-diff)) * vik * vipk);
                auto tmp_q_ek_d = tmp_x_ek_sw * (-(be + be_ch * 0.5) * vipk * vipk + (be * cos(-diff) - ge * sin(-diff))* vik * vipk);
                // so... these four should always have the same size
                p_ek_o(ekdx) = tmp_p_ek_o;
                q_ek_o(ekdx) = tmp_q_ek_o;
                p_ek_d(ekdx) = tmp_p_ek_d;
                q_ek_d(ekdx) = tmp_q_ek_d;
                std::cout<<"tmp_p_ek_o = "<<tmp_p_ek_o<<std::endl;

            }
            else{
                exit(0);
            }

        }

        //std::cout<<p_ek_o.transpose()<<std::endl;

        pq_ek_od_size =  p_ek_o.size();

        if (size_E_k0 && Ns && pq_ek_od_size)
        {
            line_var_len = size_E_k0 * Ns + size_E_k0 + 4 * pq_ek_od_size;
            SetRows(line_var_len);
        }
        else{
            std::cout<<"null size for size_E_k or Ns or pq_ek_od, quit"<<std::endl;
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

        Eigen::Map<const Eigen::VectorXd> flat_s_enk(s_enk_plus.data(), s_enk_plus.size());


        tmp_x << flat_s_enk, x_ek_sw, p_ek_o, q_ek_o, p_ek_d, q_ek_d;

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
    p_ek_o = x.segment(flat_len+size_E_k0, pq_ek_od_size);
    q_ek_o = x.segment(flat_len+size_E_k0+pq_ek_od_size, pq_ek_od_size);
    p_ek_d = x.segment(flat_len+size_E_k0+2*pq_ek_od_size, pq_ek_od_size);
    q_ek_d = x.segment(flat_len+size_E_k0+3*pq_ek_od_size, pq_ek_od_size);
}

LineVariables::VecBound  LineVariables::GetBounds() const
{

    VecBound line_bounds(GetRows());

    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());
    // now to populate the upper and lower bounds
    // i don't see bounds for pq_ek_od yet

    Eigen::MatrixXd tmp_prod = (t_n_s_over.array() * r_e_over_eigen.array()).matrix();
    Eigen::Map<const Eigen::VectorXd> tmp_flat_prod(tmp_prod.data(), tmp_prod.size());
    Eigen::VectorXd x_ek_sw_bound(size_E_k0);
    for (size_t idx=0; idx<size_E_k0; idx++)
    {
        x_ek_sw_bound(idx) = 1.0;
    }
    Eigen::VectorXd pq_ek_od_up_bound = Eigen::VectorXd::Zero(4 * pq_ek_od_size);
    Eigen::VectorXd pq_ek_od_lo_bound = Eigen::VectorXd::Zero(4 * pq_ek_od_size);
    pq_ek_od_up_bound.setConstant(1e20);

    upper_bound << tmp_flat_prod, x_ek_sw_bound, pq_ek_od_up_bound;

    pq_ek_od_lo_bound.setConstant(-1e20);
    Eigen::VectorXd flat_lo_bound = Eigen::VectorXd::Zero(tmp_flat_prod.size());
    Eigen::VectorXd x_ek_sw_lo_bound = Eigen::VectorXd::Zero(x_ek_sw_bound.size());
    lower_bound << flat_lo_bound, x_ek_sw_lo_bound, pq_ek_od_lo_bound;

    for (size_t idx=0; idx<GetRows(); idx++)
    {
        line_bounds.at(idx).upper_ = upper_bound(idx);
        line_bounds.at(idx).lower_ = lower_bound(idx);

    }

    return line_bounds;


}
