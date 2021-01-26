#include <variables.hpp>

GocVariables::GocVariables(int n_var, const std::string& name) : VariableSet(n_var, name) 
{    
}
GocVariables::~GocVariables(){}

VectorXd GocVariables::GetValues() const 
{
    
    

}

void GocVariables::SetVariables(const VectorXd &x) {}

GocVariables::VecBound GocVariables::GetBounds() const {}

void GocVariables::ReadinData(const Wrapper_Construct& model_data) 
{
     

}


