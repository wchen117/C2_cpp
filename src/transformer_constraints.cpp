//
// Created by wchen on 3/29/21.
//
#include <constraints/transformer_constraints.hpp>

TransConstraints::TransConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    trans_var_name = name;
    SetRows(4 * data_ptr->F_k.size());


}
TransConstraints::~TransConstraints() {}

Eigen::VectorXd TransConstraints::GetValues() const
{
    Eigen::VectorXd trans_cons (GetRows());
    Eigen::VectorXd tau_fk_cons (trans_var_ptr->tau_fk.size());
    Eigen::VectorXd const &Eqn62 = trans_var_ptr->tau_fk - (trans_var_ptr->tau_f_st.array() * trans_var_ptr->x_fk_st.array()).matrix() - trans_var_ptr->theta_f_mid;
    Eigen::VectorXd const &Eqn63  = trans_var_ptr->tau_f_0 -trans_var_ptr->theta_f_0;

    Eigen::VectorXd theta_fk_cons (trans_var_ptr->theta_fk.size());
    Eigen::VectorXd const &Eqn64 = trans_var_ptr->theta_fk - (trans_var_ptr->theta_f_st.array() * trans_var_ptr->x_fk_st.array()).matrix();
    Eigen::VectorXd const &Eqn65  = trans_var_ptr->theta_f_0;


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

        for (auto fk_theta:trans_var_ptr->local_input_ptr->F_theta)
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

    }









}

TransConstraints::VecBound TransConstraints::GetBounds() const
{

}

void TransConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    trans_var_ptr = x->GetComponent<TransformerVariables>(trans_var_name);
}
void TransConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}

