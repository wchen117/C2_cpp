//
// Created by wchen on 3/17/21.
//

#include <constraints/line_constraints.hpp>

LineConstraints::LineConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    line_var_name = name;
    SetRows(4 * data_ptr->E_k.size());
}
LineConstraints::~LineConstraints() {}

Eigen::VectorXd LineConstraints::GetValues() const
{
    Eigen::VectorXd line_cons(GetRows());

    /**
    for (ieo_key: line_var_ptr->local_input_ptr->i_e_o)
    {
        for (ied_key: line_var_ptr->local_input_ptr->i_e_d)
        {

        }

    }
     **/


    return line_cons;
}

LineConstraints::VecBound LineConstraints::GetBounds() const
{
    VecBound line_con_bounds(GetRows());
    return line_con_bounds;
}void LineConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    line_var_ptr = x->GetComponent<LineVariables>(line_var_name);
}
void LineConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}




