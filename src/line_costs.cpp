//
// Created by wchen on 2/23/21.
//
#include "costs/line_costs.hpp"
LineCosts::LineCosts(const std::string& name) : CostTerm(name + "_obj")
{
    line_var_name = name;
}
LineCosts::~LineCosts()
{

}
double LineCosts::GetCost() const
{
    Eigen::VectorXd x = ifopt::ConstraintSet::GetVariables()->GetComponent(line_var_name)->GetValues();
    auto load_var_ptr = ifopt::ConstraintSet::GetVariables()->GetComponent<LineVariables>(line_var_name);

}
void LineCosts::InitVariableDependedQuantities(const VariablesPtr& x)
{
    //load_var_ptr = x->GetComponent<LoadVariables>(load_var_name);

}

void LineCosts::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{

}