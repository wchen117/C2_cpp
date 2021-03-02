#include <variables/bus_variables.hpp>

BusVariables::BusVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(-1, name) 
{    
    // use kSpecifyLater since we need to figure out how many variables in bus_variables
    bus_ref_data = data_ptr;
    // number of rows (variables must be set within the constructor)
    // here we need to figure out the number of variables/rows in this variable set
    // and set their initial values

    Np = bus_ref_data->Np;
    Nq = bus_ref_data->Nq;
    Is = bus_ref_data->Is;
    size_p_ikn = Np * Is;
    size_q_ikn = Nq * Is;
    // bus variables consist of p_ikn+, p_ikn-, q_ikn+, q_ikn-, z_ik (?)
    bus_var_len = 2 * size_q_ikn + 2 * size_p_ikn;
    SetRows(bus_var_len);
    // initlize them to 0?
    if (size_p_ikn && size_q_ikn)
    {
        // will just initialize them to zero i guess
        p_ikn_plus = Eigen::MatrixXd::Zero(Np, Is);
        p_ikn_minus = Eigen::MatrixXd::Zero(Np, Is);
        q_ikn_plus = Eigen::MatrixXd::Zero(Nq, Is);
        q_ikn_minus = Eigen::MatrixXd::Zero(Nq, Is);
        c_n_p = Eigen::MatrixXd::Zero(Np, Is);
        c_n_q = Eigen::MatrixXd::Zero(Nq, Is);
        p_n_over = Eigen::MatrixXd::Zero(Np, Is);
        q_n_over = Eigen::MatrixXd::Zero(Nq, Is);
    }

    for (size_t idx=0; idx<Np; idx++)
    {
        for (size_t jdx=0; jdx<Is; jdx++)
        {
            c_n_p(idx, jdx) = bus_ref_data->new_data.sup.pcblocks.at(idx).c * bus_ref_data->s_tilde_inverse;
            p_n_over(idx, jdx) = bus_ref_data->new_data.sup.pcblocks.at(idx).pmax* bus_ref_data->s_tilde;
        }
    }

    for (size_t idx=0; idx<Nq; idx++)
    {
        for(size_t jdx=0; jdx<Is; jdx++)
        {
            c_n_q(idx, jdx) =  bus_ref_data->new_data.sup.qcblocks.at(idx).c * bus_ref_data->s_tilde_inverse;
            q_n_over(idx, jdx) = bus_ref_data->new_data.sup.qcblocks.at(idx).qmax * bus_ref_data->s_tilde;
        }
    }



}

BusVariables::~BusVariables(){}

Eigen::VectorXd BusVariables::GetValues() const
{
  if (GetRows())
  {
      Eigen::VectorXd tmp_x(GetRows());
      // flatten the *_ikn_* matrix col by col
      Eigen::Map<const Eigen::VectorXd> flat_p_ikn_plus (p_ikn_plus.data(), p_ikn_plus.size());
      Eigen::Map<const Eigen::VectorXd> flat_p_ikn_minus (p_ikn_minus.data(), p_ikn_minus.size());
      Eigen::Map<const Eigen::VectorXd> flat_q_ikn_plus (q_ikn_plus.data(), q_ikn_plus.size());
      Eigen::Map<const Eigen::VectorXd> flat_q_ikn_minus (q_ikn_minus.data(), q_ikn_minus.size());
      tmp_x << flat_p_ikn_plus, flat_p_ikn_minus, flat_q_ikn_plus, flat_q_ikn_minus;
      return tmp_x;
  }
  else
  {
      exit(0);
  }
    
}

void BusVariables::SetVariables(const VectorXd &x) 
{
    auto flat_p_ikn_plus = x.segment(0, size_p_ikn);
    auto flat_p_ikn_minus = x.segment(size_p_ikn, size_p_ikn);
    auto flat_q_ikn_plus = x.segment(2*size_p_ikn, size_q_ikn);
    auto flat_q_ikn_minus = x.segment(2*size_p_ikn+size_q_ikn, size_q_ikn);
    // unflatten the vector to matrix
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>> tmp_p_ikn_plus(flat_p_ikn_plus.data(), Np, Is);
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>> tmp_p_ikn_minus(flat_p_ikn_minus.data(), Np, Is);
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>> tmp_q_ikn_plus(flat_q_ikn_plus.data(), Np, Is);
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>> tmp_q_ikn_minus(flat_q_ikn_minus.data(), Np, Is);
    p_ikn_plus = tmp_p_ikn_plus;
    p_ikn_minus = tmp_p_ikn_minus;
    q_ikn_plus = tmp_q_ikn_plus;
    q_ikn_minus = tmp_q_ikn_minus;

}


BusVariables::VecBound BusVariables::GetBounds() const
{

    VecBound bus_bounds(GetRows());
    // in variable sets, GetRows return number of variables
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::Map<const Eigen::VectorXd> flat_p_n_over (p_n_over.data(), p_n_over.size());
    Eigen::Map<const Eigen::VectorXd> flat_q_n_over (q_n_over.data(), q_n_over.size());
    upper_bound << flat_p_n_over, flat_p_n_over, flat_q_n_over, flat_q_n_over;
    for (size_t idx=0; idx<GetRows(); idx++)
    {
        bus_bounds.at(idx).upper_ = upper_bound(idx);
        bus_bounds.at(idx).lower_ = 0.0;
    }

    return bus_bounds;
}


