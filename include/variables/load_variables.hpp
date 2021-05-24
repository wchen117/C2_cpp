#ifndef __LOAD_VARIABLES_HPP__
#define __LOAD_VARIABLES_HPP__
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>

class LoadVariables : public ifopt::VariableSet 
{
public:
    LoadVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~LoadVariables();
    Eigen::VectorXd GetValues() const override;
    Eigen::VectorXd get_p_jk();
    Eigen::VectorXd get_q_jk();
    void SetVariables(const Eigen::VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    friend class LoadCosts;
    friend class BusConstraints;
    friend class LoadConstraints;
    friend class BaseCaseProblem;
    //friend class LineCosts;

private:
    std::shared_ptr<Wrapper_Construct> load_ref_data;
    // each inner vector has length n, outter vector has length J_k
    std::vector<std::vector<double> > p_jn_over;
    std::vector<std::vector<double> > c_jn;
    // p_jk = \sum_{n} p_jkn, bounded also to t_jk by equlity constraint(?)
    std::vector<std::vector<double> > p_jkn;
    // so.... this is bounded to t_jk by equality constraint
    Eigen::VectorXd q_jk;
    Eigen::VectorXd t_jk;
    // bounds for t_jk
    Eigen::VectorXd t_j_over;
    Eigen::VectorXd t_j_under;

    Eigen::VectorXd p_j_ru_over;
    Eigen::VectorXd p_j_rd_over;

    //some coefficients used for load_constraints
    Eigen::VectorXd p_j_0;
    Eigen::VectorXd q_j_0;

    // for book keeping
    Eigen::VectorXi load_i;
    Eigen::VectorXi load_id_j;
    // some some parameters
    // p_jkn_size is the flattened p_jkn size
    size_t p_jk_size, p_jkn_size, t_jk_size;


};
#endif
