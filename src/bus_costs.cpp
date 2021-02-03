#include <costs/bus_costs.hpp>

BusCosts::BusCosts(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : CostTerm(name) 
{
    data_fvariable = data_ptr;
}

BusCosts::~BusCosts() {}

double BusCosts::GetCost () const
{
    std::vector<double> c_n_p_list;
    std::vector<double> c_n_q_list;
    for (auto pcblock: data_fvariable->new_data.sup.pcblocks)
    {
        c_n_p_list.push_back(pcblock.c * data_fvariable->s_tilde_inverse);
    }
    for(auto qcblock: data_fvariable->new_data.sup.qcblocks)
    {
        c_n_q_list.push_back(qcblock.c * data_fvariable->s_tilde_inverse);
        
    }
    double z_ik;

    z_ik = 

    return 0;
}
void BusCosts::FillJacobianBlock(std::string var_set, Jacobian&) const
{

}