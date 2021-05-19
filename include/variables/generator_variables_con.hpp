//
// Created by wchen on 2/26/21.
//

#ifndef GOC_CPP_GENERATOR_VARIABLES_CON_HPP
#define GOC_CPP_GENERATOR_VARIABLES_CON_HPP
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>
#include <fstream>

class GeneratorVariablesCon : public ifopt::VariableSet
{
public:
    GeneratorVariablesCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~GeneratorVariablesCon();
    Eigen::VectorXd GetValues() const override;
    void SetVariables(const Eigen::VectorXd &x) override;
    Eigen::VectorXd get_p_gk() const;
    // define the bounds of variables
    VecBound GetBounds() const override;
    std::string read_to_string(std::string file_name);
    std::vector<std::string>  parse_on_delimiter(std::string const &input_string, std::string delimiter);

    friend class GenCostsCon;
    friend class BusConstraintsCon;
    friend class GeneratorConstraintsCon;
    friend class ContigencyCaseProblem;

    struct read_generator {
        int i;
        int id;
        double p_gk;
        double q_gk;
        double x_gk_on;
        double x_gk_su;
        double x_gk_sd;
    };

    std::vector<std::shared_ptr<read_generator>> get_base_gen_var();

private:
    std::shared_ptr<Wrapper_Construct> gen_ref_data;
    // first dimension: number of generators, second dimension: Ng (not the same for each generator)
    std::vector<std::vector<double> > p_gnk;
    Eigen::VectorXd q_gk;
    // these three seems to be binary variables {0, 1}, for now we set them real variables between 0 and 1
    Eigen::VectorXd x_gk_on;
    Eigen::VectorXd x_gk_su;
    Eigen::VectorXd x_gk_sd;

    Eigen::VectorXd x_gk_on_base, x_gk_su_base, x_gk_sd_base, p_gk_base, q_gk_base;

    // coefficients
    std::vector<std::vector<double> > c_gn;
    std::vector<std::vector<double> > p_gn_over;
    Eigen::VectorXd c_g_on;
    Eigen::VectorXd c_g_su;
    Eigen::VectorXd c_g_sd;
    //coefficients used in eqn(82)
    Eigen::VectorXd x_g_on_0;
    //coefficients used in eqn(85) - eqn(88)
    Eigen::VectorXd p_g_over, p_g_under, q_g_over, q_g_under, p_g_ru_over, p_g_rd_over, p_g_0;
    // to determine if g \in G_su or \in G_sd
    Eigen::VectorXi G_su_value, G_sd_value;

    Eigen::VectorXi gen_i_g;
    Eigen::VectorXi gen_id_g;

    // some useful size parameters
    size_t size_p_gnk = 0;
    size_t size_G_k0, gen_var_len;





};

#endif //GOC_CPP_GENERATOR_VARIABLES_HPP
