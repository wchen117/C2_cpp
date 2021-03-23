//
// Created by wchen on 3/19/21.
//
#include <variables/switch_shunt_variables.hpp>

SwitchShuntVariables::SwitchShuntVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(-1, name)
{
    swsh_ref_data = data_ptr;

    // variable x_hak_st defined in eq(46)
    if (!swsh_ref_data->H_k.empty())
    {
        x_hak_st.resize(swsh_ref_data->H_k.size());

        for (auto sw: swsh_ref_data->x_ha_st_over)
        {
            int hh, ah;
            std::tie(hh, ah) = sw.first;
            std::cout<<"hh = "<<hh<<" ah = "<<ah<<" and sw.second = "<<sw.second<<std::endl;
        }
    }

}
SwitchShuntVariables::~SwitchShuntVariables() {}

Eigen::VectorXd SwitchShuntVariables::GetValues() const
{

}

void SwitchShuntVariables::SetVariables(const Eigen::VectorXd &x)
{

}

SwitchShuntVariables::VecBound SwitchShuntVariables::GetBounds() const
{

}


