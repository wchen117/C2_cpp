//
// Created by wchen on 3/17/21.
//

#ifndef GOC_CPP_LINE_CONSTRAINTS_HPP
#define GOC_CPP_LINE_CONSTRAINTS_HPP
#include <ifopt/constraint_set.h>
#include <variables/line_variables.hpp>
#include <variables/bus_variables.hpp>
#include <wrapper_construct.hpp>

class LineConstraints : public ifopt::ConstraintSet
{
public:
    LineConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name);
    ~LineConstraints();
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;
    void ComputeQuantities();

private:
    void FillJacobianBlock(std::string var_set, Jacobian &jac_block) const override;
    void InitVariableDependedQuantities(const VariablesPtr &x) override;

    // the name for the corresponding load variable set
    std::string line_var_name;
    std::shared_ptr<LineVariables> line_var_ptr;
    std::shared_ptr<BusVariables> bus_var_ptr;
    UMAP_TUPLE_iis_DOUBLE p_ek_o, q_ek_o, p_ek_d, q_ek_d;
    template < typename T>
    std::pair<bool, int > findInVector(const std::vector<T>  & vecOfElements, const T  & element) const {
        std::pair<bool, int> result;
        // Find given element in vector
        auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);
        if (it != vecOfElements.end()) {
            result.second = distance(vecOfElements.begin(), it);
            result.first = true;
        } else {
            result.first = false;
            result.second = -1;
        }
        return result;
    }

};
#endif //GOC_CPP_LINE_CONSTRAINTS_HPP
