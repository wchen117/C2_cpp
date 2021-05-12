//
// Created by wchen on 5/12/21.
//

#ifndef GOC_CPP_LINE_VARIABLES_CON_HPP
#define GOC_CPP_LINE_VARIABLES_CON_HPP
#include <ifopt/variable_set.h>
#include <variables/bus_variables.hpp>
#include <wrapper_construct.hpp>

class LineVariablesCon: public ifopt::VariableSet {
public:
    LineVariablesCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::shared_ptr<BusVariables> bus_var_ptr, const std::string& name);
    ~LineVariablesCon();
    Eigen::VectorXd GetValues() const override;
    void SetVariables(const Eigen::VectorXd &x) override;
    Eigen::VectorXd sigmoid_approx(const Eigen::VectorXd& base_array);
    Eigen::VectorXd inverse_sigmoid_approx(const Eigen::VectorXd& sigmoid_array);
    // define the bounds of variables
    VecBound GetBounds() const override;
    friend class LineCostsCon;
    friend class LineConstraintsCon;
    friend class BusConstraintsCon;
    friend class ContigencyCaseProblem;

private:
    // first dimension: Ns, second dimension: size of E_k
    // MatrixXd by default is column major
    // first, variables:
    Eigen::MatrixXd s_enk_plus;
    // x_ek_sw is in {0, 1}, for now we sent it to a real number between 0 and 1;
    Eigen::VectorXd x_ek_sw;
    Eigen::VectorXd x_ek_sw_bound;
    Eigen::VectorXd swqual_state;
    Eigen::VectorXd x_e_sw0;
    // use to track if e \in E^{sw} for e in x_ek_sw
    Eigen::VectorXd swqual_x_ek;
    // then some parameters and coefficients;

    Eigen::MatrixXd c_n_s;
    Eigen::MatrixXd r_e_over_eigen;
    Eigen::MatrixXd t_n_s_over;
    Eigen::VectorXd c_e_sw;
    Eigen::VectorXd ref_oribus;
    Eigen::VectorXd ref_desbus;
    Eigen::VectorXi ref_id;

    Eigen::VectorXd p_ek_o, q_ek_o, p_ek_d, q_ek_d;
    Eigen::VectorXd bus_vik, bus_vipk;

    std::shared_ptr<Wrapper_Construct> local_input_ptr;
    size_t line_var_len, size_E_k0, Ns, pq_ek_od_size;


};

#endif //GOC_CPP_LINE_VARIABLES_CON_HPP