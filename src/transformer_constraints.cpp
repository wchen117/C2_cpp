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

