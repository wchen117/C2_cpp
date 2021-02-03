#include <constraints/bus_constraints.hpp>

BusConstraints::BusConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : ConstraintSet(1, name) 
{
    data_fvariable = data_ptr;

}

BusConstraints::~BusConstraints(){}

VectorXd BusConstraints::GetValues() const 
{
    VectorXd g(GetRows());
    VectorXd x = GetVariables()->GetComponent("bus_variables")->GetValues();
    g(0) = std::pow(x(0),2) + x(1);
    return g;
}
BusConstraints::VecBound BusConstraints::GetBounds() const 
{
    VecBound b(GetRows());
    b.at(0) = ifopt::Bounds(1.0, 1.0);
    return b;

}
void BusConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const {}


