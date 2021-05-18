//
// Created by wchen on 3/29/21.
//

#ifndef GOC_CPP_TRANSFORMER_CONSTRAINTS_CON_HPP
#define GOC_CPP_TRANSFORMER_CONSTRAINTS_CON_HPP
#include <ifopt/constraint_set.h>
#include <variables/transformer_variables_con.hpp>
#include <wrapper_construct.hpp>
class TransConstraintsCon : public ifopt::ConstraintSet {
public:
    TransConstraintsCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::shared_ptr<TransformerVariablesCon> trans_var_ptr, const std::string &name);

    ~TransConstraintsCon();

    VectorXd GetValues() const override;
    VecBound GetBounds() const override;



private:
    void FillJacobianBlock(std::string var_set, Jacobian &jac_block) const override;

    void InitVariableDependedQuantities(const VariablesPtr &x) override;

    // the name for the corresponding load variable set
    std::string trans_var_name;
    std::shared_ptr<TransformerVariablesCon> trans_var_ptr;
};
#endif //GOC_CPP_TRANSFORMER_CONSTRAINTS_CON_HPP
