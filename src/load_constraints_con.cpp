//
// Created by wchen on 3/11/21.
//
#include <constraints/load_constraints_con.hpp>

LoadConstraintsCon::LoadConstraintsCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    load_var_name = name;

    // so here the constraints are
    SetRows(4 * data_ptr->J_k0.size());

}

LoadConstraintsCon::~LoadConstraintsCon(){}

Eigen::VectorXd LoadConstraintsCon::GetValues() const
{
    // we have defined that p_jk and v_jk are indexed
    // by order of load_j_id here as well
    Eigen::VectorXd load_cons(GetRows());

    Eigen::VectorXd eq_40(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_41(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_44(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_45(load_var_ptr->t_jk_size);

    // p_jk = \sum_n p_jkn
    Eigen::VectorXd p_jk = load_var_ptr->get_p_jk();
    Eigen::VectorXd q_jk = load_var_ptr->get_q_jk();

    //
    const double &delta_r = load_var_ptr->load_ref_data->new_data.sup.sys_prms["deltarctg"];

    eq_40 = (p_jk.array() - load_var_ptr->p_j_0.array() * load_var_ptr->t_jk.array()).matrix();
    eq_41 = (q_jk.array() - load_var_ptr->q_j_0.array() * load_var_ptr->t_jk.array()).matrix();
    eq_44 = (p_jk.array() - load_var_ptr->p_j_0.array() - load_var_ptr->p_j_ru_over.array() * delta_r).matrix();
    eq_45 = (p_jk.array() - load_var_ptr->p_j_0.array() + load_var_ptr->p_j_rd_over.array() * delta_r).matrix();

    load_cons << eq_40, eq_41, eq_44, eq_45;
    return load_cons;

}

LoadConstraintsCon::VecBound LoadConstraintsCon::GetBounds() const
{
    VecBound load_con_bounds(GetRows());
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());

    Eigen::VectorXd zero_bound = Eigen::VectorXd::Zero(load_var_ptr->t_jk_size);
    Eigen::VectorXd up_infy_bound = Eigen::VectorXd::Zero(load_var_ptr->t_jk_size);
    up_infy_bound.setConstant(1e20);
    Eigen::VectorXd lo_infy_bound = Eigen::VectorXd::Zero(load_var_ptr->t_jk_size);
    lo_infy_bound.setConstant(-1e20);


    // arrange bounds such that they correspond to the load_cons above
    upper_bound << zero_bound, zero_bound, zero_bound, up_infy_bound;
    lower_bound << zero_bound, zero_bound, lo_infy_bound, zero_bound;

    for(size_t idx=0; idx<load_con_bounds.size(); idx++)
    {
        load_con_bounds.at(idx).upper_ = upper_bound(idx)+1;
        load_con_bounds.at(idx).lower_ = lower_bound(idx)-1;
    }

    return load_con_bounds;

}
void LoadConstraintsCon::InitVariableDependedQuantities(const VariablesPtr& x)
{
    load_var_ptr = x->GetComponent<LoadVariablesCon>(load_var_name);
}
void LoadConstraintsCon::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{
    if (var_set == load_var_name)
    {

    }

}