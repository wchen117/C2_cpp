#ifndef __GOCVARIABLES_HPP__
#define __GOCVARIABLES_HPP__
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>

using Eigen::VectorXd;

class GocVariables : public ifopt::VariableSet {
public:
    GocVariables(int n_var, const std::string& name);
    ~GocVariables();
    // read in the input data that defines the variables
    void ReadinData(const Wrapper_Construct& model);
    // define the variables
    VectorXd GetValues() const override;
    void SetVariables(const VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    
};
#endif
