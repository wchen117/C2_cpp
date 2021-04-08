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
        x_hak_st = Eigen::MatrixXd::Zero(swsh_ref_data->H_k0.size(), swsh_ref_data->NBL);
        x_hak_st_upbound = Eigen::MatrixXd::Zero(swsh_ref_data->H_k0.size(), swsh_ref_data->NBL);
        b_ha_st = Eigen::MatrixXd::Zero(swsh_ref_data->H_k0.size(), swsh_ref_data->NBL);

        for (size_t idx=0; idx<swsh_ref_data->H_k0.size(); idx++)
        {
            auto hk = swsh_ref_data->H_k0.at(idx);
            auto ih = swsh_ref_data->i_h[hk];
            for (auto jdx=1; jdx<=swsh_ref_data->NBL; jdx++)
            {
                auto key_ih = std::make_tuple(hk, jdx);
                x_hak_st_upbound(idx, jdx-1) = swsh_ref_data->x_ha_st_over.at(key_ih);
                x_hak_st(idx, jdx-1) = 1.0;
                b_ha_st(idx, jdx-1) = swsh_ref_data->b_ha_st.at(key_ih);


            }


        }

    }

    // size of a matrix will be row * col
    size_x_hak_st = x_hak_st.size();

    SetRows(size_x_hak_st);


}
SwitchShuntVariables::~SwitchShuntVariables() {}

Eigen::VectorXd SwitchShuntVariables::get_b_hat_st() const
{
    Eigen::VectorXd tmp_b_hat_st =  (x_hak_st.array() * b_ha_st.array()).matrix().rowwise().sum();

    return tmp_b_hat_st;
}
Eigen::VectorXd SwitchShuntVariables::GetValues() const
{
    Eigen::Map<const Eigen::VectorXd> tmp_x (x_hak_st.data(), x_hak_st.size());
    return tmp_x;
}

void SwitchShuntVariables::SetVariables(const Eigen::VectorXd &x)
{
    Eigen::Map<const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor>> M2p (x.data(), x_hak_st.rows(), x_hak_st.cols());
    x_hak_st = M2p;

}

SwitchShuntVariables::VecBound SwitchShuntVariables::GetBounds() const
{
    VecBound swsh_bounds(GetRows());
    Eigen::Map<const Eigen::VectorXd> upper_bound (x_hak_st_upbound.data(), x_hak_st_upbound.size());

    for (size_t idx=0; idx<swsh_bounds.size(); idx++)
    {
        swsh_bounds.at(idx).upper_ = upper_bound(idx);
        swsh_bounds.at(idx).lower_ = 0.0;
    }

    return swsh_bounds;

}


