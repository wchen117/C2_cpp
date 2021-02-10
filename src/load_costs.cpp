#include <costs/load_costs.hpp>

LoadCosts::LoadCosts(const std::string& name) : CostTerm(name + "_obj") 
{
    load_var_name = name;  
    
}

LoadCosts::~LoadCosts() {}

double LoadCosts::GetCost() const 
{
    /**
    double z_jk=0;
    size_t num_j = load_var_ptr->p_jkn.size();
    for (size_t idx=0; idx<num_j; idx++)
    {
        size_t num_n = load_var_ptr->p_jkn.at(idx).size();
        for (size_t jdx=0; jdx<num_n; jdx++)
        {
            z_jk += load_var_ptr->p_jkn.at(idx).at(jdx) * load_var_ptr->c_jn.at(idx).at(jdx) * load_var_ptr->load_ref_data->new_data.sup.sys_prms["delta"];
        }
    }
    **/
    

    return 0.0;
}
void LoadCosts::InitVariableDependedQuantities(const VariablesPtr& x) 
{
    //load_var_ptr = x->GetComponent<LoadVariables>(load_var_name);

}
void LoadCosts::FillJacobianBlock(std::string var_set, Jacobian&) const
{

}