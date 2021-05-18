//
// Created by wchen on 2/26/21.
//

#ifndef GOC_CPP_TRANSFORMER_COSTS_CON_HPP
#define GOC_CPP_TRANSFORMER_COSTS_CON_HPP
#include <ifopt/cost_term.h>
#include <variables/transformer_variables_con.hpp>


class TransformerCostsCon : public ifopt::CostTerm {
public:
    TransformerCostsCon(const std::string& name);
    ~TransformerCostsCon();
    double GetCost () const override;

private:
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string trans_var_name;
    std::shared_ptr<TransformerVariablesCon> trans_var_ptr ;

};

#endif //GOC_CPP_TRANSFORMER_COSTS_CON_HPP
