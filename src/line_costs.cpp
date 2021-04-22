//
// Created by wchen on 2/23/21.
//
#include "costs/line_costs.hpp"
LineCosts::LineCosts(const std::string& name) : CostTerm(name + "_obj")
{
    line_var_name = name;
}
LineCosts::~LineCosts()
{

}
double LineCosts::GetCost() const
{

    // first_term is a column vector
    auto first_term = -(line_var_ptr->x_ek_sw - line_var_ptr->x_e_sw0).array().abs() * (line_var_ptr->c_e_sw.array());
    // second_term is a row vector
    auto second_term = -(line_var_ptr->s_enk_plus.array() * line_var_ptr->c_n_s.array()).matrix().colwise().sum();
    auto delta = line_var_ptr->local_input_ptr->new_data.sup.sys_prms["delta"];


    std::cout<<"c_n_s = "<<line_var_ptr->c_n_s<<std::endl;
    std::cout<<"s_enk_plus = "<<line_var_ptr->s_enk_plus<<std::endl;
    double z_ek = 0.0;
    for (size_t idx=0; idx< first_term.rows(); idx++)
    {
        z_ek +=  delta * second_term(idx) + first_term(idx);
    }
    return z_ek;

}
void LineCosts::InitVariableDependedQuantities(const VariablesPtr& x)
{
    line_var_ptr = x->GetComponent<LineVariables>(line_var_name);

}

void LineCosts::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{
    if (var_set == line_var_name)
    {
        Eigen::Map<Eigen::VectorXd> flat_c_ns(line_var_ptr->c_n_s.data(), line_var_ptr->c_n_s.size());
        flat_c_ns *= -1;
        Eigen::VectorXd x_ek_sw_coeff (line_var_ptr->size_E_k0);

        for (size_t idx=0; idx<line_var_ptr->size_E_k0; idx++)
        {
            if (line_var_ptr->x_ek_sw(idx) >= line_var_ptr->x_e_sw0(idx))
            {
                x_ek_sw_coeff(idx) = - line_var_ptr->c_e_sw(idx);
            }
            else {
                x_ek_sw_coeff(idx) = line_var_ptr->c_e_sw(idx);

            }
        }
        Eigen::VectorXd tmp(line_var_ptr->line_var_len);
        tmp<< flat_c_ns, x_ek_sw_coeff;
        for (size_t idx=0; idx<line_var_ptr->line_var_len; idx++)
        {
            jac.coeffRef(0, idx) = tmp(idx);

        }

    }








}