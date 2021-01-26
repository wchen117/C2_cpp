#ifndef __GOCCONSTRAINT__
#define __GOCCONSTRAINT__
#include <ifopt/constraint_set.h>
#include <wrapper_construct.hpp>

using Eigen::VectorXd;

class GocConstraints : public ifopt::ConstraintSet {
public:
    GocConstraints(int n_constraints, const std::string& name);
    ~GocConstraints();
    // read in the input parameters to construct constraints
    void ReadinData(const Wrapper_Construct& model_data);
    // these two define the constraints and bounds
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;

    //for now we just set ipopt.SetOption("jacobian_approximation", "finite-difference-values");
    void FillJacobianBlock(std::string var_set, Jacobian &) const override;
    
};
#endif
