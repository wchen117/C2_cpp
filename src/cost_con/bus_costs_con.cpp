//
// Created by wchen on 5/12/21.
//
#include <costs/bus_costs_con.hpp>
BusCostsCon::BusCostsCon(const std::string& name) : CostTerm(name + "_obj")
{
    bus_var_name = name;
}

BusCostsCon::~BusCostsCon() {}


double BusCostsCon::GetCost () const
{
    //Eigen::VectorXd x = ifopt::ConstraintSet::GetVariables()->GetComponent(bus_var_name)->GetValues();
    //auto bus_var_ptr = ifopt::ConstraintSet::GetVariables()->GetComponent<BusVariables>(bus_var_name);
    double z_ik = 0.0;
    auto const& delta_ct = bus_var_ptr->bus_ref_data->new_data.sup.sys_prms["deltactg"];

    // transform MatrixXd or VectorXd object to their array representation for element wise calcs, no additional cost
    auto tmp1 = bus_var_ptr->c_n_p.array() * (bus_var_ptr->p_ikn_plus.array() + bus_var_ptr->p_ikn_minus.array());
    auto tmp2 = bus_var_ptr->c_n_q.array() * (bus_var_ptr->q_ikn_plus.array() + bus_var_ptr->q_ikn_minus.array());
    z_ik = -1 * (tmp1 + tmp2).sum();

    return -z_ik;



}

void BusCostsCon::InitVariableDependedQuantities (const VariablesPtr& x)
{
    bus_var_ptr = x->GetComponent<BusVariablesCon>(bus_var_name);

}
void BusCostsCon::FillJacobianBlock(std::string var_set, Jacobian& jac) const
{
    //auto bus_var_ptr = ifopt::ConstraintSet::GetVariables()->GetComponent<BusVariables>(bus_var_name);
    if (var_set == bus_var_name)
    {

        Eigen::VectorXd tmp_coeff(bus_var_ptr->bus_var_len);
        Eigen::Map<const Eigen::VectorXd> flat_c_n_p (bus_var_ptr->c_n_p.data(), bus_var_ptr->c_n_p.size());
        Eigen::Map<const Eigen::VectorXd> flat_c_n_q (bus_var_ptr->c_n_q.data(), bus_var_ptr->c_n_q.size());
        // there are v_ik and theta_ik in bus_variables as well, both of length Is
        Eigen::VectorXd zero_vec = Eigen::VectorXd::Zero(2 * bus_var_ptr->Is);
        tmp_coeff << flat_c_n_p, flat_c_n_p,  flat_c_n_q, flat_c_n_q, zero_vec;
        for (size_t idx=0; idx<tmp_coeff.size(); idx++)
        {
            jac.coeffRef(0, idx) = tmp_coeff(idx);
        }


    }



}