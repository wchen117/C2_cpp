#ifndef __GOCBUSVARIABLESCON_HPP__
#define __GOCBUSVARIABLESCON_HPP__
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>


class BusVariablesCon : public ifopt::VariableSet {
public:
    BusVariablesCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~BusVariablesCon();
    // read in the input data that defines the variables
    // define the variables
    Eigen::VectorXd GetValues() const override;
    void SetVariables(const VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    friend class BusCostsCon;
    friend class BusConstraintsCon;
    friend class LineVariablesCon;
    friend class TransformerVariablesCon;
    friend class ContigencyCaseProblem;


private:
    std::shared_ptr<Wrapper_Construct> bus_ref_data;
    // p_ikn_* and q_ikn_* are col major matrix of size Np (Nq) * Is
    // num of rows = Np(Nq), num of cols = Is
    Eigen::MatrixXd p_ikn_plus, p_ikn_minus, q_ikn_plus, q_ikn_minus;
    // now their coeffs c_n_p and c_n_q
    Eigen::MatrixXd c_n_p, c_n_q;
    // upper bound for varibale p_n_over and q_n_over
    Eigen::MatrixXd p_n_over, q_n_over;
    size_t Np, Nq, Is, size_q_ikn, size_p_ikn, bus_var_len;
    // and some variables appear only in constraint set
    // of size Is, here the sequence of i in I is declared
    Eigen::VectorXd v_ik;
    Eigen::VectorXd theta_ik;
    // and its associated bound v_over and v_under, for K \neq k0, this is v_
    Eigen::VectorXd v_i_over, v_i_under;
    Eigen::VectorXd b_i_fs, g_i_fs;
    // and we just want a local copy of I (bus id) that is sorted for sanity
    std::vector<int> sorted_bus_ID;
};
#endif
