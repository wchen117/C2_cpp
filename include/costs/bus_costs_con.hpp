//
// Created by wchen on 5/12/21.
//

#ifndef GOC_CPP_BUS_COSTS_CON_HPP
#define GOC_CPP_BUS_COSTS_CON_HPP
#include <ifopt/cost_term.h>
#include <variables/bus_variables_con.hpp>
class BusCostsCon : public ifopt::CostTerm {
public:
    BusCostsCon(const std::string& name);
    ~BusCostsCon();
    double GetCost () const override;
private:
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    std::string bus_var_name;
    std::shared_ptr<BusVariablesCon> bus_var_ptr;



};
#endif //GOC_CPP_BUS_COSTS_CON_HPP
