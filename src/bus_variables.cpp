#include <variables/bus_variables.hpp>

BusVariables::BusVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(-1, name) 
{    
    // use kSpecifyLater since we need to figure out how many variables in bus_variables
    data_fvariable = data_ptr;
    // number of rows (variables must be set within the constructor)
    // here we need to figure out the number of variables/rows in this variable set
    // and set their initial values
    size_p_ikn = data_fvariable->Is * data_fvariable->Np;
    size_q_ikn = data_fvariable->Is * data_fvariable->Nq;
    // bus variables consist of p_ikn+, p_ikn-, q_ikn+, q_ikn-, z_ik (?)
    size_bus_variables = 2 * size_q_ikn + 2 * size_p_ikn;
    SetRows(size_bus_variables);
    // initlize them to 0?
    if (size_p_ikn && size_q_ikn)
    {
        p_ikn_plus = VectorXd::Zero(size_p_ikn);
        p_ikn_minus = VectorXd::Zero(size_p_ikn);
        q_ikn_plus = VectorXd::Zero(size_q_ikn);
        q_ikn_minus = VectorXd::Zero(size_q_ikn);

    }
}

BusVariables::~BusVariables(){}

VectorXd BusVariables::GetValues() const 
{
    // why rows = number of variables????
    if  (GetRows())
    {
       VectorXd tmp_x(GetRows());
       tmp_x.segment(0,size_p_ikn) = p_ikn_plus;
       tmp_x.segment(size_p_ikn,size_p_ikn) = p_ikn_minus;
       tmp_x.segment(2*size_p_ikn, size_q_ikn) = q_ikn_plus;
       tmp_x.segment(2*size_p_ikn+size_q_ikn, size_q_ikn) = q_ikn_minus;
       return tmp_x;
    }
    
}

void BusVariables::SetVariables(const VectorXd &x) 
{
    // I guess?
    p_ikn_plus = x.segment(0, size_p_ikn);
    p_ikn_minus = x.segment(size_p_ikn, size_p_ikn);
    q_ikn_plus = x.segment(2*size_p_ikn, size_q_ikn);
    q_ikn_minus = x.segment(2*size_p_ikn+size_q_ikn, size_q_ikn);
}


BusVariables::VecBound BusVariables::GetBounds() const
{
    
    VecBound bus_bounds(GetRows());
    Eigen::VectorXd bus_upper_bound(GetRows());
    std::vector<double> p_n_over_list;
    std::vector<double> q_n_over_list;
    for (auto pcblock: data_fvariable->new_data.sup.pcblocks)
    {
        // page 48, "pmax": p_n_over * s_tilde_inverse
        p_n_over_list.push_back(pcblock.pmax * data_fvariable->s_tilde_inverse);
        //std::cout<<pcblock.pmax * data_fvariable->s_tilde_inverse<<std::endl;
    }
    for (auto qcblock: data_fvariable->new_data.sup.qcblocks)
    {
        // page 48, "qmax": q_n_over * s_tilde_inverse
        q_n_over_list.push_back(qcblock.qmax * data_fvariable->s_tilde_inverse);
    }
    
    size_t block_size_p = size_p_ikn/p_n_over_list.size();
    size_t block_size_q = size_q_ikn/q_n_over_list.size();

    Eigen::VectorXd p_ikn_upper_bound(size_p_ikn);
    Eigen::VectorXd q_ikn_upper_bound(size_q_ikn);


    for (size_t idx=0; idx<size_p_ikn; idx++)
    {
        size_t tmp = idx/(size_p_ikn/p_n_over_list.size());
        p_ikn_upper_bound(idx) = p_n_over_list.at(tmp);
    }
    
    for (size_t idx=0; idx<size_q_ikn; idx++)
    {
        size_t tmp = idx/(size_q_ikn/q_n_over_list.size());
        q_ikn_upper_bound(idx) = q_n_over_list.at(tmp);
    }
    
    // segment(i, n): a slice starting from i, for a length of n 
    bus_upper_bound.segment(0,  size_p_ikn) = p_ikn_upper_bound;
    bus_upper_bound.segment(size_p_ikn, size_p_ikn) = p_ikn_upper_bound;
    bus_upper_bound.segment(2*size_p_ikn, size_q_ikn) = q_ikn_upper_bound;
    bus_upper_bound.segment(2*size_p_ikn+size_q_ikn, size_q_ikn) = q_ikn_upper_bound;
    
    // for p_ikn and q_ikn their lower bound is always zero

    
    for(size_t idx=0; idx<bus_bounds.size(); idx++)
    {
        bus_bounds.at(idx).lower_ = 0.0;
        bus_bounds.at(idx).upper_ = bus_upper_bound(idx);
    }

    return bus_bounds;
}


