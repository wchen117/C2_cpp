#ifndef __LOAD_COSTS_HPP__
#define __LOAD_COSTS_HPP__
#include <ifopt/cost_term.h>
#include <variables/load_variables.hpp>
#include <variables/bus_variables.hpp>

class LoadCosts : public ifopt::CostTerm {
public:
    LoadCosts(const std::string& name);
    ~LoadCosts();
    double GetCost () const override;
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
private: 
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string load_var_name;
    //std::shared_ptr<LoadVariables> load_var_ptr;
    //std::shared_ptr<BusVariables> bus_var_ptr;
};

#endif