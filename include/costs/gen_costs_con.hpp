//
// Created by wchen on 3/2/21.
//

#ifndef GOC_CPP_GEN_COSTS_CON_HPP
#define GOC_CPP_GEN_COSTS_CON_HPP
#include <ifopt/cost_term.h>
#include <variables/generator_variables_con.hpp>

class GenCostsCon : public ifopt::CostTerm {
public:
    GenCostsCon(const std::string& name);
    ~GenCostsCon();
    double GetCost () const override;

private:
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string gen_var_name;
    std::shared_ptr<GeneratorVariablesCon> gen_var_ptr;

};
#endif //GOC_CPP_GEN_COSTS_HPP
