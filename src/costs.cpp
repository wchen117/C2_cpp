#include <costs.hpp>


GocCost::GocCost(const std::string& name) : CostTerm(name){}
GocCost::~GocCost() {}

double GocCost::GetCost() const  {}
void GocCost::FillJacobianBlock (std::string var_set, Jacobian& jac) const  {}
void GocCost::ReadinData(const Wrapper_Construct& model_data) {}
