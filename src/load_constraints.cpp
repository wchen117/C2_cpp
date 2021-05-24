//
// Created by wchen on 3/11/21.
//
#include <constraints/load_constraints.hpp>

LoadConstraints::LoadConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    load_var_name = name;

    // so here the constraints are
    SetRows(4 * data_ptr->J_k0.size());

}

LoadConstraints::~LoadConstraints(){}

Eigen::VectorXd LoadConstraints::GetValues() const
{
    // we have defined that p_jk and v_jk are indexed
    // by order of load_j_id here as well
    Eigen::VectorXd load_cons(GetRows());

    Eigen::VectorXd eq_40(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_41(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_42(load_var_ptr->t_jk_size);
    Eigen::VectorXd eq_43(load_var_ptr->t_jk_size);

    // p_jk = \sum_n p_jkn
    Eigen::VectorXd p_jk = load_var_ptr->get_p_jk();
    Eigen::VectorXd q_jk = load_var_ptr->get_q_jk();

    //
    const double &delta_r = load_var_ptr->load_ref_data->new_data.sup.sys_prms["deltar"];

    eq_40 = (p_jk.array() - load_var_ptr->p_j_0.array() * load_var_ptr->t_jk.array()).matrix();
    eq_41 = (q_jk.array() - load_var_ptr->q_j_0.array() * load_var_ptr->t_jk.array()).matrix();
    eq_42 = (p_jk.array() - load_var_ptr->p_j_0.array() - load_var_ptr->p_j_ru_over.array() * delta_r).matrix();
    eq_43 = (p_jk.array() - load_var_ptr->p_j_0.array() + load_var_ptr->p_j_rd_over.array() * delta_r).matrix();

    load_cons << eq_40, eq_41, eq_42, eq_43;
    return load_cons;

}

LoadConstraints::VecBound LoadConstraints::GetBounds() const
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
void LoadConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    load_var_ptr = x->GetComponent<LoadVariables>(load_var_name);
}
void LoadConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{
    if (var_set == load_var_name)
    {

        // size of p_jk = the size of p_jkn's first dimension
        Eigen::MatrixXd eqn40_wrt_flat_p_jkn = Eigen::MatrixXd::Zero(load_var_ptr->p_jk_size, load_var_ptr->p_jkn_size);
        size_t sum_len = 0;
        for (size_t idx=0; idx<load_var_ptr->p_jkn.size(); idx++)
        {
            for (size_t jdx=0; jdx<load_var_ptr->p_jkn.at(idx).size(); jdx++)
            {
                // p_jk = \sum_n p_jkn, for each j, only
                eqn40_wrt_flat_p_jkn(idx, jdx + sum_len) = 1.0;
            }
            sum_len += load_var_ptr->p_jkn.at(idx).size();
        }

        // eqn40 has no q_jk, q_jk and t_jk same size
        Eigen::MatrixXd eqn40_wrt_q_jk = Eigen::MatrixXd::Zero(load_var_ptr->p_jk_size, load_var_ptr->q_jk.size());
        Eigen::MatrixXd eqn40_wrt_t_jk = Eigen::MatrixXd(load_var_ptr->p_jk_size, load_var_ptr->t_jk_size);
        eqn40_wrt_t_jk.diagonal() << -1.0 * load_var_ptr->p_j_0;
        Eigen::MatrixXd eqn40_jac(eqn40_wrt_flat_p_jkn.rows(), eqn40_wrt_flat_p_jkn.cols() + eqn40_wrt_q_jk.cols() + eqn40_wrt_t_jk.cols());
        eqn40_jac << eqn40_wrt_flat_p_jkn, eqn40_wrt_q_jk, eqn40_wrt_t_jk;

        Eigen::MatrixXd eqn41_wrt_flat_p_jkn = Eigen::MatrixXd::Zero(load_var_ptr->p_jk_size, load_var_ptr->p_jkn_size);
        Eigen::MatrixXd eqn41_wrt_q_jk = Eigen::MatrixXd::Ones(load_var_ptr->p_jk_size, load_var_ptr->q_jk.size());
        Eigen::MatrixXd eqn41_wrt_t_jk = Eigen::MatrixXd(load_var_ptr->p_jk_size, load_var_ptr->q_jk.size());
        eqn41_wrt_t_jk.diagonal() << -1.0 * load_var_ptr->q_j_0;

        Eigen::MatrixXd eqn41_jac(eqn41_wrt_flat_p_jkn.rows(), eqn41_wrt_flat_p_jkn.cols() + eqn41_wrt_q_jk.cols() + eqn41_wrt_t_jk.cols());
        eqn41_jac << eqn41_wrt_flat_p_jkn, eqn41_wrt_q_jk, eqn41_wrt_t_jk;

        // eqn42
        Eigen::MatrixXd const& eqn42_wrt_flat_p_jkn = eqn40_wrt_flat_p_jkn;
        Eigen::MatrixXd eqn42_wrt_q_jk = Eigen::MatrixXd::Zero(load_var_ptr->p_jk_size, load_var_ptr->q_jk.size());
        Eigen::MatrixXd eqn42_wrt_t_jk = Eigen::MatrixXd::Zero(load_var_ptr->p_jk_size, load_var_ptr->q_jk.size());
        Eigen::MatrixXd eqn42_jac(eqn42_wrt_flat_p_jkn.rows(), eqn42_wrt_flat_p_jkn.cols() + eqn42_wrt_q_jk.cols() + eqn42_wrt_t_jk.cols());
        eqn42_jac << eqn42_wrt_flat_p_jkn, eqn42_wrt_q_jk, eqn42_wrt_t_jk;

        //eqn43
        Eigen::MatrixXd const& eqn43_wrt_flat_p_jkn = eqn40_wrt_flat_p_jkn;
        Eigen::MatrixXd const& eqn43_wrt_q_jk = eqn42_wrt_q_jk;
        Eigen::MatrixXd const& eqn43_wrt_t_jk = eqn42_wrt_t_jk;
        Eigen::MatrixXd eqn43_jac(eqn43_wrt_flat_p_jkn.rows(), eqn43_wrt_flat_p_jkn.cols() + eqn43_wrt_q_jk.cols() + eqn43_wrt_t_jk.cols());
        eqn43_jac << eqn43_wrt_flat_p_jkn, eqn43_wrt_q_jk, eqn43_wrt_t_jk;

        Eigen::MatrixXd load_jac(4 * eqn42_wrt_flat_p_jkn.rows(), eqn42_wrt_flat_p_jkn.cols() + eqn42_wrt_q_jk.cols() + eqn42_wrt_t_jk.cols());
        load_jac << eqn40_jac, eqn41_jac, eqn42_jac, eqn43_jac;


        for(size_t idx=0; idx<jac_block.rows(); idx++)
        {
            for(size_t jdx=0; jdx<jac_block.cols(); jdx++)
            {
                jac_block.coeffRef(idx, jdx) = load_jac(idx, jdx);
            }
        }


    }

}