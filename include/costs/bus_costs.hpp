#ifndef __BUS_COSTS_HPP__
#define __BUS_COSTS_HPP__
#include <ifopt/cost_term.h>
#include <wrapper_construct.hpp>
class BusCosts : public ifopt::CostTerm {
public:
    BusCosts(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~BusCosts();
    double GetCost () const override;
private: 
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::shared_ptr<Wrapper_Construct> data_fvariable;

    
};
#endif