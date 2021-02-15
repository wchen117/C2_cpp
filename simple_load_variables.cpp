#include <variables/load_variables.hpp>

LoadVariables::LoadVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(-1, name)
{
    x0_ = 3.5;
    x1_ = 1.5;
    SetRows(2);
    

}
LoadVariables::~LoadVariables() {}

Eigen::VectorXd LoadVariables::GetValues() const 
{
    return Eigen::Vector2d(x0_, x1_);
    
    
}
void LoadVariables::SetVariables(const Eigen::VectorXd &x)  
{
    x0_ = x(0);
    x1_ = x(1);
}
LoadVariables::VecBound LoadVariables::GetBounds() const 
{
    VecBound bounds(GetRows());
    bounds.at(0) = ifopt::Bounds(-1.0, 1.0);
    bounds.at(1) = ifopt::NoBound;
    return bounds;
}
