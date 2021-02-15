#ifndef __GOCVARIABLES_HPP__
#define __GOCVARIABLES_HPP__
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>

using Eigen::VectorXd;
class BusVariables : public ifopt::VariableSet {
public:
    BusVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~BusVariables();
    // read in the input data that defines the variables
    // define the variables
    VectorXd GetValues() const override;
    void SetVariables(const VectorXd &x) override;
    // define the bounds of variables
    VecBound GetBounds() const override;
    std::shared_ptr<Wrapper_Construct> data_fvariable;
    friend class BusCosts;

    // within *_ikn_*, size i*n
    VectorXd p_ikn_plus, p_ikn_minus, q_ikn_plus, q_ikn_minus;
    size_t size_p_ikn, size_q_ikn, size_bus_variables;
};
#endif
