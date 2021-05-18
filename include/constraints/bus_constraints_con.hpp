#ifndef __BUSCONSTRAINTSCON_HPP__
#define __BUSCONSTRAINTSCON_HPP__
#include <ifopt/constraint_set.h>
#include <variables/bus_variables_con.hpp>
#include <variables/line_variables_con.hpp>
#include <variables/generator_variables_con.hpp>
#include <variables/load_variables_con.hpp>
#include <variables/load_variables_con.hpp>
#include <variables/transformer_variables_con.hpp>
#include <variables/switch_shunt_variables_con.hpp>
#include <wrapper_construct.hpp>

class BusConstraintsCon : public ifopt::ConstraintSet {
public:
    BusConstraintsCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name, const std::string load_name,\
                   const std::string line_name, const std::string swsh_name, const std::string trans_name, const std::string gen_name);
    ~BusConstraintsCon();
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;



private:
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    void InitVariableDependedQuantities(const VariablesPtr& x) override;


    std::string bus_var_name;
    std::string load_var_name;
    std::string line_var_name;
    std::string swsh_var_name;
    std::string trans_var_name;
    std::string gen_var_name;

    std::shared_ptr<Wrapper_Construct> bus_ref_data;
    std::shared_ptr<BusVariablesCon> bus_var_ptr;
    std::shared_ptr<GeneratorVariablesCon> gen_var_ptr;
    std::shared_ptr<LoadVariablesCon> load_var_ptr;
    std::shared_ptr<TransformerVariablesCon> trans_var_ptr;
    std::shared_ptr<LineVariablesCon> line_var_ptr;
    std::shared_ptr<SwitchShuntVariablesCon> swsh_var_ptr;


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