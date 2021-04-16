#include <string>
#include <iostream>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>

#include <variables/bus_variables.hpp>
#include <variables/load_variables.hpp>
#include <variables/line_variables.hpp>
#include <variables/transformer_variables.hpp>
#include <variables/generator_variables.hpp>
#include <variables/switch_shunt_variables.hpp>

#include <constraints/bus_constraints.hpp>
#include <constraints/load_constraints.hpp>
#include <constraints/line_constraints.hpp>
#include <constraints/transformer_constraints.hpp>
#include <constraints/generator_constraints.hpp>

#include <costs/bus_costs.hpp>
#include <costs/load_costs.hpp>
#include <costs/line_costs.hpp>
#include <costs/transformer_costs.hpp>
#include <costs/gen_costs.hpp>
#include <basecase_problem.hpp>


using namespace ifopt;


int main(int args, char** argv)
{

    /**
    // smart pointer pointing to model parameters derived from raw input
    //auto input_ptr = std::make_shared<Wrapper_Construct>("/Users/wchen/Projects/GOC_competition/SandboxData_C2S7_20210305/C2S7N00793/scenario_001/");
    auto input_ptr = std::make_shared<Wrapper_Construct>("./sample_data/ieee14/scenario_3/");
    // we first look at k = 0 case
    Problem nlp;

    // variables related with buses
    // their objectives and constraints are presented later
    auto bus_var_ptr = std::make_shared<BusVariables>(input_ptr, "bus_variables");


    // variables, constraints and objectives assocaited with loads
    auto load_vars_ptr = std::make_shared<LoadVariables>(input_ptr, "load_variables");
    auto load_cons_ptr = std::make_shared<LoadConstraints>(input_ptr, "load_variables");
    auto load_cost_ptr = std::make_shared<LoadCosts>("load_variables");
    nlp.AddVariableSet(load_vars_ptr);
    nlp.AddConstraintSet(load_cons_ptr);
    nlp.AddCostSet(load_cost_ptr);

    // variables and constraints associated with switch shunts
    auto switch_shunt_vars_ptr = std::make_shared<SwitchShuntVariables>(input_ptr, "switch_shunt_variables");
    nlp.AddVariableSet(switch_shunt_vars_ptr);

    // variables, constraints and objectives associated with lines
    auto line_vars_ptr = std::make_shared<LineVariables>(input_ptr, bus_var_ptr,"line_variables");
    auto line_cons_ptr = std::make_shared<LineConstraints>(input_ptr, "line_variables");
    auto line_cost_ptr = std::make_shared<LineCosts>("line_variables");
    nlp.AddVariableSet(line_vars_ptr);
    nlp.AddConstraintSet(line_cons_ptr);
    nlp.AddCostSet(line_cost_ptr);

    // variables, constraints and objectives associated with transformers
    auto trans_vars_ptr = std::make_shared<TransformerVariables>(input_ptr, bus_var_ptr, "trans_variables");
    auto trans_cons_ptr = std::make_shared<TransConstraints>(input_ptr, "trans_variables");
    auto trans_cost_ptr = std::make_shared<TransformerCosts>("trans_variables");
    nlp.AddVariableSet(trans_vars_ptr);
    nlp.AddConstraintSet(trans_cons_ptr);
    nlp.AddCostSet(trans_cost_ptr);

    // variables, constraints and objectives associated with generators
    auto gen_vars_ptr = std::make_shared<GeneratorVariables>(input_ptr, "gen_variables");
    auto gen_cons_ptr = std::make_shared<GeneratorConstraints>(input_ptr, "gen_variables");
    auto gen_cost_ptr = std::make_shared<GenCosts>("gen_variables");
    nlp.AddVariableSet(gen_vars_ptr);
    nlp.AddConstraintSet(gen_cons_ptr);
    nlp.AddCostSet(gen_cost_ptr);

    //variables, constraints and objectives associated with buses

    auto bus_cons_ptr = std::make_shared<BusConstraints>(input_ptr, "bus_variables", "load_variables", \
                                                         "line_variables", "switch_shunt_variables", "trans_variables", "gen_variables");
    auto bus_cost_ptr = std::make_shared<BusCosts>("bus_variables");

    nlp.AddVariableSet(bus_var_ptr);
    nlp.AddConstraintSet(bus_cons_ptr);
    nlp.AddCostSet(bus_cost_ptr);
    nlp.PrintCurrent();



    // 2. choose solver and options

    IpoptSolver ipopt;
    //ipopt.SetOption("linear_solver", "ma97");
    ipopt.SetOption("jacobian_approximation", "finite-difference-values");
    ipopt.SetOption("check_derivatives_for_naninf", "yes");
    ipopt.SetOption("bound_relax_factor", 1);
    ipopt.SetOption("print_level", 3);
    ipopt.SetOption("output_file", "output.txt");
    ipopt.SetOption("max_iter", 3000);
    ipopt.Solve(nlp);
    Eigen::VectorXd x = nlp.GetOptVariables()->GetValues();
    std::cout << x.transpose() << std::endl;

    **/

    return 0;
}
void write_solution(const Problem& nlp)
{
    auto bus_var_ptr = nlp.GetOptVariables()->GetComponent<BusVariables>("bus_variables");

}
