//
// Created by wchen on 2/26/21.
//

#ifndef GOC_CPP_GENERATOR_VARIABLES_HPP
#define GOC_CPP_GENERATOR_VARIABLES_HPP
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>

class GeneratorVariables : public ifopt::VariableSet
{
public:
    GeneratorVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~GeneratorVariables();
    Eigen::VectorXd GetValues() const override;
    void SetVariables(const Eigen::VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    friend class GenCosts;
    friend class BusConstraints;

private:
    std::shared_ptr<Wrapper_Construct> gen_ref_data;
    // first dimension: number of generators, second dimension: Ng (not the same for each generator)
    std::vector<std::vector<double> > p_gnk;
    // these three seems to be binary variables {0, 1}, for now we set them real variables between 0 and 1
    Eigen::VectorXd x_gk_on;
    Eigen::VectorXd x_gk_su;
    Eigen::VectorXd x_gk_sd;

    // coefficients
    std::vector<std::vector<double> > c_gn;
    std::vector<std::vector<double> > p_gn_over;
    Eigen::VectorXd c_g_on;
    Eigen::VectorXd c_g_su;
    Eigen::VectorXd c_g_sd;
    //coefficients used in eqn(82)
    Eigen::VectorXd x_g_on_0;
    //coefficients used in eqn(85) - eqn(88)
    Eigen::VectorXd p_g_over, p_g_under, q_g_over, q_g_under, p_g_ru_over;


    // some useful size parameters
    size_t size_p_gnk = 0;
    size_t size_G_k0, gen_var_len;



};

#endif //GOC_CPP_GENERATOR_VARIABLES_HPP
