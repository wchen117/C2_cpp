//
// Created by wchen on 2/24/21.
//

#ifndef GOC_CPP_TRANSFORMER_VARIABLES_H
#define GOC_CPP_TRANSFORMER_VARIABLES_H
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>
class TransformerVariables: public ifopt::VariableSet {
public:
    TransformerVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~TransformerVariables();
    Eigen::VectorXd GetValues() const override;
    void SetVariables(const Eigen::VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    friend class TransformerCosts;
    friend class TransConstraints;
    friend class BusConstraints;
private:
    // first variables, s_fnk_plus is colmajor matrix,
    // first dimension: Ns, second dimension: size of F_k
    Eigen::MatrixXd s_fnk_plus;
    // x_fk_sw, size of F_k
    Eigen::VectorXd x_fk_sw;
    // x_fk_st, eqn(61)
    Eigen::VectorXd x_fk_st;
    // tau_fk eqn(62) and its bounds
    Eigen::VectorXd tau_fk;
    // upper and lower bounds for tau_fk
    Eigen::VectorXd tau_fk_over, tau_fk_under;
    // some coefficents needed for tau_fk and x_fk
    Eigen::VectorXd tau_f_st, tau_f_mid, tau_f_0;
    // theta_fk mentioned in eqn(64)
    Eigen::VectorXd theta_fk, theta_fk_over, theta_fk_under;
    // some coefficients needed for theta_fkand x_fk
    Eigen::VectorXd theta_f_st, theta_f_mid, theta_f_0;
    // variables in eqn(66) and eqn(67)
    // these are conductance and susceptance values, not generators
    Eigen::VectorXd b_fk, g_fk, eta_fk;
    // some coeffcients asscociated with them
    Eigen::VectorXd b_f_0, g_f_0;




    // now some parameters, matrices, size of Ns * F_k
    Eigen::MatrixXd c_n_s;
    Eigen::MatrixXd t_n_s_over;
    Eigen::MatrixXd s_f_over_eigen;

    // vectors, size of F_k

    Eigen::VectorXd c_f_sw;
    Eigen::VectorXd ref_oribus;
    Eigen::VectorXd ref_desbus;
    Eigen::VectorXd x_f_sw0;
    Eigen::VectorXd x_fk_st_bound;
    // pointer to input data and some useful size info
    std::shared_ptr<Wrapper_Construct> local_input_ptr;
    size_t trans_var_len, size_F_k0, Ns;



};
#endif //GOC_CPP_TRANSFORMER_VARIABLES_H
