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
    auto first_term = -(trans_var_ptr->x_fk_sw - trans_var_ptr->x_f_sw0).array().abs() * (trans_var_ptr->c_f_sw.array());
    auto second_term = -(trans_var_ptr->s_fnk_plus.array() * trans_var_ptr->c_n_s.array()).matrix().colwise().sum();
    double z_ek = 0.0;
    for (size_t idx=0; idx< first_term.rows(); idx++)
    {
        z_ek += trans_var_ptr->local_input_ptr->new_data.sup.sys_prms["delta"] * second_term(idx) + first_term(idx);
    }
    return z_ek;

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

