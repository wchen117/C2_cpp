//
// Created by wchen on 2/26/21.
//
#include <variables/generator_variables.hpp>

GeneratorVariables::GeneratorVariables(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name): VariableSet(-1, name)
{
    gen_ref_data = data_ptr;
    if (!gen_ref_data->G_k0.empty())
    {
        size_G_k0 = gen_ref_data->G_k0.size();
        p_gnk.resize(size_G_k0);
        c_gn.resize(size_G_k0);
        p_gn_over.resize(size_G_k0);

        x_gk_on = Eigen::VectorXd::Zero(size_G_k0);
        x_gk_su = Eigen::VectorXd::Zero(size_G_k0);
        x_gk_sd = Eigen::VectorXd::Zero(size_G_k0);
        c_g_on = Eigen::VectorXd::Zero(size_G_k0);
        c_g_su = Eigen::VectorXd::Zero(size_G_k0);
        c_g_sd = Eigen::VectorXd::Zero(size_G_k0);
        // just to sure
        size_p_gnk = 0;


        for (size_t idx=0; idx<size_G_k0; idx++)
        {
            int iii;
            std::string idd;
            auto g_key= gen_ref_data->G_k0.at(idx);
            std::tie (iii, idd) = g_key;
            // again the idd read from G_k0 has \'\' around it
            idd.erase(std::remove(idd.begin(), idd.end(), '\''), idd.end());
            for (auto g: gen_ref_data->new_data.sup.generators)
            {
                if (g.bus == iii & g.id == idd)
                {
                    key_is tmp_g;
                    tmp_g = std::make_tuple(g.bus, g.id);
                    size_t Ng = g.cblocks.size();
                    p_gnk.at(idx).resize(Ng);
                    c_gn.at(idx).resize(Ng);
                    p_gn_over.at(idx).resize(Ng);
                    // intilize them to zero first
                    x_gk_on(idx) = 0.0;
                    x_gk_su(idx) = 0.0;
                    x_gk_sd(idx) = 0.0;
                    // read their coeffs
                    c_g_on(idx) = g.oncost;
                    c_g_su(idx) = g.sucost;
                    c_g_sd(idx) = g.sdcost;

                    for (size_t jdx=0; jdx<Ng; jdx++)
                    {
                        p_gnk.at(idx).at(jdx) = 0.5;
                        c_gn.at(idx).at(jdx) = g.cblocks.at(jdx).c * gen_ref_data->s_tilde;
                        p_gn_over.at(idx).at(jdx) = g.cblocks.at(jdx).pmax * gen_ref_data->s_tilde_inverse;
                        size_p_gnk++;
                    }
                }
            }

        }
        // length of p_gnk +  x_gk_on +  x_gk_su + x_gk_sd
        gen_var_len = size_p_gnk + 3 * size_G_k0;
        SetRows(gen_var_len);

    }
}

GeneratorVariables::~GeneratorVariables() {}

Eigen::VectorXd GeneratorVariables::GetValues() const
{

    if(GetRows())
    {
        size_t count = 0;
        Eigen::VectorXd tmp_x(GetRows());
        Eigen::VectorXd flat_p_gnk(size_p_gnk);




        for (size_t idx=0; idx<size_G_k0; idx++)
        {
            for (size_t jdx=0; jdx<p_gnk.at(idx).size(); jdx++)
            {
                flat_p_gnk(count) = p_gnk.at(idx).at(jdx);
                count++;

            }
        }
        assert(count == size_p_gnk);
        tmp_x << flat_p_gnk, x_gk_on, x_gk_su, x_gk_sd;
        return tmp_x;
    }
    else
    {
        exit(0);
    }
}
void GeneratorVariables::SetVariables(const Eigen::VectorXd &x)
{
    Eigen::VectorXd flat_p_gnk = x.segment(0, size_p_gnk);

    size_t count = 0;
    for (size_t idx=0; idx<size_G_k0; idx++)
    {
        for(size_t jdx=0; jdx<p_gnk.at(idx).size(); jdx++)
        {
            p_gnk.at(idx).at(jdx) = flat_p_gnk(count);
            count++;
        }
    }
    assert(count==size_p_gnk);
    x_gk_on = x.segment(size_p_gnk, size_G_k0);
    x_gk_su = x.segment(size_p_gnk+size_G_k0, size_G_k0);
    x_gk_sd = x.segment(size_p_gnk+2*size_G_k0, size_G_k0);

}

GeneratorVariables::VecBound GeneratorVariables::GetBounds() const
{
    VecBound gen_bounds(GetRows());
    // 0 < p_gnk < p_n_over
    // x_gk_* between 0 and 1

    size_t count = 0;
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd p_gnk_ub(size_p_gnk);
    for (size_t idx=0; idx<size_G_k0; idx++)
    {
        for (size_t jdx=0; jdx<p_gn_over.at(idx).size(); jdx++)
        {
            p_gnk_ub(count) = p_gn_over.at(idx).at(jdx);
            count++;
        }
    }

    Eigen::VectorXd x_gk_ub(size_G_k0);
    x_gk_ub.setOnes();
    upper_bound << p_gnk_ub, x_gk_ub, x_gk_ub, x_gk_ub;

    for (size_t idx=0; idx<gen_bounds.size(); idx++)
    {
        gen_bounds.at(idx).upper_ = upper_bound(idx);
        gen_bounds.at(idx).lower_ = 0.0;
    }

    return gen_bounds;


}