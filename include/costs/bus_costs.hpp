#ifndef __BUS_COSTS_HPP__
#define __BUS_COSTS_HPP__
#include <ifopt/cost_term.h>
#include <variables/bus_variables.hpp>

class BusCosts : public ifopt::CostTerm {
public:
    BusCosts(const std::string& name);
    ~BusCosts();
    double GetCost () const override;
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
private: 
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string bus_var_name;
    std::shared_ptr<BusVariables> bus_var_ptr;


    
};
#endif