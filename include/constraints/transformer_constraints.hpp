//
// Created by wchen on 3/29/21.
//

#ifndef GOC_CPP_TRANSFORMER_CONSTRAINTS_HPP
#define GOC_CPP_TRANSFORMER_CONSTRAINTS_HPP
#include <ifopt/constraint_set.h>
#include <variables/transformer_variables.hpp>
#include <wrapper_construct.hpp>
class TransConstraints : public ifopt::ConstraintSet {
public:
    TransConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name);

    ~TransConstraints();

    VectorXd GetValues() const override;

    VecBound GetBounds() const override;


private:
    void FillJacobianBlock(std::string var_set, Jacobian &jac_block) const override;

    void InitVariableDependedQuantities(const VariablesPtr &x) override;

    // the name for the corresponding load variable set
    std::string trans_var_name;
    std::shared_ptr<LoadVariables> trans_var_ptr;
};
#endif //GOC_CPP_TRANSFORMER_CONSTRAINTS_HPP
