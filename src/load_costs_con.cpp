//
// Created by wchen on 5/12/21.
//
#include <costs/load_costs_con.hpp>

LoadCostsCon::LoadCostsCon(const std::string& name) : CostTerm(name + "_obj")
{
    load_var_name = name;

}

LoadCostsCon::~LoadCostsCon() {}

double LoadCostsCon::GetCost() const
{
    //Eigen::VectorXd x = ifopt::ConstraintSet::GetVariables()->GetComponent("load_variables")->GetValues();
    //auto load_var_ptr = ifopt::ConstraintSet::GetVariables()->GetComponent<LoadVariables>(load_var_name);
    auto const& delta_ct = load_var_ptr->load_ref_data->new_data.sup.sys_prms["deltactg"];
    double z_jk=0;
    size_t num_j = load_var_ptr->p_jkn.size();
    for (size_t idx=0; idx<num_j; idx++)
    {
        size_t num_n = load_var_ptr->p_jkn.at(idx).size();
        for (size_t jdx=0; jdx<num_n; jdx++)
        {
            z_jk += delta_ct * load_var_ptr->p_jkn.at(idx).at(jdx) * load_var_ptr->c_jn.at(idx).at(jdx);
        }
    }

    return -z_jk;
}
void LoadCostsCon::InitVariableDependedQuantities(const VariablesPtr& x)
{
    load_var_ptr = x->GetComponent<LoadVariablesCon>(load_var_name);

}
void LoadCostsCon::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{
    if (var_set == load_var_name)
    {
        auto const& delta_ct = load_var_ptr->load_ref_data->new_data.sup.sys_prms["deltactg"];

        size_t num_j = load_var_ptr->c_jn.size();
        size_t counter = 0;
        for (size_t idx=0; idx<num_j; idx++)
        {
            size_t num_n = load_var_ptr->c_jn.at(idx).size();
            for (size_t jdx=0; jdx<num_n; jdx++)
            {
                auto tmp_c = load_var_ptr->c_jn.at(idx).at(jdx);
                jac.coeffRef(0, counter) = - tmp_c * delta_ct;
                counter++;
            }
        }
    }





}
