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
        x_gk_on.resize(size_G_k0);
        x_gk_su.resize(size_G_k0);
        x_gk_sd.resize(size_G_k0);
        c_g_on.resize(size_G_k0);
        c_g_su.resize(size_G_k0);
        c_g_sd.resize(size_G_k0);
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
                    x_gk_on.at(idx) = 0.0;
                    x_gk_su.at(idx) = 0.0;
                    x_gk_sd.at(idx) = 0.0;
                    // read their coeffs
                    c_g_on.at(idx) = g.oncost;
                    c_g_su.at(idx) = g.sucost;
                    c_g_sd.at(idx) = g.sdcost;

                    for (size_t jdx=0; jdx<Ng; jdx++)
                    {
                        p_gnk.at(idx).at(jdx) = 0.0;
                        c_gn.at(idx).at(jdx) = g.cblocks.at(jdx).c * gen_ref_data->s_tilde;
                        p_gn_over.at(idx).at(jdx) = g.cblocks.at(jdx).pmax * gen_ref_data->s_tilde_inverse;
                        size_p_gnk++;
                    }
                }
            }

        }
        // length of p_gnk +  x_gk_on +  x_gk_su + x_gk_sd
        SetRows(size_p_gnk + 3 * size_G_k0);

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
        Eigen::VectorXd eigen_x_gk_on(x_gk_on.data(), x_gk_on.size());
        Eigen::VectorXd eigen_x_gk_su(x_gk_su.data(), x_gk_su.size());
        Eigen::VectorXd eigen_x_gk_sd(x_gk_sd.data(), x_gk_sd.size());

        for (size_t idx=0; idx<size_G_k0; idx++)
        {
            for (size_t jdx=0; jdx<p_gnk.at(idx).size(); jdx++)
            {
                flat_p_gnk(count) = p_gnk.at(idx).at(jdx);
                count++;

            }
        }
        tmp_x << flat_p_gnk, eigen_x_gk_on, eigen_x_gk_su,eigen_x_gk_sd;
        return tmp_x;
    }
    else
    {
        exit(0);
    }
}
void GeneratorVariables::SetVariables(const Eigen::VectorXd &x)
{


}
GeneratorVariables::VecBound GeneratorVariables::GetBounds() const
{

}