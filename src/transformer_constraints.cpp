//
// Created by wchen on 3/29/21.
//
#include <constraints/transformer_constraints.hpp>

TransConstraints::TransConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    trans_var_name = name;
    SetRows(4 * data_ptr->F_k0.size());


}
TransConstraints::~TransConstraints() {}

Eigen::VectorXd TransConstraints::GetValues() const
{
    Eigen::VectorXd trans_cons (GetRows());
    // eqn(62) - eqn(69) are all bounded to zero
    Eigen::VectorXd tau_fk_cons = Eigen::VectorXd::Zero(trans_var_ptr->tau_fk.size());
    const Eigen::VectorXd  &Eqn62 = trans_var_ptr->tau_fk - (trans_var_ptr->tau_f_st.array() * trans_var_ptr->x_fk_st.array()).matrix() - trans_var_ptr->tau_f_mid;
    const Eigen::VectorXd  &Eqn63  = trans_var_ptr->tau_fk - trans_var_ptr->theta_f_0;

    Eigen::VectorXd theta_fk_cons = Eigen::VectorXd::Zero(trans_var_ptr->theta_fk.size());
    const Eigen::VectorXd  &Eqn64 = trans_var_ptr->theta_fk - (trans_var_ptr->theta_f_st.array() * trans_var_ptr->x_fk_st.array()).matrix() - trans_var_ptr->theta_f_mid;
    const Eigen::VectorXd  &Eqn65  = trans_var_ptr->theta_fk - trans_var_ptr->theta_f_0;

    Eigen::VectorXd b_fk_cons = Eigen::VectorXd::Zero(trans_var_ptr->eta_fk.size());
    Eigen::VectorXd g_fk_cons = Eigen::VectorXd::Zero(trans_var_ptr->eta_fk.size());
    const Eigen::VectorXd  &Eqn66 = trans_var_ptr->b_fk - (trans_var_ptr->b_f_0.array() / trans_var_ptr->eta_fk.array()).matrix();
    const Eigen::VectorXd  &Eqn67 = trans_var_ptr->g_fk - (trans_var_ptr->g_f_0.array() / trans_var_ptr->eta_fk.array()).matrix();
    const Eigen::VectorXd  &Eqn68 = trans_var_ptr->b_fk - trans_var_ptr->b_f_0;
    const Eigen::VectorXd  &Eqn69 = trans_var_ptr->g_fk - trans_var_ptr->g_f_0;

    for (size_t idx=0; idx<trans_var_ptr->local_input_ptr->F_k0.size(); idx++)
    {
        auto fk = trans_var_ptr->local_input_ptr->F_k0.at(idx);

        for (auto fk_tau: trans_var_ptr->local_input_ptr->F_tau)
        {
            // condition on eqn(62), f \in F_k0 and F_tau
            if (fk == fk_tau)
            {
                tau_fk_cons(idx) = Eqn62(idx);
            }
            // condition on eqn(63), f \in F_k0 but not in F_tau
            else{
                tau_fk_cons(idx) = Eqn63(idx);

            }

        }

        for (auto fk_theta: trans_var_ptr->local_input_ptr->F_theta)
        {
            // condition on eqn(64), f \in F_k and F_theta
            if (fk == fk_theta)
            {
                theta_fk_cons(idx) = Eqn64(idx);

            }
            // condition on eqn(65), f \in F_k but not in F_theta
            else {
                theta_fk_cons(idx) = Eqn65(idx);
            }
        }

        // wrong name, should be F_eta
        for (auto fk_eta: trans_var_ptr->local_input_ptr->F_gamma)
        {
            // condition on eqn(66) and eqn(67)
            if (fk == fk_eta)
            {
                b_fk_cons(idx) = Eqn66(idx);
                g_fk_cons(idx) = Eqn67(idx);

            }
            // condition on eqn(68) and eqn(69)
            else {
                b_fk_cons(idx) = Eqn68(idx);
                g_fk_cons(idx) = Eqn69(idx);
            }


        }


    }
    trans_cons << tau_fk_cons, theta_fk_cons, b_fk_cons, g_fk_cons;
    return trans_cons;
}

TransConstraints::VecBound TransConstraints::GetBounds() const
{
    VecBound trans_con_bounds(GetRows());
    Eigen::VectorXd upper_bounds(GetRows());
    Eigen::VectorXd lower_bounds(GetRows());
    // well... eqn(70) and eqn(71) hasn't been coded yet, so
    // we might need to relax this bound
    upper_bounds.setConstant(10);
    lower_bounds.setConstant(-10);

    for (size_t idx=0; idx<GetRows(); idx++)
    {
        trans_con_bounds.at(idx).upper_ = upper_bounds(idx);
        trans_con_bounds.at(idx).lower_ = lower_bounds(idx);
    }

    return trans_con_bounds;
}

void TransConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    trans_var_ptr = x->GetComponent<TransformerVariables>(trans_var_name);
}
void TransConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}

