#include <constraints/bus_constraints.hpp>
BusConstraints::BusConstraints(const std::string& name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    bus_var_name = name;
    // from eqn 33 - 38, it seems that we should have 6 * Is constraints for bus
    SetRows(6 * bus_var_ptr->Is);
}

BusConstraints::~BusConstraints(){}

Eigen::VectorXd BusConstraints::GetValues() const
{
    // this GetRows() should return the number of constraints we set in the constructor
    Eigen::VectorXd bus_cons(GetRows());
    // these four has lower bound 0 and upper bound +inf
    Eigen::VectorXd p_ik_plus = bus_var_ptr->p_ikn_plus.colwise().sum();
    Eigen::VectorXd p_ik_minus =  bus_var_ptr->p_ikn_minus.colwise().sum();
    Eigen::VectorXd q_ik_plus = bus_var_ptr->q_ikn_plus.colwise().sum();
    Eigen::VectorXd q_ik_minus = bus_var_ptr->q_ikn_minus.colwise().sum();
    // now the more complicated ones, equation 35 and 38
    // just to be sure initlize them to zero first
    Eigen::VectorXd eq35 = Eigen::VectorXd::Zero(bus_var_ptr->Is);
    Eigen::VectorXd eq38 = Eigen::VectorXd::Zero(bus_var_ptr->Is);

    for (size_t idx=0; idx<eq35.size(); idx++)
    {

    }


    return bus_cons;

}

BusConstraints::VecBound BusConstraints::GetBounds() const
{
    VecBound bus_con_bounds(GetRows());
    return bus_con_bounds;

}

void BusConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    bus_var_ptr = x->GetComponent<BusVariables>(bus_var_name);
}
void BusConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}