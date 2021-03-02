//
// Created by wchen on 3/2/21.
//

#ifndef GOC_CPP_GEN_COSTS_HPP
#define GOC_CPP_GEN_COSTS_HPP
#include <ifopt/cost_term.h>
#include <variables/generator_variables.hpp>

class GenCosts : public ifopt::CostTerm {
public:
    GenCosts(const std::string& name);
    ~GenCosts();
    double GetCost () const override;
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
private:
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string gen_var_name;
    std::shared_ptr<GeneratorVariables> gen_var_ptr;

};
#endif //GOC_CPP_GEN_COSTS_HPP
