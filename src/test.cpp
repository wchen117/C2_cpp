#include <string>
#include <iostream>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
#include <variables/bus_variables.hpp>
#include <variables/load_variables.hpp>
#include <variables/line_variables.hpp>
#include <variables/transformer_variables.hpp>
#include <variables/generator_variables.hpp>

#include <costs/bus_costs.hpp>
#include <costs/load_costs.hpp>
#include <costs/line_costs.hpp>
#include <costs/transformer_costs.hpp>



using namespace ifopt;

int main(int args, char** argv)
{

    // smart pointer pointing to model parameters derived from raw input
    auto input_ptr = std::make_shared<Wrapper_Construct>();
    
    // we first look at k = 0 case
    Problem nlp;

    //variables, constraints and objectives associated with buses
    //auto bus_variables_ptr = std::make_shared<BusVariables>(input_ptr, "bus_variables");
    //auto bus_cost_ptr = std::make_shared<BusCosts>("bus_variables");
    //nlp.AddVariableSet(bus_variables_ptr);
    //nlp.AddCostSet(bus_cost_ptr);

    // variables, constraints and objectives assocaited with loads
    //auto load_vars_ptr = std::make_shared<LoadVariables>(input_ptr, "load_variables");
    //auto load_cost_ptr = std::make_shared<LoadCosts>("load_variables");
    //nlp.AddVariableSet(load_vars_ptr);
    //nlp.AddCostSet(load_cost_ptr);

    // variables, constraints and objectives associated with lines
    //auto line_vars_ptr = std::make_shared<LineVariables>(input_ptr, "line_variables");
    //auto line_cost_ptr = std::make_shared<LineCosts>("line_variables");
    //nlp.AddVariableSet(line_vars_ptr);
    //nlp.AddCostSet(line_cost_ptr);

    // variables, constraints and objectives associated with transformers
    //auto trans_vars_ptr = std::make_shared<TransformerVariables>(input_ptr, "trans_variables");
    //auto trans_cost_ptr = std::make_shared<TransformerCosts>("trans_variables");
    //nlp.AddVariableSet(trans_vars_ptr);
    //nlp.AddCostSet(trans_cost_ptr);

    // variables, constraints and objectives associated with generators
    auto gen_vars_ptr = std::make_shared<GeneratorVariables>(input_ptr, "gen_variables");

    nlp.PrintCurrent();



    // 2. choose solver and options

    IpoptSolver ipopt;
    //ipopt.SetOption("linear_solver", "ma27");
    ipopt.SetOption("jacobian_approximation", "finite-difference-values");
    ipopt.Solve(nlp);


    return 0;
}

