#ifndef __BUSCONSTRAINTS_HPP__
#define __BUSCONSTRAINTS_HPP__
#include <ifopt/constraint_set.h>
#include <variables/bus_variables.hpp>

class BusConstraints : public ifopt::ConstraintSet {
public:
    BusConstraints(const std::string& name);
    ~BusConstraints();
    VectorXd GetValues() const override;
    VecBound GetBounds() const override;


private:
    void FillJacobianBlock(std::string var_set, Jacobian& jac_block) const override;
    void InitVariableDependedQuantities(const VariablesPtr& x) override;
    std::string bus_var_name;
    std::shared_ptr<BusVariables> bus_var_ptr;
    size_t bus_cons_size;
    // a template function to find common item between unordered map with key=T and vector with item T
    template<typename T>
    void FindCommon(const std::unordered_map<T, int, boost::hash<T> >& umap_list, \
                    const std::vector<T>& vect, std::vector<int>& output) const
    {
        for (auto umap_item: umap_list)
        {
            for (auto vect_item: vect)
            {
                if (umap_item.second == std::get<0>(vect_item))
                {
                    output.push_back(umap_item.second);

                }
            }
        }



    }



};

#endif