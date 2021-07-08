//
// Created by wchen on 3/31/21.
//
#include <constraints/generator_constraints_con.hpp>

GeneratorConstraintsCon::GeneratorConstraintsCon(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    SetRows(12 * data_ptr->G_k0.size());
    gen_var_name = name;

}

GeneratorConstraintsCon::~GeneratorConstraintsCon() {}

Eigen::VectorXd GeneratorConstraintsCon::GetValues() const
{
    Eigen::VectorXd gen_cons(GetRows());
    const Eigen::VectorXd Eqn83 = gen_var_ptr->x_gk_on - gen_var_ptr->x_gk_on_base - gen_var_ptr->x_gk_su + gen_var_ptr->x_gk_sd;
    const Eigen::VectorXd Eqn84 = ((gen_var_ptr->x_gk_su + gen_var_ptr->x_gk_sd).array() - 1.0).matrix();

    // p_gk = \sum_n p_gnk
    Eigen::VectorXd p_gk = Eigen::VectorXd::Zero(gen_var_ptr->p_gnk.size());
    size_t count = 0;
    for (size_t idx=0; idx<gen_var_ptr->p_gnk.size(); idx++)
    {
        for (size_t jdx=0; jdx<gen_var_ptr->p_gnk.at(idx).size(); jdx++)
        {
            p_gk(idx) += gen_var_ptr->p_gnk.at(idx).at(jdx);
        }
    }


    const Eigen::VectorXd Eqn85_right = p_gk - (gen_var_ptr->p_g_over.array() * gen_var_ptr->x_gk_on.array()).matrix();
    const Eigen::VectorXd Eqn85_left = p_gk - (gen_var_ptr->p_g_under.array() * gen_var_ptr->x_gk_on.array()).matrix();
    const Eigen::VectorXd Eqn86_right = gen_var_ptr->q_gk - (gen_var_ptr->q_g_over.array() * gen_var_ptr->x_gk_on.array()).matrix();
    const Eigen::VectorXd Eqn86_left = gen_var_ptr->q_gk - (gen_var_ptr->q_g_under.array() * gen_var_ptr->x_gk_on.array()).matrix();

    const double &delta_r = gen_var_ptr->gen_ref_data->new_data.sup.sys_prms["deltar"];
    // Eqn(89) and Eqn(90)
    const Eigen::VectorXd Eqn89 = (p_gk.array() - (gen_var_ptr->p_gk_base + gen_var_ptr->p_g_ru_over * delta_r).array() \
                                           * (gen_var_ptr->x_gk_on - gen_var_ptr->x_gk_su).array() - (gen_var_ptr->p_g_under + gen_var_ptr->p_g_ru_over * delta_r).array() * gen_var_ptr->x_gk_su.array()).matrix();
    const Eigen::VectorXd Eqn90 = (p_gk.array() - (gen_var_ptr->p_gk_base - gen_var_ptr->p_g_rd_over * delta_r).array() \
                                           * (gen_var_ptr->x_gk_on - gen_var_ptr->x_gk_su).array()).matrix();
    Eigen::VectorXd Eqn95 = gen_var_ptr->x_gk_su_base.array() + gen_var_ptr->x_gk_sd.array() - 1.0;
    Eigen::VectorXd Eqn96 = gen_var_ptr->x_gk_sd_base.array() + gen_var_ptr->x_gk_su.array() - 1.0;

    gen_cons << Eqn83, Eqn84, Eqn85_right, Eqn85_left, Eqn86_right, Eqn86_left, Eqn89, Eqn90, gen_var_ptr->x_gk_su, gen_var_ptr->x_gk_sd, Eqn95, Eqn96;

    return gen_cons;
}

