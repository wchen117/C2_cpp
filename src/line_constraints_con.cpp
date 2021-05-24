//
// Created by wchen on 3/17/21.
//

#include <constraints/line_constraints_con.hpp>

LineConstraintsCon::LineConstraintsCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    // this name is the corresponding line variable name
    line_var_name = name;
    SetRows(4 * data_ptr->E_k0.size());

}
LineConstraintsCon::~LineConstraintsCon() {}


Eigen::VectorXd LineConstraintsCon::GetValues() const
{
    Eigen::VectorXd line_cons(GetRows());
    // eqn 49
    Eigen::VectorXd eq49 = (line_var_ptr->x_ek_sw.array() - line_var_ptr->x_e_sw0.array()).matrix();
    // eqn 54
    Eigen::VectorXd s_ek_plus = line_var_ptr->s_enk_plus.colwise().sum();
    // eqn 55 - 56 for k = k_0 case
    Eigen::VectorXd eq57 = ((line_var_ptr->p_ek_o.array().square() +  line_var_ptr->q_ek_o.array().square()).sqrt() - s_ek_plus.array()).matrix();
    Eigen::VectorXd eq58 = ((line_var_ptr->p_ek_d.array().square() +  line_var_ptr->q_ek_d.array().square()).sqrt() - s_ek_plus.array()).matrix();

    line_cons << eq49, s_ek_plus, eq57, eq58;

    return line_cons;
}

LineConstraintsCon::VecBound LineConstraintsCon::GetBounds() const
{
    VecBound line_con_bounds(GetRows());
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());
    // x_ek_sw \in (0, 1), x_e_sw0 \in (0, 1), so eq49 must be either -1, 0, or 1
    Eigen::VectorXd eq49_up_bound = Eigen::VectorXd::Ones(line_var_ptr->size_E_k0);
    Eigen::VectorXd eq49_lo_bound = -1 * Eigen::VectorXd::Ones(line_var_ptr->size_E_k0);

    Eigen::VectorXd sek_up_bound = Eigen::VectorXd::Zero(line_var_ptr->size_E_k0);
    Eigen::VectorXd sek_lo_bound = Eigen::VectorXd::Zero(line_var_ptr->size_E_k0);
    Eigen::VectorXd eq57_up_bound = Eigen::VectorXd::Zero(line_var_ptr->size_E_k0);
    Eigen::VectorXd eq57_lo_bound = Eigen::VectorXd::Zero(line_var_ptr->size_E_k0);
    Eigen::VectorXd eq58_up_bound = Eigen::VectorXd::Zero(line_var_ptr->size_E_k0);
    Eigen::VectorXd eq58_lo_bound = Eigen::VectorXd::Zero(line_var_ptr->size_E_k0);

    // eq(49), x_ek_sw - x_e_sw0 = 0 if swqual = 0, else have normal bound 0 and 1
    eq49_up_bound = (eq49_up_bound.array() * line_var_ptr->swqual_state.array()).matrix();
    eq49_lo_bound = (eq49_lo_bound.array() * line_var_ptr->swqual_state.array()).matrix();

    sek_up_bound.setConstant(1e20);
    // content of r_e_over_eigen is changed in line_variables_con.cpp
    eq57_up_bound = (line_var_ptr->r_e_over_eigen.row(0).transpose().array() * line_var_ptr->bus_vik.array()).matrix();
    eq57_lo_bound.setConstant(-1e20);
    eq58_up_bound = (line_var_ptr->r_e_over_eigen.row(0).transpose().array() * line_var_ptr->bus_vipk.array()).matrix();
    eq58_lo_bound.setConstant(-1e20);

    upper_bound << eq49_up_bound, sek_up_bound, eq57_up_bound, eq58_up_bound;
    lower_bound << eq49_lo_bound, sek_lo_bound, eq57_lo_bound, eq58_lo_bound;

    for (size_t idx=0; idx<line_con_bounds.size(); idx++)
    {
        line_con_bounds.at(idx).upper_ = upper_bound(idx);
        line_con_bounds.at(idx).lower_ = lower_bound(idx);
    }


    return line_con_bounds;
}

void LineConstraintsCon::InitVariableDependedQuantities(const VariablesPtr& x)
{
    line_var_ptr = x->GetComponent<LineVariablesCon>(line_var_name);
}
void LineConstraintsCon::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}



