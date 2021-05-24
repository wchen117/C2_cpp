//
// Created by wchen on 2/26/21.
//

#ifndef GOC_CPP_TRANSFORMER_COSTS_HPP
#define GOC_CPP_TRANSFORMER_COSTS_HPP
#include <ifopt/cost_term.h>
#include <variables/transformer_variables.hpp>


class TransformerCosts : public ifopt::CostTerm {
public:
    TransformerCosts(const std::string& name);
    ~TransformerCosts();
    double GetCost () const override;

private:
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string trans_var_name;
    std::shared_ptr<TransformerVariables> trans_var_ptr ;
    double epsilon = 1e-4;

};

#endif //GOC_CPP_TRANSFORMER_COSTS_HPP
