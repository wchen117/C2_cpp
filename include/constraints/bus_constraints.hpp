#ifndef __BUSCONSTRAINTS_HPP__
#define __BUSCONSTRAINTS_HPP__
#include <ifopt/constraint_set.h>
#include <wrapper_construct.hpp>

using Eigen::VectorXd;

class BusConstraints : public ifopt::ConstraintSet {
public:
    BusConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~BusConstraints();
    VectorXd GetValues() const override;
    // define the bounds of variables
    VecBound GetBounds() const override;
private: 
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::shared_ptr<Wrapper_Construct> data_fvariable;

};
#endif