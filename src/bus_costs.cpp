#include <costs/bus_costs.hpp>

BusCosts::BusCosts(const std::string& name) : CostTerm(name) 
{
    bus_var_name = name;  
}

BusCosts::~BusCosts() {}


double BusCosts::GetCost () const
{
    std::vector<double> c_n_p;
    std::vector<double> c_n_q;
    double z_ik;

    for (auto pcblock: bus_vars_ptr->data_fvariable->new_data.sup.pcblocks)
    {
        c_n_p.push_back(pcblock.c * bus_vars_ptr->data_fvariable->s_tilde_inverse);
    }

    for (auto qcblock: bus_vars_ptr->data_fvariable->new_data.sup.qcblocks)
    {
        c_n_q.push_back(qcblock.c * bus_vars_ptr->data_fvariable->s_tilde_inverse);
    }
    
    double tmp_np, tmp_nq;
    Eigen::MatrixXd tmp = (bus_vars_ptr->p_ikn_plus + bus_vars_ptr->p_ikn_minus);
    size_t num_rows = c_n_p.size();
    size_t num_columns = bus_vars_ptr->size_p_ikn/c_n_p.size();
    
    if (num_rows == 1)
    {
        tmp_np = c_n_p.at(0) * tmp.sum();
    }
    else
    {
        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>, Eigen::RowMajor> tmp_p_ikn(tmp.data(), num_rows, num_columns);
        for (size_t idx=0; idx<num_rows; idx++)
        {
            auto tmp_row = (c_n_p.at(idx) * tmp_p_ikn.row(idx));
            tmp += tmp_row.colwise().sum();
        }
    }
    


    return tmp_np;
}
void BusCosts::InitVariableDependedQuantities (const VariablesPtr& x)
{
    bus_vars_ptr = x->GetComponent<BusVariables>(bus_var_name);
}
void BusCosts::FillJacobianBlock(std::string var_set, Jacobian&) const
{

}