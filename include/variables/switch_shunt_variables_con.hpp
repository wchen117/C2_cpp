//
// Created by wchen on 3/19/21.
//

#ifndef GOC_CPP_SWITCH_SHUNT_CON_HPP
#define GOC_CPP_SWITCH_SHUNT_CON_HPP
#include <ifopt/variable_set.h>
#include <wrapper_construct.hpp>
class SwitchShuntVariablesCon : public ifopt::VariableSet
{
public:
    SwitchShuntVariablesCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~SwitchShuntVariablesCon();
    void SetVariables(const Eigen::VectorXd &x) override;
    Eigen::VectorXd GetValues() const override;
    Eigen::VectorXd get_b_hat_st() const;
    // define the bounds of variables
    VecBound GetBounds() const override;
    friend class BusConstraintsCon;
    friend class ContigencyCaseProblem;
private:
    std::shared_ptr<Wrapper_Construct> swsh_ref_data;
    //eq (46)

    // num of rows: size of H_k, num or cols: number of pairs of BL and NL in each h
    Eigen::MatrixXd x_hak_st;
    // x_hak_st is binary variable
    Eigen::MatrixXd x_hak_st_upbound;
    // coefficients for x_hak_st
    Eigen::MatrixXd b_ha_st;
    Eigen::VectorXd swsh_ih;
    // size of variables
    size_t size_x_hak_st;

};

#endif //GOC_CPP_SWITCH_SHUNT_HPP
