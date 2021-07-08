//
// Created by wchen on 2/26/21.
//
#include <variables/generator_variables_con.hpp>

GeneratorVariablesCon::GeneratorVariablesCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string& name): VariableSet(-1, name)
{
    gen_ref_data = data_ptr;
    if (!gen_ref_data->G_k0.empty())
    {
        size_G_k0 = gen_ref_data->G_k0.size();
        p_gnk.resize(size_G_k0);
        c_gn.resize(size_G_k0);
        p_gn_over.resize(size_G_k0);

        //q_gk only has values for infeasible solutions?
        q_gk = Eigen::VectorXd::Zero(size_G_k0);

        x_gk_on = Eigen::VectorXd::Zero(size_G_k0);
        x_gk_su = Eigen::VectorXd::Zero(size_G_k0);
        x_gk_sd = Eigen::VectorXd::Zero(size_G_k0);
        c_g_on = Eigen::VectorXd::Zero(size_G_k0);
        c_g_su = Eigen::VectorXd::Zero(size_G_k0);
        c_g_sd = Eigen::VectorXd::Zero(size_G_k0);
        //
        x_g_on_0 = Eigen::VectorXd::Zero(size_G_k0);
        p_g_over = Eigen::VectorXd::Zero(size_G_k0);
        p_g_under = Eigen::VectorXd::Zero(size_G_k0);
        q_g_over = Eigen::VectorXd::Zero(size_G_k0);
        q_g_under = Eigen::VectorXd::Zero(size_G_k0);
        p_g_ru_over = Eigen::VectorXd::Zero(size_G_k0);
        p_g_rd_over = Eigen::VectorXd::Zero(size_G_k0);
        p_g_0 = Eigen::VectorXd::Zero(size_G_k0);

        G_su_value = Eigen::VectorXi::Zero(size_G_k0);
        G_sd_value = Eigen::VectorXi::Zero(size_G_k0);

        gen_i_g = Eigen::VectorXi::Zero(size_G_k0);
        gen_id_g = Eigen::VectorXi::Zero(size_G_k0);
        // just to sure
        size_p_gnk = 0;



        auto basecase_generators = get_base_gen_var();
        x_gk_on_base = Eigen::VectorXd::Zero(size_G_k0);
        x_gk_su_base = Eigen::VectorXd::Zero(size_G_k0);
        x_gk_sd_base = Eigen::VectorXd::Zero(size_G_k0);
        q_gk_base = Eigen::VectorXd::Zero(size_G_k0);
        p_gk_base = Eigen::VectorXd::Zero(size_G_k0);


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

                    size_t Ng = g.cblocks.size();
                    p_gnk.at(idx).resize(Ng);
                    c_gn.at(idx).resize(Ng);
                    p_gn_over.at(idx).resize(Ng);
                    // intilize them to zero first, 1 is start
                    x_gk_on(idx) = 0.0;
                    x_gk_su(idx) = 0.0;
                    x_gk_sd(idx) = 0.0;
                    // read their coeffs
                    c_g_on(idx) = g.oncost;
                    c_g_su(idx) = g.sucost;
                    c_g_sd(idx) = g.sdcost;
                    // if they are in G_su_ct or G_sd_ct
                    G_su_value(idx) = g.suqualctg;
                    G_sd_value(idx) = g.sdqualctg;

                    // eqn(82) and eqn(83)
                    x_g_on_0(idx) = gen_ref_data->x_g_on_0[g_key];
                    p_g_over(idx) = gen_ref_data->p_g_over[g_key];
                    p_g_under(idx) = gen_ref_data->p_g_under[g_key];
                    q_g_over(idx) = gen_ref_data->q_g_over[g_key];
                    q_g_under(idx) = gen_ref_data->q_g_under[g_key];
                    // so....
                    p_g_ru_over(idx) = g.prumaxctg;
                    p_g_rd_over(idx) = g.prdmaxctg;
                    p_g_0(idx) = gen_ref_data->p_g_0[g_key];

                    gen_i_g(idx) = iii;
                    gen_id_g(idx) = stoi(idd);


                    for (size_t jdx=0; jdx<Ng; jdx++)
                    {
                        p_gnk.at(idx).at(jdx) = 0.5;
                        c_gn.at(idx).at(jdx) = g.cblocks.at(jdx).c * gen_ref_data->s_tilde;
                        p_gn_over.at(idx).at(jdx) = g.cblocks.at(jdx).pmax * gen_ref_data->s_tilde_inverse;
                        size_p_gnk++;
                    }
                }
            }

            // read in the base case gen vars, make sure the one-to-one corresponds
            for (auto const &bg: basecase_generators)
            {
                if (bg->i == iii & bg->id == std::stoi(idd))
                {
                    x_gk_on_base(idx) = bg->x_gk_on;
                    x_gk_su_base(idx) = bg->x_gk_su;
                    x_gk_sd_base(idx) = bg->x_gk_sd;
                    p_gk_base(idx) = bg->p_gk;
                    q_gk_base(idx) = bg->q_gk;


                }

            }

        }




        // length of p_gnk + q_gk + x_gk_on +  x_gk_su + x_gk_sd
        gen_var_len = size_p_gnk + 4 * size_G_k0;
        SetRows(gen_var_len);

    }
}

GeneratorVariablesCon::~GeneratorVariablesCon() {}

