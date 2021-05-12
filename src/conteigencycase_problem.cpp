//
// Created by wchen on 5/11/21.
//
#include <contigencycase_problem.hpp>

ContigencyCaseProblem::ContigencyCaseProblem(const std::string& input_dir)
{
    input_path = input_dir;
    input_ptr =  std::make_shared<Wrapper_Construct>(input_path);

    bus_vars_ptr = std::make_shared<BusVariables>(input_ptr, bus_var_name);

    load_vars_ptr = std::make_shared<LoadVariables>(input_ptr, load_var_name);
    load_cons_ptr = std::make_shared<LoadConstraints>(input_ptr, load_var_name);
    load_cost_ptr = std::make_shared<LoadCostsCon>(load_var_name);

    switch_shunt_vars_ptr = std::make_shared<SwitchShuntVariables>(input_ptr, swsh_var_name);

    line_vars_ptr = std::make_shared<LineVariablesCon>(input_ptr, bus_vars_ptr, line_var_name);
    line_cons_ptr = std::make_shared<LineConstraints>(input_ptr, line_var_name);
    line_cost_ptr = std::make_shared<LineCostsCon>(line_var_name);

    trans_vars_ptr = std::make_shared<TransformerVariables>(input_ptr, bus_vars_ptr, trans_var_name);
    trans_cons_ptr = std::make_shared<TransConstraints>(input_ptr, trans_vars_ptr, trans_var_name);
    trans_cost_ptr = std::make_shared<TransformerCosts>(trans_var_name);

    gen_vars_ptr = std::make_shared<GeneratorVariables>(input_ptr, gen_var_name);
    gen_cons_ptr = std::make_shared<GeneratorConstraints>(input_ptr, gen_var_name);
    gen_cost_ptr = std::make_shared<GenCosts>(gen_var_name);

    bus_cons_ptr = std::make_shared<BusConstraints>(input_ptr, bus_var_name, load_var_name, \
                                                         line_var_name, swsh_var_name, trans_var_name, gen_var_name);
    bus_cost_ptr = std::make_shared<BusCostsCon>(bus_var_name);

    nlp.AddVariableSet(load_vars_ptr);
    nlp.AddConstraintSet(load_cons_ptr);
    nlp.AddCostSet(load_cost_ptr);

    nlp.AddVariableSet(switch_shunt_vars_ptr);

    nlp.AddVariableSet(line_vars_ptr);
    nlp.AddConstraintSet(line_cons_ptr);
    nlp.AddCostSet(line_cost_ptr);

    nlp.AddVariableSet(trans_vars_ptr);
    nlp.AddConstraintSet(trans_cons_ptr);
    nlp.AddCostSet(trans_cost_ptr);

    nlp.AddVariableSet(gen_vars_ptr);
    nlp.AddConstraintSet(gen_cons_ptr);
    nlp.AddCostSet(gen_cost_ptr);

    nlp.AddVariableSet(bus_vars_ptr);
    nlp.AddConstraintSet(bus_cons_ptr);
    nlp.AddCostSet(bus_cost_ptr);
    nlp.PrintCurrent();




}
ContigencyCaseProblem::~ContigencyCaseProblem()
{}
void ContigencyCaseProblem::Solve()
{
    // 2. choose solver and options

    ifopt::IpoptSolver ipopt;
    //ipopt.SetOption("linear_solver", "ma97");
    ipopt.SetOption("jacobian_approximation", "finite-difference-values");
    ipopt.SetOption("check_derivatives_for_naninf", "yes");
    //ipopt.SetOption("bound_relax_factor", 1);
    ipopt.SetOption("print_level", 5);
    ipopt.SetOption("output_file", "output.txt");
    ipopt.SetOption("max_iter", 500);
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
    //std::cout<<"eq_70_var = "<<trans_vars_ptr->eq70_binary_variable.transpose()<<std::endl;
    //std::cout<<"eta fk = "<<trans_vars_ptr->eta_fk.transpose()<<std::endl;
    //std::cout<<"tau fk = "<<trans_vars_ptr->tau_fk.transpose()<<std::endl;


}