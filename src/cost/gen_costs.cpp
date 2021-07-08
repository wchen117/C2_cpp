//
// Created by wchen on 3/2/21.
//
#include "costs/gen_costs.hpp"

GenCosts::GenCosts(const std::string& name) : CostTerm(name + "_obj")
{
    gen_var_name = name;
}

GenCosts::~GenCosts(){}

double GenCosts::GetCost() const
{
    double z_gk = 0.0;
    // initilize it to zero and size of flattened p_gnk
    Eigen::VectorXd tmp_cp = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);
    for (size_t idx=0; idx<gen_var_ptr->size_G_k0; idx++) {
        for (size_t jdx = 0; jdx < gen_var_ptr->p_gnk.at(idx).size(); jdx++) {
            // always initialize vector to something before adding numbers to it
            tmp_cp(idx) += gen_var_ptr->p_gnk.at(idx).at(jdx) * gen_var_ptr->c_gn.at(idx).at(jdx);
        }
    }

    auto tmp1 = tmp_cp.array();
    auto tmp2 = gen_var_ptr->c_g_on.array() * gen_var_ptr->x_gk_on.array();
    auto tmp3 = gen_var_ptr->gen_ref_data->new_data.sup.sys_prms["delta"];
    auto tmp4 = gen_var_ptr->c_g_su.array() * gen_var_ptr->x_gk_su.array();
    auto tmp5 = gen_var_ptr->c_g_sd.array() * gen_var_ptr->x_gk_sd.array();
    auto const &alpha = gen_var_ptr->gen_ref_data->alpha_factor;
    Eigen::ArrayXd tmp6 = (alpha * (gen_var_ptr->x_gk_on.array() * (1.0 - gen_var_ptr->x_gk_on.array())));
    Eigen::ArrayXd tmp7 = (alpha * (gen_var_ptr->x_gk_sd.array() * (1.0 - gen_var_ptr->x_gk_sd.array())));
    Eigen::ArrayXd tmp8 = (alpha * (gen_var_ptr->x_gk_su.array() * (1.0 - gen_var_ptr->x_gk_su.array())));
    z_gk = -1 * ((tmp1 + tmp2) * tmp3 + tmp4 + tmp5 + tmp6 + tmp7 + tmp8).sum();
    //z_gk = -1 * ((tmp1 + tmp2) * tmp3 + tmp4 + tmp5).sum();

    return -z_gk;
}

void GenCosts::InitVariableDependedQuantities(const VariablesPtr& x)
{
    gen_var_ptr = x->GetComponent<GeneratorVariables>(gen_var_name);

}
void GenCosts::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{
    if (var_set == gen_var_name)
    {
        // GetRows() here returns the number of cost, which is one
        Eigen::VectorXd tmp(gen_var_ptr->gen_var_len);
        Eigen::VectorXd flat_c_gn(gen_var_ptr->size_p_gnk);
        Eigen::VectorXd gen_obj_wrt_q = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);
        size_t count = 0;
        for (size_t idx=0; idx<gen_var_ptr->size_G_k0; idx++)
        {
            for (size_t jdx=0; jdx<gen_var_ptr->c_gn.at(idx).size(); jdx++)
            {
                flat_c_gn(count) = gen_var_ptr->c_gn.at(idx).at(jdx);
                count++;
            }

        }

        auto const &alpha = gen_var_ptr->gen_ref_data->alpha_factor;

        tmp << -1 * flat_c_gn, gen_obj_wrt_q, -1 * gen_var_ptr->c_g_on.array() + alpha * (1.0 - 2.0 * gen_var_ptr->x_gk_on.array()), -1 * gen_var_ptr->c_g_su.array() + alpha * (1.0 - 2.0 * gen_var_ptr->x_gk_su.array()), -1 * gen_var_ptr->c_g_sd.array() + alpha * (1.0 - 2.0 * gen_var_ptr->x_gk_sd.array());

        for(size_t idx=0; idx<tmp.size(); idx++)
        {
            jac.coeffRef(0, idx) = tmp(idx);
        }



    }

}