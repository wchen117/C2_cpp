//
// Created by wchen on 2/26/21.
//
#include <costs/transformer_costs.hpp>
TransformerCosts::TransformerCosts(const std::string& name) : CostTerm(name + "_obj")
{
    trans_var_name = name;
}
TransformerCosts::~TransformerCosts()
{

}
double TransformerCosts::GetCost() const
{
    auto first_term = -1.0 * (trans_var_ptr->x_fk_sw - trans_var_ptr->x_f_sw0).array().abs() * (trans_var_ptr->c_f_sw.array());
    auto second_term = -1.0 * (trans_var_ptr->s_fnk_plus.array() * trans_var_ptr->c_n_s.array()).matrix().colwise().sum();
    auto delta = trans_var_ptr->local_input_ptr->new_data.sup.sys_prms["delta"];
    auto const &alpha = trans_var_ptr->local_input_ptr->alpha_factor;

    auto third_term = (alpha * (trans_var_ptr->x_fk_sw.array() * (1.0 - trans_var_ptr->x_fk_sw.array()))).matrix();
    auto fourth_term = (alpha * (trans_var_ptr->eq70_binary_variable.array() * (1.0 - trans_var_ptr->eq70_binary_variable.array()))).matrix();
    auto fifth_term = (alpha * (trans_var_ptr->eq71_binary_variable.array() * (1.0 - trans_var_ptr->eq71_binary_variable.array()))).matrix();


    double z_ek = 0.0;
    for (size_t idx=0; idx< first_term.rows(); idx++)
    {
        z_ek += delta * second_term(idx) + first_term(idx) + third_term(idx);
    }

    if (fourth_term.size() > 0)
    {
        for (size_t idx=0; idx< fourth_term.rows(); idx++)
        {
            z_ek += fourth_term(idx);
        }
    }
    else if (fifth_term.size() > 0)
    {
        for (size_t idx=0; idx< fifth_term.rows(); idx++)
        {
            z_ek += fifth_term(idx);
        }
    }
    //std::cout<<"first_term = "<<first_term.transpose()<<std::endl;
    //std::cout<<"second_term = "<<second_term<<std::endl;
    //std::cout<<"c_n_s = "<<trans_var_ptr->c_n_s<<std::endl;
    //std::cout<<"s_fnk_plus = "<<trans_var_ptr->s_fnk_plus<<std::endl;




    return -z_ek;

}
void TransformerCosts::InitVariableDependedQuantities(const VariablesPtr& x)
{
    trans_var_ptr = x->GetComponent<TransformerVariables>(trans_var_name);

}

void TransformerCosts::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{
    if (var_set == trans_var_name)
    {
        Eigen::Map<Eigen::VectorXd> flat_c_ns(trans_var_ptr->c_n_s.data(), trans_var_ptr->c_n_s.size());
        flat_c_ns *= -1;
        Eigen::VectorXd x_fk_sw_coeff (trans_var_ptr->size_F_k0);

        for (size_t idx=0; idx<trans_var_ptr->size_F_k0; idx++)
        {
            if (trans_var_ptr->x_fk_sw(idx) >= trans_var_ptr->x_fk_sw(idx))
            {
                x_fk_sw_coeff(idx) = - trans_var_ptr->c_f_sw(idx);
            }
            else {
                x_fk_sw_coeff(idx) = trans_var_ptr->c_f_sw(idx);

            }
        }
        Eigen::VectorXd tmp(trans_var_ptr->trans_var_len);
        tmp<< flat_c_ns, x_fk_sw_coeff;
        for (size_t idx=0; idx<trans_var_ptr->trans_var_len; idx++)
        {
            jac.coeffRef(0, idx) = tmp(idx);

        }

    }


}

