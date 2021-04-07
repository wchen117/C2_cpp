#ifndef __BUSCONSTRAINTS_HPP__
#define __BUSCONSTRAINTS_HPP__
#include <ifopt/constraint_set.h>
#include <variables/bus_variables.hpp>
#include <variables/line_variables.hpp>
#include <variables/generator_variables.hpp>
#include <variables/load_variables.hpp>
#include <variables/load_variables.hpp>
#include <variables/transformer_variables.hpp>
#include <variables/switch_shunt_variables.hpp>
#include <wrapper_construct.hpp>

class BusConstraints : public ifopt::ConstraintSet {
public:
    BusConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name);
    ~BusConstraints();
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;



private:
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    void InitVariableDependedQuantities(const VariablesPtr& x) override;


    std::string bus_var_name;
    std::shared_ptr<Wrapper_Construct> bus_ref_data;
    std::shared_ptr<BusVariables> bus_var_ptr;
    std::shared_ptr<GeneratorVariables> gen_var_ptr;
    std::shared_ptr<LoadVariables> load_var_ptr;
    std::shared_ptr<TransformerVariables> trans_var_ptr;
    std::shared_ptr<LineVariables> line_var_ptr;
    std::shared_ptr<SwitchShuntVariables> swsh_var_ptr;

    template <typename T>
    double get_sum(const std::vector<T> K0_vector, const std::unordered_map<T, int, boost::hash<T> > K0_umap, const Eigen::VectorXd sum_from_vector)  const
    {
        double sum_value = 0.0;
        for (size_t idx=0; idx<K0_vector.size(); idx++)
        {
            auto item_k0 =K0_vector.at(idx);

            for (auto k0_u: K0_umap)
            {
                if (item_k0 == k0_u.first)
                {
                    sum_value += sum_from_vector(idx);

                }
            }

        }
        return sum_value;
    }





};

#endif