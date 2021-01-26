#ifndef __GOCCOST_HPP__
#define __GOCCOST_HPP__
#include <ifopt/cost_term.h>
#include <wrapper_construct.hpp>

using Eigen::VectorXd;

class GocCost : public ifopt::CostTerm
{
public:
    GocCost(const std::string& name);
    ~GocCost();
    // raed in the input data that define the cost/objective
    void ReadinData(const Wrapper_Construct& model);

    double GetCost() const override;
    // ??? where does this comes from
    void FillJacobianBlock (std::string var_set, Jacobian& jac) const override;

};
#endif