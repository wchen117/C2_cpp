//
// Created by wchen on 3/11/21.
//

#ifndef GOC_CPP_LOAD_CONSTRAINTS_HPP
#define GOC_CPP_LOAD_CONSTRAINTS_HPP
#include <ifopt/constraint_set.h>
#include <variables/load_variables.hpp>
#include <wrapper_construct.hpp>
class LoadConstraints : public ifopt::ConstraintSet {
public:
    LoadConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name);

    ~LoadConstraints();

    VectorXd GetValues() const override;

    VecBound GetBounds() const override;


private:
    void FillJacobianBlock(std::string var_set, Jacobian &jac_block) const override;

    void InitVariableDependedQuantities(const VariablesPtr &x) override;

    // the name for the corresponding load variable set
    std::string load_var_name;
    std::shared_ptr<LoadVariables> load_var_ptr;
};
#endif //GOC_CPP_LOAD_CONSTRAINTS_HPP
