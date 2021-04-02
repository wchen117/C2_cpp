//
// Created by wchen on 3/31/21.
//
#include <constraints/generator_constraints.hpp>

GeneratorConstraints::GeneratorConstraints(const std::shared_ptr<Wrapper_Construct> data_ptr, const std::string &name) : ifopt::ConstraintSet(-1, name + "_constraint")
{
    SetRows(10 * data_ptr->G_k0.size());
    gen_var_name = name;

}

GeneratorConstraints::~GeneratorConstraints() {}

Eigen::VectorXd GeneratorConstraints::GetValues() const
{
    Eigen::VectorXd gen_cons(GetRows());
    const Eigen::VectorXd Eqn82 = gen_var_ptr->x_gk_on - gen_var_ptr->x_g_on_0 - gen_var_ptr->x_gk_su + gen_var_ptr->x_gk_sd;
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
    const Eigen::VectorXd Eqn87 = (p_gk.array() - (gen_var_ptr->p_g_0 + gen_var_ptr->p_g_ru_over * delta_r).array() \
                                           * (gen_var_ptr->x_gk_on - gen_var_ptr->x_gk_su).array() + (gen_var_ptr->p_g_under + gen_var_ptr->p_g_ru_over * delta_r).array() * gen_var_ptr->x_gk_su.array()).matrix();
    const Eigen::VectorXd Eqn88 = (p_gk.array() - (gen_var_ptr->p_g_0 - gen_var_ptr->p_g_rd_over * delta_r).array() \
                                           * (gen_var_ptr->x_gk_on - gen_var_ptr->x_gk_su).array()).matrix();

    gen_cons << Eqn82, Eqn84, Eqn85_right, Eqn85_left, Eqn86_right, Eqn86_left, Eqn87, Eqn88, gen_var_ptr->x_gk_su, gen_var_ptr->x_gk_sd;

    return gen_cons;
}

GeneratorConstraints::VecBound GeneratorConstraints::GetBounds() const
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

    upper_bounds << Eqn82_up_bound, Eqn84_up_bound, Eqn85_right_up_bound, Eqn85_left_up_bound, Eqn86_right_up_bound, \
                    Eqn86_left_up_bound, Eqn87_up_bound, Eqn88_up_bound, Eqn91_up_bound, Eqn93_up_bound;
    lower_bounds <<  Eqn82_lo_bound, Eqn84_lo_bound, Eqn85_right_lo_bound, Eqn85_left_lo_bound, Eqn86_right_lo_bound, \
                    Eqn86_left_lo_bound, Eqn87_lo_bound, Eqn88_lo_bound, Eqn91_lo_bound, Eqn93_lo_bound;

    for (size_t idx=0; idx<gen_con_bounds.size(); idx++)
    {
        // if apply strick bound, it's having a hard time to converge
        //gen_con_bounds.at(idx).upper_ = 1e10;
        //gen_con_bounds.at(idx).lower_ = 1e-10;
        gen_con_bounds.at(idx).upper_ = upper_bounds(idx);
        gen_con_bounds.at(idx).lower_ = lower_bounds(idx);

    }

    return gen_con_bounds;

}

void GeneratorConstraints::InitVariableDependedQuantities(const VariablesPtr& x)
{
    gen_var_ptr = x->GetComponent<GeneratorVariables>(gen_var_name);
}
void GeneratorConstraints::FillJacobianBlock(std::string var_set, Jacobian& jac_block) const
{

}