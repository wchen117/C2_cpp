#include <constraints/bus_constraints.hpp>
BusConstraints::BusConstraints(const std::string& name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    bus_var_name = name;
    // from eqn 33 - 38, it seems that we should have 6 * Is constraints for bus
    //bus_cons_size = 6 * bus_var_ptr->bus_ref_data->Is;
    SetRows(96);
}

BusConstraints::~BusConstraints(){}

Eigen::VectorXd BusConstraints::GetValues() const
{
    // this GetRows() should return the number of constraints we set in the constructor
    Eigen::VectorXd bus_cons(GetRows());
    // these four has lower bound 0 and upper bound +inf
    Eigen::VectorXd p_ik_plus = bus_var_ptr->p_ikn_plus.colwise().sum();
    Eigen::VectorXd p_ik_minus = bus_var_ptr->p_ikn_minus.colwise().sum();
    Eigen::VectorXd q_ik_plus = bus_var_ptr->q_ikn_plus.colwise().sum();
    Eigen::VectorXd q_ik_minus = bus_var_ptr->q_ikn_minus.colwise().sum();
    // now the more complicated ones, equation 35 and 38
    // just to be sure initlize them to zero first
    Eigen::VectorXd eq35 = Eigen::VectorXd::Zero(bus_var_ptr->Is);
    Eigen::VectorXd eq38 = Eigen::VectorXd::Zero(bus_var_ptr->Is);

    // g in both G_i and G_k
    std::vector<int> g_Gi_Gk;
    FindCommon(bus_var_ptr->bus_ref_data->G_i,bus_var_ptr->bus_ref_data->G_k,  g_Gi_Gk);
    // j in both J_i and J_k
    std::vector<int> j_Ji_Jk;
    FindCommon(bus_var_ptr->bus_ref_data->J_i, bus_var_ptr->bus_ref_data->J_k, j_Ji_Jk);
    // e in both E_i_o and E_k
    std::vector<int> e_Eio_Ek;
    FindCommon(bus_var_ptr->bus_ref_data->E_i_o, bus_var_ptr->bus_ref_data->E_k, e_Eio_Ek);
    // e in both E_i_d and E_k;
    std::vector<int> e_Eid_Ek;
    FindCommon(bus_var_ptr->bus_ref_data->E_i_d, bus_var_ptr->bus_ref_data->E_k, e_Eid_Ek);
    // f in both f_i_o and F_k;
    std::vector<int> f_Fio_Fk;
    FindCommon(bus_var_ptr->bus_ref_data->F_i_o, bus_var_ptr->bus_ref_data->F_k, f_Fio_Fk);
    // f in both F_i_d and F_k;
    std::vector<int> f_Fid_Fk;
    FindCommon(bus_var_ptr->bus_ref_data->F_i_d, bus_var_ptr->bus_ref_data->F_k, f_Fid_Fk);

    //std::cout<<eq35.transpose()<<std::endl;
    for(auto f: f_Fid_Fk)
    {
        std::cout<<f<<std::endl;
    }








    return bus_cons;

}






BusConstraints::VecBound BusConstraints::GetBounds() const
{
    VecBound bus_con_bounds(GetRows());
    return bus_con_bounds;

}

void BusConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    bus_var_ptr = x->GetComponent<BusVariables>(bus_var_name);
}
void BusConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}