//
// Created by wchen on 3/31/21.
//
#include <constraints/generator_constraints.hpp>

GeneratorConstraints::GeneratorConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{

}

GeneratorConstraints::~GeneratorConstraints() {}

Eigen::VectorXd GeneratorConstraints::GetValues() const
{

}

GeneratorConstraints::VecBound GeneratorConstraints::GetBounds() const
{

}

void GeneratorConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    gen_var_ptr = x->GetComponent<GeneratorVariables>(gen_var_name);
}
void GeneratorConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}