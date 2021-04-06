#include <constraints/bus_constraints.hpp>
BusConstraints::BusConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    bus_var_name = name;
    //auto tmp_ptr = ifopt::ConstraintSet::GetVariables()->GetComponent<BusVariables>(bus_var_name);
    // from eqn 33 - 38, it seems that we should have 6 * Is constraints for bus
    auto bus_con_size = 6 * data_ptr->Is;
    bus_ref_data = data_ptr;
    SetRows(bus_con_size);

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

    Eigen::VectorXd gen_p_gk = gen_var_ptr->get_p_gk();
    Eigen::VectorXd load_p_jk = load_var_ptr->get_p_jk();
    Eigen::VectorXd load_q_jk = load_var_ptr->get_q_jk();

    // same sequence as every variables in generator variables
    // G_k0, vector
    double sum_p_gk = get_sum(bus_ref_data->G_k0, bus_ref_data->G_i, gen_p_gk);
    double sum_p_jk = get_sum(bus_ref_data->J_k0, bus_ref_data->J_i, load_p_jk);
    double sum_p_ek_o = get_sum(bus_ref_data->E_k0, bus_ref_data->E_i_o, line_var_ptr->p_ek_o);
    double sum_p_ek_d = get_sum(bus_ref_data->E_k0, bus_ref_data->E_i_d, line_var_ptr->p_ek_d);
    double sum_p_fk_o = get_sum(bus_ref_data->F_k0, bus_ref_data->F_i_o, trans_var_ptr->p_fk_o);
    double sum_p_fk_d = get_sum(bus_ref_data->F_k0, bus_ref_data->F_i_d, trans_var_ptr->p_fk_d);

    double sum_q_gk = get_sum(bus_ref_data->G_k0, bus_ref_data->G_i, gen_var_ptr->q_gk);
    double sum_q_jk = get_sum(bus_ref_data->J_k0, bus_ref_data->J_i, load_q_jk);
    double sum_q_ek_o = get_sum(bus_ref_data->E_k0, bus_ref_data->E_i_o, line_var_ptr->q_ek_o);
    double sum_q_ek_d = get_sum(bus_ref_data->E_k0, bus_ref_data->E_i_d, line_var_ptr->q_ek_d);
    double sum_q_fk_o = get_sum(bus_ref_data->F_k0, bus_ref_data->F_i_o, trans_var_ptr->q_fk_o);
    double sum_q_fk_d = get_sum(bus_ref_data->F_k0, bus_ref_data->F_i_d, trans_var_ptr->q_fk_d);











    return bus_cons;

}






BusConstraints::VecBound BusConstraints::GetBounds() const
{
 VecBound bus_con_bounds(GetRows());

 for (size_t idx=0; idx<bus_con_bounds.size(); idx++)
 {
     bus_con_bounds.at(idx).upper_ = 1.0;
     bus_con_bounds.at(idx).lower_ = 0.0;
 }
 return bus_con_bounds;

}

void BusConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    bus_var_ptr = x->GetComponent<BusVariables>(bus_var_name);
    gen_var_ptr =  x->GetComponent<GeneratorVariables>("gen_variables");
    load_var_ptr = x->GetComponent<LoadVariables>("load_variables");
    line_var_ptr = x->GetComponent<LineVariables>("line_variables");
    trans_var_ptr = x->GetComponent<TransformerVariables>("trans_variables");
}
void BusConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}