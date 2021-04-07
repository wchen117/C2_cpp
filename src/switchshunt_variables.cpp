//
// Created by wchen on 3/19/21.
//
#include <variables/switch_shunt_variables.hpp>

SwitchShuntVariables::SwitchShuntVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name) : VariableSet(-1, name)
{
    swsh_ref_data = data_ptr;

    // variable x_hak_st defined in eq(46)
    if (!swsh_ref_data->H_k0.empty())
    {
        x_hak_st.resize(swsh_ref_data->H_k0.size());

        for (size_t idx=0; idx<swsh_ref_data->H_k0.size(); idx++)
        {
            auto hk = swsh_ref_data->H_k0.at(idx);
            auto ih = swsh_ref_data->i_h[hk];
            for (auto jdx=1; jdx<=swsh_ref_data->NBL; jdx++)
            {
                auto key_ih = std::make_tuple(hk, jdx);
                auto x_ha_st_over = swsh_ref_data->x_ha_st_over.at(key_ih);



            }


        }
        for (auto sw: swsh_ref_data->x_ha_st_over)
        {
            int h, a;
            std::tie(h, a) = sw.first;
            std::cout<<"h = "<<h<<" a = "<< a<<" sw = "<<sw.second<<std::endl;
        }


    }
    //SetRows(10);


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


