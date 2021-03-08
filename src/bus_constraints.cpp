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
    for (auto gi: bus_var_ptr->bus_ref_data->G_i)
    {

        for (auto gk: bus_var_ptr->bus_ref_data->G_k)
        {
            int gk_key_int;
            std::string gk_key_string;
            std::tie(gk_key_int, gk_key_string) = gk;
            if (gi.second == gk_key_int)
            {
                g_Gi_Gk.push_back(gk_key_int);
            }

        }

    }

    std::vector<int> j_Ji_Jk;
    for (auto ji: bus_var_ptr->bus_ref_data->J_i)
    {
        for (auto jk: bus_var_ptr->bus_ref_data->J_k)
        {
            int jk_key_int;
            int jk_key_string;
            //std::tie(jk_key_int, jk_key_string) = jk;
            if (ji.second == jk_key_int)
            {
                //j_Ji_Jk.push_back(jk_key_int);
            }
        }
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