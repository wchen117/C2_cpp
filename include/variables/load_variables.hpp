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
    void SetVariables(const Eigen::VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    friend class LoadCosts;
    friend class BusConstraints;
    //friend class LineCosts;
private:
    std::shared_ptr<Wrapper_Construct> load_ref_data;
    // each inner vector has length n, outter vector has length J_k
    std::vector<std::vector<double> > p_jn_over;
    std::vector<std::vector<double> > c_jn;
    std::vector<std::vector<double> > p_jkn;
    std::vector<double> t_jk;
    std::vector<double> t_j_over;
    std::vector<double> t_j_under;
    // a local copy of j index in J_k and all the other variable above
    std::vector<double> load_j_id;


};
#endif
