#ifndef __LOAD_VARIABLES_HPP__
#define __LOAD_VARIABLES_HPP__
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>

class LoadVariables : public ifopt::VariableSet 
{
    LoadVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~LoadVariables();
    VectorXd GetValues() const override;
    void SetVariables(const VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    std::shared_ptr<Wrapper_Construct> data_fvariable;
    


};
#endif
