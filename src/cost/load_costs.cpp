#include <costs/load_costs.hpp>

LoadCosts::LoadCosts(const std::string& name) : CostTerm(name + "_obj")
{
    load_var_name = name;  
    
}

LoadCosts::~LoadCosts() {}

double LoadCosts::GetCost() const
{
    //Eigen::VectorXd x = ifopt::ConstraintSet::GetVariables()->GetComponent("load_variables")->GetValues();
    //auto load_var_ptr = ifopt::ConstraintSet::GetVariables()->GetComponent<LoadVariables>(load_var_name);
    double z_jk=0;
    size_t num_j = load_var_ptr->p_jkn.size();
    for (size_t idx=0; idx<num_j; idx++)
    {
        size_t num_n = load_var_ptr->p_jkn.at(idx).size();
        for (size_t jdx=0; jdx<num_n; jdx++)
        {
            auto tmp1 = load_var_ptr->p_jkn.at(idx).at(jdx) * load_var_ptr->load_ref_data->new_data.sup.sys_prms["delta"] * load_var_ptr->c_jn.at(idx).at(jdx);
            z_jk += tmp1;
        }
    }

    return -z_jk;
}
void LoadCosts::InitVariableDependedQuantities(const VariablesPtr& x)
{
    load_var_ptr = x->GetComponent<LoadVariables>(load_var_name);

}
void LoadCosts::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{
    if (var_set == load_var_name)
    {
        
        auto const& delta = load_var_ptr->load_ref_data->new_data.sup.sys_prms["delta"];

        size_t num_j = load_var_ptr->c_jn.size();
        size_t counter = 0;
        for (size_t idx=0; idx<num_j; idx++)
        {
            size_t num_n = load_var_ptr->c_jn.at(idx).size();
            for (size_t jdx=0; jdx<num_n; jdx++)
            {
                auto tmp_c = load_var_ptr->c_jn.at(idx).at(jdx);
                jac.coeffRef(0, counter) = - tmp_c * delta;
                //jac.coeffRef(0, counter) = 1e5;
                counter++;
            }
        }

        for (size_t idx=0; idx<jac.cols(); idx++)
        {
            //std::cout<<jac.coeff(0, idx)<<std::endl;
        }
        
    }





}
