#include <costs/bus_costs.hpp>

BusCosts::BusCosts(const std::string& name) : CostTerm(name + "_obj") 
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
    
    auto tmp_np = ComputeObj(bus_vars_ptr->p_ikn_plus, bus_vars_ptr->p_ikn_minus, c_n_p);
    auto tmp_nq = ComputeObj(bus_vars_ptr->q_ikn_plus, bus_vars_ptr->q_ikn_minus, c_n_q);

    z_ik = - (tmp_np + tmp_nq);


    return z_ik;
}
double BusCosts::ComputeObj(const Eigen::MatrixXd& ikn_plus, const Eigen::MatrixXd& ikn_minus, const std::vector<double>& c_n) const
{
    size_t size_ikn = ikn_plus.size();
    double tmp_np;
    Eigen::MatrixXd tmp = (ikn_plus + ikn_minus);
    size_t num_rows = c_n.size();
    size_t num_columns = size_ikn/num_rows;
    
    if (num_rows == 1)
    {
        tmp_np = c_n.at(0) * tmp.sum();
    }
    else
    {
        Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>, Eigen::RowMajor> tmp_ikn(tmp.data(), num_rows, num_columns);
        for (size_t idx=0; idx<num_rows; idx++)
        {
            auto tmp_row = (c_n.at(idx) * tmp_ikn.row(idx));
            //std::cout<<tmp_row.colwise().sum()<<std::endl;;
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