GeneratorConstraintsCon::VecBound GeneratorConstraintsCon::GetBounds() const
{
    VecBound gen_con_bounds(GetRows());
    Eigen::VectorXd upper_bounds(GetRows());
    Eigen::VectorXd lower_bounds(GetRows());
    // now the upper and lower bound for each individual component
    // eqn(82)
    Eigen::VectorXd Eqn82_up_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);
    Eigen::VectorXd Eqn82_lo_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);

    // eqn(84)
    Eigen::VectorXd Eqn84_up_bound(gen_var_ptr->size_G_k0);
    Eqn84_up_bound.setOnes();
    Eigen::VectorXd Eqn84_lo_bound(gen_var_ptr->size_G_k0);
    Eqn84_lo_bound.setConstant(-1e20);

    // eqn(85), right hand size
    Eigen::VectorXd Eqn85_right_up_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);
    Eigen::VectorXd Eqn85_right_lo_bound(gen_var_ptr->size_G_k0);
    Eqn85_right_lo_bound.setConstant(-1e20);

    // eqn(85), left hand size
    Eigen::VectorXd Eqn85_left_up_bound(gen_var_ptr->size_G_k0);
    Eqn85_left_up_bound.setConstant(1e20);
    Eigen::VectorXd Eqn85_left_lo_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);

    // eqn(86), right hand size
    Eigen::VectorXd Eqn86_right_up_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);
    Eigen::VectorXd Eqn86_right_lo_bound(gen_var_ptr->size_G_k0);
    Eqn86_right_lo_bound.setConstant(-1e20);

    // eqn(86), left hand size
    Eigen::VectorXd Eqn86_left_up_bound(gen_var_ptr->size_G_k0);
    Eqn86_left_up_bound.setConstant(1e20);
    Eigen::VectorXd Eqn86_left_lo_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);

    // eqn(87)
    Eigen::VectorXd Eqn87_up_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);
    Eigen::VectorXd Eqn87_lo_bound(gen_var_ptr->size_G_k0);
    Eqn87_lo_bound.setConstant(-1e20);

    // eqn(88)
    Eigen::VectorXd Eqn88_up_bound(gen_var_ptr->size_G_k0);
    Eqn88_up_bound.setConstant(1e20);
    Eigen::VectorXd Eqn88_lo_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);

    // eqn (91) and (93)
    Eigen::VectorXd Eqn91_up_bound(gen_var_ptr->size_G_k0);
    Eqn91_up_bound.setOnes();
    Eigen::VectorXd Eqn91_lo_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);

    Eigen::VectorXd Eqn93_up_bound(gen_var_ptr->size_G_k0);
    Eqn91_up_bound.setOnes();
    Eigen::VectorXd Eqn93_lo_bound = Eigen::VectorXd::Zero(gen_var_ptr->size_G_k0);

    for (size_t idx=0; idx<gen_var_ptr->size_G_k0; idx++)
    {

        if(gen_var_ptr->G_su_value(idx) == 0)
        {
            Eqn91_up_bound(idx) = 0;

        }
        if(gen_var_ptr->G_su_value(idx) == 0)
        {
            Eqn93_up_bound(idx) = 0;
        }
    }

    // eqn(95) and eqn(96) have zero up bound, -infty lower bound;
    auto const& Eqn9596_up_bound = Eqn87_up_bound;
    auto const& Eqn9596_low_bound = Eqn87_lo_bound;


    upper_bounds << Eqn82_up_bound, Eqn84_up_bound, Eqn85_right_up_bound, Eqn85_left_up_bound, Eqn86_right_up_bound, \
                    Eqn86_left_up_bound, Eqn87_up_bound, Eqn88_up_bound, Eqn91_up_bound, Eqn93_up_bound, Eqn9596_up_bound, Eqn9596_up_bound;
    lower_bounds <<  Eqn82_lo_bound, Eqn84_lo_bound, Eqn85_right_lo_bound, Eqn85_left_lo_bound, Eqn86_right_lo_bound, \
                    Eqn86_left_lo_bound, Eqn87_lo_bound, Eqn88_lo_bound, Eqn91_lo_bound, Eqn93_lo_bound, Eqn87_lo_bound, Eqn87_lo_bound;

    for (size_t idx=0; idx<gen_con_bounds.size(); idx++)
    {
        // if apply strick bound, it's having a hard time to converge
        //gen_con_bounds.at(idx).upper_ = 10;
        //gen_con_bounds.at(idx).lower_ = -10;
        // relax bound by +- 1
        gen_con_bounds.at(idx).upper_ = upper_bounds(idx) + 1;
        gen_con_bounds.at(idx).lower_ = lower_bounds(idx) - 1;

    }

    return gen_con_bounds;

}

