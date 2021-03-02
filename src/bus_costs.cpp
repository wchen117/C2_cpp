#include <costs/bus_costs.hpp>

BusCosts::BusCosts(const std::string& name) : CostTerm(name + "_obj") 
{
    bus_var_name = name;  
}

BusCosts::~BusCosts() {}


double BusCosts::GetCost () const
{
    double z_ik = 0.0;
    auto tmp1 = bus_var_ptr->c_n_p.array() * (bus_var_ptr->p_ikn_plus.array() + bus_var_ptr->p_ikn_minus.array());
    auto tmp2 = bus_var_ptr->c_n_q.array() * (bus_var_ptr->q_ikn_plus.array() + bus_var_ptr->q_ikn_minus.array());
    z_ik = -1 * (tmp1 + tmp2).sum();
    return z_ik;



}

void BusCosts::InitVariableDependedQuantities (const VariablesPtr& x)
{
    bus_var_ptr = x->GetComponent<BusVariables>(bus_var_name);

}
void BusCosts::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{
    if (var_set == bus_var_name)
    {

        Eigen::VectorXd tmp_coeff(bus_var_ptr->bus_var_len);
        Eigen::Map<const Eigen::VectorXd> flat_c_n_p (bus_var_ptr->c_n_p.data(), bus_var_ptr->c_n_p.size());
        Eigen::Map<const Eigen::VectorXd> flat_c_n_q (bus_var_ptr->c_n_q.data(), bus_var_ptr->c_n_q.size());
        tmp_coeff << -1 * flat_c_n_p, -1 * flat_c_n_p, -1 * flat_c_n_q, -1 * flat_c_n_q;
        for (size_t idx=0; idx<tmp_coeff.size(); idx++)
        {
            jac.coeffRef(0, idx) = tmp_coeff(idx);
        }


    }



}