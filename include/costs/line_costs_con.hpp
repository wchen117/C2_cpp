//
// Created by wchen on 5/12/21.
//

#ifndef GOC_CPP_LINE_COSTS_CON_HPP
#define GOC_CPP_LINE_COSTS_CON_HPP
#include <ifopt/cost_term.h>
#include <variables/line_variables_con.hpp>
//#include <variables/load_variables.hpp>
class LineCostsCon : public ifopt::CostTerm{
public:
    LineCostsCon(const std::string& name);
    ~LineCostsCon();
    double GetCost () const override;

private:
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string line_var_name;
    std::shared_ptr<LineVariablesCon> line_var_ptr;
    //std::shared_ptr<LoadVariables> load_var_ptr;

};
#endif //GOC_CPP_LINE_COSTS_CON_HPP
