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
    friend class GeneratorCosts;

private:
    std::shared_ptr<Wrapper_Construct> gen_ref_data;
    // first dimension: number of generators, second dimension: Ng (not the same for each generator)
    std::vector<std::vector<double> > p_gnk;
    // these three seems to be binary variables {0, 1}, for now we set them real variables between 0 and 1
    std::vector<double> x_gk_on;
    std::vector<double> x_gk_su;
    std::vector<double> x_gk_sd;

    // coefficients
    std::vector<std::vector<double> > c_gn;
    std::vector<std::vector<double> > p_gn_over;
    std::vector<double> c_g_on;
    std::vector<double> c_g_su;
    std::vector<double> c_g_sd;

    // some useful size parameters
    size_t size_p_gnk = 0;
    size_t size_G_k0;


};

#endif //GOC_CPP_GENERATOR_VARIABLES_HPP
