#ifndef __BUSCONSTRAINTS_HPP__
#define __BUSCONSTRAINTS_HPP__
#include <ifopt/constraint_set.h>
#include <variables/bus_variables.hpp>

class BusConstraints : public ifopt::ConstraintSet {
public:
    BusConstraints(const std::string& name);
    ~BusConstraints();
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
private:
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    std::string bus_var_name;
    std::shared_ptr<BusVariables> bus_var_ptr;



};

#endif