#ifndef __VARIABLES_ALL_HPP__
#define __VARIABLES_ALL_HPP__
#include <variables.hpp>

class VariablesAll : public GocVariables
{
public:
    VariablesAll(std::shared_ptr<Wrapper_Construct> data_ptr, int n_var, const std::string& name);
    ~VariablesAll();

};

#endif