Eigen::VectorXd GeneratorVariablesCon::GetValues() const
{

    if(GetRows())
    {
        auto test = get_p_gk();

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
        tmp_x << flat_p_gnk, q_gk, x_gk_on, x_gk_su, x_gk_sd;
        return tmp_x;
    }
    else
    {
        exit(0);
    }
}
void GeneratorVariablesCon::SetVariables(const Eigen::VectorXd &x)
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
    q_gk = x.segment(size_p_gnk, size_G_k0);
    x_gk_on = x.segment(size_p_gnk+size_G_k0, size_G_k0);
    x_gk_su = x.segment(size_p_gnk+2*size_G_k0, size_G_k0);
    x_gk_sd = x.segment(size_p_gnk+3*size_G_k0, size_G_k0);

}

GeneratorVariablesCon::VecBound GeneratorVariablesCon::GetBounds() const
{
    VecBound gen_bounds(GetRows());
    // 0 < p_gnk < p_n_over
    // x_gk_* between 0 and 1

    size_t count = 0;
    Eigen::VectorXd upper_bound(GetRows());
    Eigen::VectorXd lower_bound(GetRows());
    Eigen::VectorXd p_gnk_ub(size_p_gnk);
    Eigen::VectorXd q_gk_lb = Eigen::VectorXd::Zero(size_G_k0);
    Eigen::VectorXd q_gk_ub = Eigen::VectorXd::Zero(size_G_k0);
    Eigen::VectorXd p_gnk_lb = Eigen::VectorXd::Zero(size_p_gnk);
    Eigen::VectorXd x_gk_su_lb = Eigen::VectorXd::Zero(size_G_k0);
    q_gk_lb.setConstant(-1e20);
    q_gk_ub.setConstant(1e20);

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
    upper_bound << p_gnk_ub, q_gk_ub, x_gk_ub, x_gk_ub, x_gk_ub;
    lower_bound << p_gnk_lb, q_gk_lb, x_gk_su_lb, x_gk_su_lb, x_gk_su_lb;

    for (size_t idx=0; idx<gen_bounds.size(); idx++)
    {
        gen_bounds.at(idx).upper_ = upper_bound(idx);
        gen_bounds.at(idx).lower_ = lower_bound(idx);
    }

    return gen_bounds;

}

Eigen::VectorXd GeneratorVariablesCon::get_p_gk() const
{

    Eigen::VectorXd p_gk = Eigen::VectorXd::Zero(p_gnk.size());

    for (size_t idx=0; idx<p_gnk.size(); idx++)
    {
        for (size_t jdx=0; jdx<p_gnk.at(idx).size(); jdx++)
        {
            p_gk(idx) += p_gnk.at(idx).at(jdx);
        }
    }

    return p_gk;

}

std::string GeneratorVariablesCon::read_to_string(std::string file_name)
{
    // read in case.raw file into a string
    std::ifstream input(file_name, std::ios::in | std::ios::binary);
    input.clear();
    if (input)
    {
        std::string container;
        input.seekg(0, std::ios::end);
        container.resize(input.tellg());
        input.seekg(0, std::ios::beg);
        input.read(&container[0], container.size());
        input.close();
        return container;

    }
    throw(errno);
}

std::vector<std::string> GeneratorVariablesCon::parse_on_delimiter(std::string const &input_string, std::string delimiter)
{
    std::vector<std::string> parsed_string_vector;
    std::size_t start = 0;
    std::size_t end = input_string.find(delimiter);

    while(end != std::string::npos)
    {
        parsed_string_vector.push_back(input_string.substr(start, end - start));
        start = end + delimiter.length();
        end = input_string.find(delimiter, start);
    }
    parsed_string_vector.push_back(input_string.substr(start, std::string::npos));

    return parsed_string_vector;

}

std::vector<std::shared_ptr<GeneratorVariablesCon::read_generator>> GeneratorVariablesCon::get_base_gen_var()
{
    std::string additional_var = "additional_generator_varBASECASE.txt";

    std::string content = read_to_string(additional_var);
    std::vector<std::string> vector_string = parse_on_delimiter(content, "--");

    std::vector<std::shared_ptr<read_generator>> generator_ref_vec;

    for (size_t idx=0; idx<vector_string.size(); idx++)
    {
        std::string const& section = vector_string.at(idx);
        std::vector<std::string> lines_vector = parse_on_delimiter(section, "\n");

        if (lines_vector.at(0) == "generator section")
        {
            // first two lines not numbers, last line empty
            for (size_t jdx=2; jdx<lines_vector.size()-1; jdx++)
            {
                std::string const& line = lines_vector.at(jdx);
                std::vector<std::string> num_vec = parse_on_delimiter(line, ",");
                auto tmp_gen = std::make_shared<read_generator>();
                tmp_gen->i = std::stoi(num_vec.at(0));
                tmp_gen->id = std::stoi(num_vec.at(1));
                tmp_gen->p_gk = std::stod(num_vec.at(2));
                tmp_gen->q_gk = std::stod(num_vec.at(3));
                tmp_gen->x_gk_on = std::stod(num_vec.at(4));
                tmp_gen->x_gk_su = std::stod(num_vec.at(5));
                tmp_gen->x_gk_sd = std::stod(num_vec.at(6));
                generator_ref_vec.push_back(tmp_gen);

            }

        }



    }
    return generator_ref_vec;

}