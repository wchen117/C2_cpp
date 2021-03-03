#include <constraints/bus_constraints.hpp>
BusConstraints::BusConstraints(const std::string& name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    bus_var_name = name;
    SetRows(10);
}

BusConstraints::~BusConstraints(){}

Eigen::VectorXd BusConstraints::GetValues() const
{
    Eigen::VectorXd g(GetRows());
    return g;

}

BusConstraints::VecBound BusConstraints::GetBounds() const
{
    VecBound b(GetRows());
    return b;

}

void BusConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    bus_var_ptr = x->GetComponent<BusVariables>(bus_var_name);
}
void BusConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}