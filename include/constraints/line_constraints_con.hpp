//
// Created by wchen on 3/17/21.
//

#ifndef GOC_CPP_LINE_CONSTRAINTS_CON_HPP
#define GOC_CPP_LINE_CONSTRAINTS_CON_HPP
#include <ifopt/constraint_set.h>
#include <variables/line_variables_con.hpp>
#include <variables/bus_variables_con.hpp>
#include <wrapper_construct.hpp>

class LineConstraintsCon : public ifopt::ConstraintSet
{
public:
    LineConstraintsCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name);
    ~LineConstraintsCon();
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;

private:
    void FillJacobianBlock(std::string var_set, Jacobian &jac_block) const override;
    void InitVariableDependedQuantities(const VariablesPtr &x) override;

    // the name for the corresponding load variable set
    std::string line_var_name;
    std::shared_ptr<LineVariablesCon> line_var_ptr;
    std::shared_ptr<BusVariablesCon> bus_var_ptr;




};
#endif //GOC_CPP_LINE_CONSTRAINTS_HPP
