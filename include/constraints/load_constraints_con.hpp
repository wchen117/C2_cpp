//
// Created by wchen on 3/11/21.
//

#ifndef GOC_CPP_LOAD_CONSTRAINTS_CON_HPP
#define GOC_CPP_LOAD_CONSTRAINTS_CON_HPP
#include <ifopt/constraint_set.h>
#include <variables/load_variables_con.hpp>
#include <wrapper_construct.hpp>
class LoadConstraintsCon : public ifopt::ConstraintSet {
public:
    LoadConstraintsCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name);

    ~LoadConstraintsCon();

    VectorXd GetValues() const override;

    VecBound GetBounds() const override;


private:
    void FillJacobianBlock(std::string var_set, Jacobian &jac_block) const override;

    void InitVariableDependedQuantities(const VariablesPtr &x) override;

    // the name for the corresponding load variable set
    std::string load_var_name;
    std::shared_ptr<LoadVariablesCon> load_var_ptr;
};
#endif //GOC_CPP_LOAD_CONSTRAINTS_HPP