void GeneratorConstraintsCon::InitVariableDependedQuantities(const VariablesPtr& x)
{
    gen_var_ptr = x->GetComponent<GeneratorVariablesCon>(gen_var_name);
}
void GeneratorConstraintsCon::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{
     if (var_set == gen_var_name)
    {
    typedef Eigen::Triplet<double> T;
        std::vector<T> generator_triplets;

        const auto &delta_r = gen_var_ptr->gen_ref_data->new_data.sup.sys_prms["deltar"];

        for(size_t idx=0; idx<gen_var_ptr->size_G_k0;idx++)
        {
            // eqn(82) wrt to x_gk_on
            generator_triplets.push_back(T(idx, gen_var_ptr->size_p_gnk+gen_var_ptr->size_G_k0+idx, 1.0));
            // eqn(82) wrt to x_gk_su
            generator_triplets.push_back(T(idx, gen_var_ptr->size_p_gnk+2*gen_var_ptr->size_G_k0+idx, -1.0));
            // eqn(82) wrt to x_gk_sd
            generator_triplets.push_back(T(idx, gen_var_ptr->size_p_gnk+3*gen_var_ptr->size_G_k0+idx, 1.0));
            // eqn(84) wrt to x_gk_on
            generator_triplets.push_back(T(gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+2*gen_var_ptr->size_G_k0+idx, 1.0));
            // eqn(83) wrt to x_gk_sd
            generator_triplets.push_back(T(gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+3*gen_var_ptr->size_G_k0+idx, 1.0));
            // eqn(85) right hand side wrt to x_gk_on
            generator_triplets.push_back(T(2*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+gen_var_ptr->size_G_k0+idx, -gen_var_ptr->p_g_over(idx)));
            // eqn(85) left hand side wrt to x_gk_on
            generator_triplets.push_back(T(3*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+gen_var_ptr->size_G_k0+idx, -gen_var_ptr->p_g_under(idx)));
            // eqn(86) right hand side wrt to q_gk
            generator_triplets.push_back(T(4*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+idx, 1.0));
            // eqn(86) left hand side wrt to q_gk
            generator_triplets.push_back(T(5*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+idx, 1.0));
            // eqn(86) right hand side wrt to x_gk_on
            generator_triplets.push_back(T(4*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+gen_var_ptr->size_G_k0+idx, -gen_var_ptr->q_g_over(idx)));
            // eqn(86) left hand side wrt to x_gk_on
            generator_triplets.push_back(T(5*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+gen_var_ptr->size_G_k0+idx, -gen_var_ptr->q_g_under(idx)));
            // eqn(87) wrt to x_gk_on
            generator_triplets.push_back(T(6*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+gen_var_ptr->size_G_k0+idx, -(gen_var_ptr->p_g_0(idx) + gen_var_ptr->p_g_rd_over(idx) * delta_r)));
            //std::cout<<"indices are "<<6*gen_var_ptr->size_G_k0 + idx<<" and "<< gen_var_ptr->size_p_gnk+gen_var_ptr->size_G_k0+idx<<std::endl;
            // eqn(87) wrt to x_gk_su
            generator_triplets.push_back(T(6*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+2*gen_var_ptr->size_G_k0+idx, gen_var_ptr->p_g_0(idx) - gen_var_ptr->p_g_under(idx)));
            // eqn(88) wrt to x_gk_on
            generator_triplets.push_back(T(7*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+gen_var_ptr->size_G_k0+idx, -gen_var_ptr->p_g_0(idx) + gen_var_ptr->p_g_rd_over(idx) * delta_r));
            // eqn(88) wrt to x_gk_su
            generator_triplets.push_back(T(7*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+2*gen_var_ptr->size_G_k0+idx, gen_var_ptr->p_g_0(idx) - gen_var_ptr->p_g_rd_over(idx) * delta_r));
            // eqn(91) wrt to x_gk_su
            generator_triplets.push_back(T(8*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+2*gen_var_ptr->size_G_k0+idx, 1.0));
            // eqn(92) wrt to x_gk_sd
            generator_triplets.push_back(T(9*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+3*gen_var_ptr->size_G_k0+idx, 1.0));
            // eqn(95) wrt tp x_gk_sd
            generator_triplets.push_back(T(10*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+3*gen_var_ptr->size_G_k0+idx, 1.0));
            // eqn(96) wrt to x_gk_su
            generator_triplets.push_back(T(11*gen_var_ptr->size_G_k0 + idx, gen_var_ptr->size_p_gnk+2*gen_var_ptr->size_G_k0+idx, 1.0));
        }

        size_t sum_len = 0;
        for (size_t idx=0; idx<gen_var_ptr->p_gnk.size(); idx++)
        {
            for (size_t jdx=0; jdx<gen_var_ptr->p_gnk.at(idx).size(); jdx++)
            {
                // eqn(85) right hand side wrt to flat_p_gnk
                generator_triplets.push_back(T(2*gen_var_ptr->size_G_k0+idx, jdx+sum_len, 1.0));
                // eqn(85) left hand size wrt to flat_p_gnk
                generator_triplets.push_back(T(3*gen_var_ptr->size_G_k0+idx, jdx+sum_len, 1.0));
                // eqn(87) wrt to flat_p_gnk
                generator_triplets.push_back(T(6*gen_var_ptr->size_G_k0+idx, jdx+sum_len, 1.0));
                // eqn(88) wrt to flat_p_gnk
                generator_triplets.push_back(T(7*gen_var_ptr->size_G_k0+idx, jdx+sum_len, 1.0));
                
            }
            sum_len += gen_var_ptr->p_gnk.at(idx).size();
        }

        jac_block.setFromTriplets(generator_triplets.begin(), generator_triplets.end());
    

    }
    

}