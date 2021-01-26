#include "constraints.hpp"

GocConstraints::GocConstraints(int n_constraints, const std::string& name) : ConstraintSet(n_constraints, name)  {}
GocConstraints::~GocConstraints() {}
VectorXd GocConstraints::GetValues() const {}
GocConstraints::VecBound GocConstraints::GetBounds() const {}
void GocConstraints::FillJacobianBlock(std::string var_set, Jacobian &) const {}
void GocConstraints::ReadinData(const Wrapper_Construct& model_data) {}


