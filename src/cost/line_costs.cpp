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


    auto first_term = -(((line_var_ptr->x_ek_sw - line_var_ptr->x_e_sw0).array().pow(2) + epsilon).sqrt()).array() * (line_var_ptr->c_e_sw.array());
    //auto first_term = -(line_var_ptr->x_ek_sw - line_var_ptr->x_e_sw0).array().abs() * (line_var_ptr->c_e_sw.array());
    // second_term is a row vector
    auto second_term = -(line_var_ptr->s_enk_plus.array() * line_var_ptr->c_n_s.array()).matrix().colwise().sum();
    const auto &alpha = line_var_ptr->local_input_ptr->alpha_factor;
    auto third_term = (alpha * (line_var_ptr->x_ek_sw.array() * (1.0 - line_var_ptr->x_ek_sw.array()))).matrix();
    auto delta = line_var_ptr->local_input_ptr->new_data.sup.sys_prms["delta"];


    //std::cout<<"c_n_s = "<<line_var_ptr->c_n_s<<std::endl;
    //std::cout<<"s_enk_plus = "<<line_var_ptr->s_enk_plus<<std::endl;
    double z_ek = 0.0;
    for (size_t idx=0; idx< first_term.rows(); idx++)
    {
        z_ek +=  delta * second_term(idx) + first_term(idx) + third_term(idx);
        //z_ek +=  delta * second_term(idx) + first_term(idx) ;
    }
    return -z_ek;

}
void LineCosts::InitVariableDependedQuantities(const VariablesPtr& x)
{
    line_var_ptr = x->GetComponent<LineVariables>(line_var_name);

}

void LineCosts::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{
    if (var_set == line_var_name)
    {
        Eigen::VectorXd eqn17_der_1 = ((line_var_ptr->x_ek_sw.array() - line_var_ptr->x_e_sw0.array()) / ((line_var_ptr->x_ek_sw.array() - line_var_ptr->x_e_sw0.array()).pow(2) + epsilon).sqrt()).matrix();
        Eigen::VectorXd zero_vec = Eigen::VectorXd::Zero(line_var_ptr->size_E_k0);
        Eigen::Map<const Eigen::VectorXd> flat_cns(line_var_ptr->c_n_s.data(), line_var_ptr->c_n_s.size());
        assert(jac.cols() == line_var_ptr->line_var_len);
        Eigen::VectorXd eqn17_jac = Eigen::VectorXd::Zero(line_var_ptr->line_var_len);
        eqn17_jac << flat_cns, eqn17_der_1, zero_vec, zero_vec, zero_vec ,zero_vec;

        for (size_t idx=0; idx<jac.cols(); idx++)
        {
            jac.coeffRef(0, idx) = eqn17_jac(idx);
            //jac.coeffRef(0, idx) = 0.0;
        }



    }








}