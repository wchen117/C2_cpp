#include <variables_all.hpp>
#include <iostream>

VariablesAll::VariablesAll(std::shared_ptr<Wrapper_Construct> data_ptr, int n_var, const std::string& name) : GocVariables(n_var, name)
{
       
}
VariablesAll::~VariablesAll()
{

}
