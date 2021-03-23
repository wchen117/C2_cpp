//
// Created by wchen on 3/17/21.
//

#include <constraints/line_constraints.hpp>

LineConstraints::LineConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    // this name is the corresponding line variable name
    line_var_name = name;
    std::cout<<4 * data_ptr->E_k.size()<<std::endl;
    SetRows(4 * data_ptr->E_k.size());
}
LineConstraints::~LineConstraints() {}

Eigen::VectorXd LineConstraints::GetValues() const
{
    Eigen::VectorXd line_cons(GetRows());
    //std::cout<<"Hello this is from GetValues"<<std::endl;

   for (auto ek : line_var_ptr->local_input_ptr->E_k)
   {
       // i \in i_e_o for e \in E_k, i_p \in i_e_d for e \in E_k
       auto idx = line_var_ptr->local_input_ptr->i_e_o[ek];
       auto ipdx = line_var_ptr->local_input_ptr->i_e_d[ek];
       auto ge = line_var_ptr->local_input_ptr->g_e[ek];
       auto be = line_var_ptr->local_input_ptr->b_e[ek];
       auto diff = line_var_ptr->local_input_ptr->theta_0[idx] - line_var_ptr->local_input_ptr->theta_0[ipdx];
       // now figure out the where bus idx and ipdx locate in v_ik
       auto bus_idx_pair = findInVector(bus_var_ptr->sorted_bus_ID, idx);
       auto bus_ipdx_pair = findInVector(bus_var_ptr->sorted_bus_ID, ipdx);
       if (bus_idx_pair.first && bus_ipdx_pair.first)
       {
           auto bus_idx = bus_idx_pair.second;
           auto bus_ipdx = bus_ipdx_pair.second;
       }
       else{
           exit(0);
           }

   }







    return line_cons;
}

LineConstraints::VecBound LineConstraints::GetBounds() const
{
    VecBound line_con_bounds(GetRows());
    return line_con_bounds;
}

void LineConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    line_var_ptr = x->GetComponent<LineVariables>(line_var_name);
    bus_var_ptr = x->GetComponent<BusVariables>("bus_variables");
}
void LineConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}




