//
// Created by wchen on 2/18/21.
//

#ifndef GOC_CPP_LINE_VARIABLES_HPP
#define GOC_CPP_LINE_VARIABLES_HPP
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>

class LineVariables: public ifopt::VariableSet {
public:
    LineVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~LineVariables();
    Eigen::VectorXd GetValues() const override;
    void SetVariables(const Eigen::VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    friend class LineCosts;
private:
    // first dimension: Ns, second dimension: size of E_k
    // MatrixXd by default is column major
    Eigen::MatrixXd s_enk_plus;
    Eigen::MatrixXd c_n_s;
    Eigen::MatrixXd r_e_over_eigen;
    Eigen::MatrixXd t_n_s_over;

    //Eigen::ArrayXd r_e_over;

    Eigen::VectorXd c_e_sw;
    Eigen::VectorXd ref_oribus;
    Eigen::VectorXd ref_desbus;

    // x_ek_sw, x_e_sw0 are binary variables \in {0, 1}, for each e we have a pair of x_ek_sw and x_e_sw0
    // for now we set their bound between 0 and 1;
    Eigen::VectorXd x_ek_sw;
    Eigen::VectorXd x_e_sw0;

    std::shared_ptr<Wrapper_Construct> local_input_ptr;
    size_t line_var_len, size_E_k0, Ns;

};


#endif //GOC_CPP_LINE_VARIABLES_HPP
