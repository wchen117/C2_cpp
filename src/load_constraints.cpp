//
// Created by wchen on 3/11/21.
//
#include <constraints/load_constraints.hpp>

LoadConstraints::LoadConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    load_var_name = name;

    // so here the constraints are
    SetRows(3*data_ptr->J_k.size());

}

LoadConstraints::~LoadConstraints(){}

Eigen::VectorXd LoadConstraints::GetValues() const
{
    // we have defined that p_jk and v_jk are indexed
    // by order of load_j_id here as well
    Eigen::VectorXd load_cons(GetRows());
    Eigen::VectorXd p_jk(load_var_ptr->t_jk_size);
    Eigen::Map<const Eigen::VectorXd> q_jk(load_var_ptr->q_jk.data(), load_var_ptr->q_jk.size());


    assert(load_var_ptr->load_j_id.size() == load_var_ptr->t_jk_size);

    // p_jk = \sum_n p_jkn
    for (size_t idx=0; idx<load_var_ptr->p_jkn.size(); idx++)
    {
        for(size_t jdx=0; jdx<load_var_ptr->p_jkn.at(idx).size(); jdx++)
        {
            //std::cout<<idx<<" "<<jdx<<std::endl;
            p_jk(idx) += load_var_ptr->p_jkn.at(idx).at(jdx);
        }
    }

    // equation 40, 41, (42 and 43)
    load_cons << p_jk, q_jk, p_jk;

    return load_cons;


}

LoadConstraints::VecBound LoadConstraints::GetBounds() const
{
    VecBound load_con_bounds(GetRows());
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());


    Eigen::VectorXd eq_40_cons(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_41_cons(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_42_cons(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_43_cons(load_var_ptr->t_jk_size);
    for (size_t idx=0; idx<load_var_ptr->load_j_id.size(); idx++)
    {
        auto j = load_var_ptr->load_j_id.at(idx);
        auto p_j_0 = load_var_ptr->load_ref_data->p_l[j];
        auto q_j_0 = load_var_ptr->load_ref_data->q_l[j];

        eq_40_cons(idx) = p_j_0 * load_var_ptr->t_jk.at(idx);
        eq_41_cons(idx) = q_j_0 * load_var_ptr->t_jk.at(idx);
        eq_42_cons(idx) = p_j_0 + load_var_ptr->p_j_ru_over.at(idx) * load_var_ptr->load_ref_data->new_data.sup.sys_prms["deltar"];
        eq_43_cons(idx) = p_j_0 - load_var_ptr->p_j_rd_over.at(idx) * load_var_ptr->load_ref_data->new_data.sup.sys_prms["deltar"];

    }

    upper_bound << eq_40_cons, eq_41_cons, eq_42_cons;
    lower_bound << eq_40_cons, eq_41_cons, eq_43_cons;

    for(size_t idx=0; idx<load_con_bounds.size(); idx++)
    {
        load_con_bounds.at(idx).upper_ = upper_bound(idx);
        load_con_bounds.at(idx).lower_ = lower_bound(idx);
    }

    return load_con_bounds;

}
void LoadConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    load_var_ptr = x->GetComponent<LoadVariables>(load_var_name);
}
void LoadConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}