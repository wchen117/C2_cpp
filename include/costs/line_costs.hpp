//
// Created by wchen on 2/23/21.
//

#ifndef __LINE_COSTS_HPP__
#define __LINE_COSTS_HPP__
#include <ifopt/cost_term.h>
#include <variables/line_variables.hpp>
//#include <variables/load_variables.hpp>
class LineCosts : public ifopt::CostTerm{
public:
    LineCosts(const std::string& name);
    ~LineCosts();
    double GetCost () const override;

private:
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string line_var_name;
    std::shared_ptr<LineVariables> line_var_ptr;
    double epsilon = 1e-4;
    //std::shared_ptr<LoadVariables> load_var_ptr;

};
#endif
