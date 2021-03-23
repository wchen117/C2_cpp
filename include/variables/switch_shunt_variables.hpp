//
// Created by wchen on 3/19/21.
//

#ifndef GOC_CPP_SWITCH_SHUNT_HPP
#define GOC_CPP_SWITCH_SHUNT_HPP
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>
class SwitchShuntVariables : public ifopt::VariableSet
{
public:
    SwitchShuntVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~SwitchShuntVariables();
    void SetVariables(const Eigen::VectorXd &x) override;
    Eigen::VectorXd GetValues() const override;
    // define the bounds of variables
    VecBound GetBounds() const override;
private:
    std::shared_ptr<Wrapper_Construct> swsh_ref_data;
    //eq (46)

    // num of rows: size of H_k, num or cols: number of pairs of BL and NL in each h
    std::vector<std::vector<int> > x_hak_st;

};

#endif //GOC_CPP_SWITCH_SHUNT_HPP
