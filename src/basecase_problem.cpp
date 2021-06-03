//
// Created by wchen on 4/15/21.
//
#include <basecase_problem.hpp>

BaseCaseProblem::BaseCaseProblem(const std::string& input_dir)
{
    input_path = input_dir;
    input_ptr =  std::make_shared<Wrapper_Construct>(input_path);

    bus_vars_ptr = std::make_shared<BusVariables>(input_ptr, bus_var_name);

    load_vars_ptr = std::make_shared<LoadVariables>(input_ptr, load_var_name);
    load_cons_ptr = std::make_shared<LoadConstraints>(input_ptr, load_var_name);
    load_cost_ptr = std::make_shared<LoadCosts>(load_var_name);

    switch_shunt_vars_ptr = std::make_shared<SwitchShuntVariables>(input_ptr, swsh_var_name);

    line_vars_ptr = std::make_shared<LineVariables>(input_ptr, bus_vars_ptr, line_var_name);
    line_cons_ptr = std::make_shared<LineConstraints>(input_ptr, line_var_name);
    line_cost_ptr = std::make_shared<LineCosts>(line_var_name);

    trans_vars_ptr = std::make_shared<TransformerVariables>(input_ptr, bus_vars_ptr, trans_var_name);
    trans_cons_ptr = std::make_shared<TransConstraints>(input_ptr, trans_vars_ptr, trans_var_name);
    trans_cost_ptr = std::make_shared<TransformerCosts>(trans_var_name);

    gen_vars_ptr = std::make_shared<GeneratorVariables>(input_ptr, gen_var_name);
    gen_cons_ptr = std::make_shared<GeneratorConstraints>(input_ptr, gen_var_name);
    gen_cost_ptr = std::make_shared<GenCosts>(gen_var_name);

    bus_cons_ptr = std::make_shared<BusConstraints>(input_ptr, bus_var_name, load_var_name, \
                                                         line_var_name, swsh_var_name, trans_var_name, gen_var_name);
    bus_cost_ptr = std::make_shared<BusCosts>(bus_var_name);

    //nlp.AddVariableSet(load_vars_ptr);
    //nlp.AddConstraintSet(load_cons_ptr);
    //nlp.AddCostSet(load_cost_ptr);

    //nlp.AddVariableSet(switch_shunt_vars_ptr);

    nlp.AddVariableSet(line_vars_ptr);
    nlp.AddConstraintSet(line_cons_ptr);
    nlp.AddCostSet(line_cost_ptr);

    //nlp.AddVariableSet(trans_vars_ptr);
    //nlp.AddConstraintSet(trans_cons_ptr);
    //nlp.AddCostSet(trans_cost_ptr);

    //nlp.AddVariableSet(gen_vars_ptr);
    //nlp.AddConstraintSet(gen_cons_ptr);
    //nlp.AddCostSet(gen_cost_ptr);

    //nlp.AddVariableSet(bus_vars_ptr);
    //nlp.AddConstraintSet(bus_cons_ptr);
    //nlp.AddCostSet(bus_cost_ptr);
    nlp.PrintCurrent();




}
BaseCaseProblem::~BaseCaseProblem()
{}
void BaseCaseProblem::Solve()
{
    // 2. choose solver and options

    ifopt::IpoptSolver ipopt;
    //ipopt.SetOption("linear_solver", "ma97");
    ipopt.SetOption("jacobian_approximation", "exact");
    //ipopt.SetOption("jacobian_approximation", "finite-difference-values");
    //ipopt.SetOption("check_derivatives_for_naninf", "yes");
    ipopt.SetOption("derivative_test", "first-order");
    //ipopt.SetOption("bound_relax_factor", 1);
    ipopt.SetOption("print_level", 4);
    ipopt.SetOption("output_file", "output.txt");
    ipopt.SetOption("max_iter", 100);
    ipopt.SetOption("max_cpu_time", 1e3);
    ipopt.Solve(nlp);

    Eigen::VectorXd x = nlp.GetOptVariables()->GetValues();

    std::cout<<"x = "<<x.transpose()<<std::endl;

    //std::cout<<"g_fk = "<<trans_vars_ptr->g_fk.transpose()<<std::endl;
    //std::cout<<"b_fk = "<<trans_vars_ptr->b_fk.transpose()<<std::endl;


    nlp.PrintCurrent();

    //std::cout<<"x_ek_sw = "<<line_vars_ptr->x_ek_sw.transpose()<<std::endl;
    //std::cout<<"x_fk_sw = "<<trans_vars_ptr->x_fk_sw.transpose()<<std::endl;
    //std::cout<<"x_gk_on = "<<gen_vars_ptr->x_gk_on.transpose()<<std::endl;
    //std::cout<<"x_gk_su = "<<gen_vars_ptr->x_gk_su.transpose()<<std::endl;
    //std::cout<<"x_gk_sd = "<<gen_vars_ptr->x_gk_sd.transpose()<<std::endl;
    std::cout<<"eq_70_var = "<<trans_vars_ptr->eq70_binary_variable.transpose()<<std::endl;
    std::cout<<"eta fk = "<<trans_vars_ptr->eta_fk.transpose()<<std::endl;
    std::cout<<"tau fk = "<<trans_vars_ptr->tau_fk.transpose()<<std::endl;


}
void BaseCaseProblem::WriteOutputFile()
{
    std::ofstream outputfile;
    outputfile.open("solution_" + input_ptr->label_k_0 + ".txt");
    outputfile << "--bus section\ni, v, theta\n";
    for (size_t idx=0; idx<bus_vars_ptr->sorted_bus_ID.size(); idx++)
    {
        outputfile <<bus_vars_ptr->sorted_bus_ID.at(idx)<<", "<<bus_vars_ptr->v_ik(idx)<<", "<<bus_vars_ptr->theta_ik(idx)<<std::endl;

    }
    outputfile << "--load section\ni, id, t\n";
    for(size_t idx=0; idx<input_ptr->J_k0.size(); idx++)
    {
        outputfile <<load_vars_ptr->load_i(idx)<<", "<<load_vars_ptr->load_id_j(idx)<<", "<<load_vars_ptr->t_jk(idx)<<std::endl;

    }
    outputfile << "--generator section\ni, id, p, q, x\n";
    auto p_gk =gen_vars_ptr->get_p_gk();
    for (size_t idx=0; idx<input_ptr->G_k0.size(); idx++)
    {
        outputfile <<gen_vars_ptr->gen_i_g(idx)<<", "<<gen_vars_ptr->gen_id_g(idx)<<", "<<p_gk(idx)<<", "<<gen_vars_ptr->q_gk(idx)<<", "<<gen_vars_ptr->x_gk_on(idx)<<std::endl;
    }
    outputfile << "--line section\niorig, idest, id, x\n";

    for (size_t idx=0; idx<input_ptr->E_k0.size(); idx++)
    {
        outputfile <<line_vars_ptr->ref_oribus(idx)<<", "<<line_vars_ptr->ref_desbus(idx)<<", "<<line_vars_ptr->ref_id(idx)<<", "<<line_vars_ptr->x_ek_sw(idx)<<std::endl;
    }
    outputfile <<"--transformer section\niorig, idest, id, x, xst\n";

    for (size_t idx=0; idx<input_ptr->F_k0.size(); idx++)
    {
        outputfile <<trans_vars_ptr->ref_oribus(idx)<<", "<<trans_vars_ptr->ref_desbus(idx)<<", "<<trans_vars_ptr->ref_id(idx)<<", "<<trans_vars_ptr->x_fk_sw(idx)<<", "<<trans_vars_ptr->x_fk_st(idx)<<std::endl;

    }

    outputfile <<" --switched shunt section\ni, xst1, xst2, xst3, xst4, xst5, xst6, xst7, xst8\n";


    for (size_t idx=0; idx<input_ptr->H_k0.size(); idx++)
    {
        outputfile <<switch_shunt_vars_ptr->swsh_ih(idx)<<", ";

        for (size_t jdx=1; jdx<=input_ptr->NBL; jdx++)
            outputfile << switch_shunt_vars_ptr->x_hak_st(idx, jdx-1)<<", ";

        outputfile << "\n";

    }
    outputfile.close();

    std::ofstream additional_outfile;
    additional_outfile.open("additional_generator_var" + input_ptr->label_k_0 + ".txt");
    additional_outfile << "--generator section\ni, id, p, q, x_gk_on, x_gk_su, x_gk_sd\n";

    for (size_t idx=0; idx<input_ptr->G_k0.size(); idx++)
    {
        additional_outfile <<gen_vars_ptr->gen_i_g(idx)<<", "<<gen_vars_ptr->gen_id_g(idx)<<", "<<p_gk(idx)<<", "<<gen_vars_ptr->q_gk(idx)<<", "<<gen_vars_ptr->x_gk_on(idx)<<", "<<gen_vars_ptr->x_gk_su(idx)<<", "<<gen_vars_ptr->x_gk_sd(idx)<<std::endl;
    }
    additional_outfile.close();















}
