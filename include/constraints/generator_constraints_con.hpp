//
// Created by wchen on 3/31/21.
//

#ifndef GOC_CPP_GENERATOR_CONSTRAINTS_CON_HPP
#define GOC_CPP_GENERATOR_CONSTRAINTS_CON_HPP
#include <ifopt/constraint_set.h>
#include <variables/generator_variables_con.hpp>
#include <wrapper_construct.hpp>
class GeneratorConstraintsCon : public ifopt::ConstraintSet {
public:
    GeneratorConstraintsCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name);

    ~GeneratorConstraintsCon();

    VectorXd GetValues() const override;

    VecBound GetBounds() const override;


private:
    void FillJacobianBlock(std::string var_set, Jacobian &jac_block) const override;

    void InitVariableDependedQuantities(const VariablesPtr &x) override;

    // the name for the corresponding load variable set
    std::string gen_var_name;
    std::shared_ptr<GeneratorVariablesCon> gen_var_ptr;
};

#endif //GOC_CPP_GENERATOR_CONSTRAINTS_HPP
