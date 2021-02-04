#include <costs/bus_costs.hpp>

BusCosts::BusCosts(const std::string& name) : CostTerm(name) 
{
    bus_var_name = name;  
}

BusCosts::~BusCosts() {}

double BusCosts::GetCost () const
{
    std::vector<double> c_n_p_list;
    std::vector<double> c_n_q_list;
    double z_ik;

    std::cout<<bus_vars_ptr->p_ikn_plus<<std::endl;

    return 0;
}
void BusCosts::InitVariableDependedQuantities (const VariablesPtr& x)
{
    bus_vars_ptr = x->GetComponent<BusVariables>(bus_var_name);
}
void BusCosts::FillJacobianBlock(std::string var_set, Jacobian&) const
{

}