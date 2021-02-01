#include <bus_variables.hpp>
using Eigen::Vector2d;
#include "Eigen/Dense"
#include "Eigen/Core"

BusVariables::BusVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(kSpecifyLater, name) 
{    
    // use kSpecifyLater since we need to figure out how many variables in bus_variables
    data_fvariable = data_ptr;
    // number of rows (variables must be set within the constructor)
    // here we need to figure out the number of variables/rows in this variable set
    // and set their initial values
    size_p_ikn = data_fvariable->Is * data_fvariable->Np;
    size_q_ikn = data_fvariable->Is * data_fvariable->Nq;
    // bus variables consist of p_ikn+, p_ikn-, q_ikn+, q_ikn-, z_ik (?)
    size_bus_variables = 2 * size_q_ikn + 2 * size_p_ikn + 1;
    SetRows(size_bus_variables);
    // initlize them to 0?
    if (size_p_ikn && size_q_ikn)
    {
        p_ikn_plus = VectorXd::Zero(size_p_ikn);
        p_ikn_minus = VectorXd::Zero(size_p_ikn);
        q_ikn_plus = VectorXd::Zero(size_q_ikn);
        q_ikn_minus = VectorXd::Zero(size_q_ikn);
        z_ik = 0.0;
    }
    

    
}
BusVariables::~BusVariables(){}

VectorXd BusVariables::GetValues() const 
{
    // why rows = number of variables????
    if  (GetRows())
    {
        return VectorXd(GetRows());
    }
    
}

void BusVariables::SetVariables(const VectorXd &x) 
{
    p_ikn_plus = x(Eigen::seq(0, size_p_ikn));
    p_ikn_minus = x(Eigen::seq(size_p_ikn, 2*size_p_ikn));
    q_ikn_plus = x(Eigen::seq(2*size_p_ikn, 2*size_p_ikn+size_q_ikn));
    q_ikn_minus = x(Eigen::seq(2*size_p_ikn+size_q_ikn, 2*size_p_ikn+2*size_q_ikn));
    z_ik = x(2*size_p_ikn+2*size_q_ikn+1);

   
}

BusVariables::VecBound BusVariables::GetBounds() const 
{
    
    VecBound bounds(GetRows());

    
    return bounds;
}


