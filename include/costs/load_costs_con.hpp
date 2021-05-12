//
// Created by wchen on 5/12/21.
//

#ifndef GOC_CPP_LOAD_COSTS_CON_HPP
#define GOC_CPP_LOAD_COSTS_CON_HPP
#include <ifopt/cost_term.h>
#include <variables/load_variables.hpp>


class LoadCostsCon : public ifopt::CostTerm {
public:
    LoadCostsCon(const std::string& name);
    ~LoadCostsCon();
    double GetCost () const override;

private:
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string load_var_name;
    std::shared_ptr<LoadVariables> load_var_ptr;

};
#endif //GOC_CPP_LOAD_COSTS_CON_HPP
