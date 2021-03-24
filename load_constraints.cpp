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
    Eigen::VectorXd eq_40_cons(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_41_cons(load_var_ptr->t_jk_size);


    assert(load_var_ptr->load_j_id.size() == load_var_ptr->t_jk_size);

    // p_jk = \sum_n p_jkn
    for (size_t idx=0; idx<load_var_ptr->p_jkn.size(); idx++)
    {
        for(size_t jdx=0; jdx<load_var_ptr->p_jkn.at(idx).size(); jdx++)
        {
            p_jk(idx) += load_var_ptr->p_jkn.at(idx).at(jdx);
        }
    }

    for (size_t idx=0; idx<load_var_ptr->load_j_id.size(); idx++) {
        auto j = load_var_ptr->load_j_id.at(idx);
        auto p_j_0 = load_var_ptr->load_ref_data->p_l[j];
        auto q_j_0 = load_var_ptr->load_ref_data->q_l[j];

        eq_40_cons(idx) = p_j_0 * load_var_ptr->t_jk.at(idx);
        eq_41_cons(idx) = q_j_0 * load_var_ptr->t_jk.at(idx);
    }

    // equation 40, 41, (42 and 43)
    load_cons << p_jk - eq_40_cons, q_jk - eq_41_cons, p_jk;


    return load_cons;


}

LoadConstraints::VecBound LoadConstraints::GetBounds() const
{
    VecBound load_con_bounds(GetRows());
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());
    Eigen::VectorXd test_upper_bound = Eigen::VectorXd::Zero(load_var_ptr->t_jk_size);
    Eigen::VectorXd test_lower_bound = Eigen::VectorXd::Zero(load_var_ptr->t_jk_size);

    Eigen::VectorXd eq_42_cons(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_43_cons(load_var_ptr->t_jk_size);

    for (size_t idx=0; idx<load_var_ptr->load_j_id.size(); idx++)
    {
        auto j = load_var_ptr->load_j_id.at(idx);
        auto p_j_0 = load_var_ptr->load_ref_data->p_l[j];
        auto q_j_0 = load_var_ptr->load_ref_data->q_l[j];

        eq_42_cons(idx) = p_j_0 + load_var_ptr->p_j_ru_over.at(idx) * load_var_ptr->load_ref_data->new_data.sup.sys_prms["deltar"];
        eq_43_cons(idx) = p_j_0 - load_var_ptr->p_j_rd_over.at(idx) * load_var_ptr->load_ref_data->new_data.sup.sys_prms["deltar"];

    }

    test_upper_bound.setConstant(1e20);
    test_lower_bound.setConstant(-1e20);

    upper_bound << test_upper_bound, test_upper_bound, test_upper_bound;
    lower_bound << test_lower_bound, test_lower_bound, test_lower_bound;

    for(size_t idx=0; idx<load_con_bounds.size(); idx++)
    {
        load_con_bounds.at(idx).upper_ = 1e20;
        load_con_bounds.at(idx).lower_ = -1e20;
    }

    return load_con_bounds;

}
void LoadConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    load_var_ptr = x->GetComponent<LoadVariables>(load_var_name);
}
void LoadConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{
    if (var_set == load_var_name)
    {
        /**
        size_t counter = 0;
        Eigen::MatrixXd jac_p_jkn = Eigen::MatrixXd::Zero(GetRows(), load_var_ptr->p_jkn_size);
        Eigen::MatrixXd jac_q_jk = Eigen::MatrixXd::Zero(GetRows(), load_var_ptr->q_jk.size());
        Eigen::MatrixXd jac_t_jk = Eigen::MatrixXd::Zero(GetRows(), load_var_ptr->t_jk_size);

        //Eigen::VectorXd p_jkn_block = Eigen::VectorXd::Ones();
        for (size_t idx=0; idx=load_var_ptr->p_jkn.size(); idx++)
        {
            for (size_t jdx=0; jdx=load_var_ptr->p_jkn.at(idx).size(); jdx++)
            {
                jac_p_jkn(idx, counter) = 1.0;
                counter++;

            }

        }

        std::cout<<jac_p_jkn<<std::endl;
         **/


    }

}