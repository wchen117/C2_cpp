#ifndef __LINE_COSTS_HPP__
#define __LINE_COSTS_HPP__
#include <ifopt/cost_term.h>
#include <variables/line_variables.hpp>
class LineCosts :: public ifopt::CostTerm{
public:
    LineCosts(const std::string& name);
    ~LineCosts();
    double GetCost () const override;
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
private:
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string line_var_name;

};
#endif