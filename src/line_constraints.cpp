//
// Created by wchen on 3/17/21.
//

#include <constraints/line_constraints.hpp>

LineConstraints::LineConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    // this name is the corresponding line variable name
    line_var_name = name;
    SetRows(4 * data_ptr->E_k.size());

}
LineConstraints::~LineConstraints() {}


Eigen::VectorXd LineConstraints::GetValues() const
{
    Eigen::VectorXd line_cons(GetRows());
    //std::cout<<"Hello this is from GetValues"<<std::endl;
    UMAP_TUPLE_iis_DOUBLE p_ek_o, q_ek_o, p_ek_d, q_ek_d;
    // x_ek_sw is also ordered by ek in E_k (see line_variables.cpp)
    // we need index of E_k (ekdx) to reference indices in x_ek_sw
    for (size_t ekdx=0; ekdx< line_var_ptr->local_input_ptr->E_k.size(); ekdx++)
    {
        auto ek = line_var_ptr->local_input_ptr->E_k.at(ekdx);
        // i \in i_e_o for e \in E_k, i_p \in i_e_d for e \in E_k
        auto idx = line_var_ptr->local_input_ptr->i_e_o[ek];
        auto ipdx = line_var_ptr->local_input_ptr->i_e_d[ek];
        auto ge = line_var_ptr->local_input_ptr->g_e[ek];
        auto be = line_var_ptr->local_input_ptr->b_e[ek];
        auto be_ch = line_var_ptr->local_input_ptr->b_e_ch[ek];
        auto diff = line_var_ptr->local_input_ptr->theta_0[idx] - line_var_ptr->local_input_ptr->theta_0[ipdx];
        // now figure out the where bus idx and ipdx locate in v_ik
        auto bus_idx_pair = findInVector(bus_var_ptr->sorted_bus_ID, idx);
        auto bus_ipdx_pair = findInVector(bus_var_ptr->sorted_bus_ID, ipdx);
        auto tmp_x_ek_sw = line_var_ptr->x_ek_sw(ekdx);
        if (bus_idx_pair.first && bus_ipdx_pair.first)
        {
            auto bus_idx = bus_idx_pair.second;
            auto bus_ipdx = bus_ipdx_pair.second;
            auto vik = bus_var_ptr->v_ik(bus_idx);
            auto vipk = bus_var_ptr->v_ik(bus_ipdx);
            // eq 50 - 53
            auto tmp_p_ek_o = tmp_x_ek_sw * (ge * vik * vik - (ge * cos(diff) + be * sin(diff)) * vik * vipk);
            auto tmp_q_ek_o = tmp_x_ek_sw * (-(be + be_ch * 0.5) * vik * vik + (be * cos(diff) - ge * sin(diff)) * vik * vipk);
            auto tmp_p_ek_d = tmp_x_ek_sw * (ge * vipk * vipk - (ge * cos(-diff) + be * sin(-diff)) * vik * vipk);
            auto tmp_q_ek_d = tmp_x_ek_sw * (-(be + be_ch * 0.5) * vipk * vipk + (be * cos(-diff) - ge * sin(-diff))* vik * vipk);
            p_ek_o.insert(std::make_pair(ek, tmp_p_ek_o));
            q_ek_o.insert(std::make_pair(ek, tmp_q_ek_o));
            p_ek_d.insert(std::make_pair(ek, tmp_p_ek_d));
            q_ek_d.insert(std::make_pair(ek, tmp_q_ek_d));

        }
        else{
            exit(0);
        }

    }

    return line_cons;
}

LineConstraints::VecBound LineConstraints::GetBounds() const
{
    VecBound line_con_bounds(GetRows());
    return line_con_bounds;
}

void LineConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    line_var_ptr = x->GetComponent<LineVariables>(line_var_name);
    bus_var_ptr = x->GetComponent<BusVariables>("bus_variables");
}
void LineConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}




