#include <string>
#include <iostream>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
#include <variables/bus_variables.hpp>
#include <variables/load_variables.hpp>
#include <constraints/bus_constraints.hpp>
#include <costs/bus_costs.hpp>
#include <costs/load_costs.hpp>

using namespace ifopt;

int main(int args, char** argv)
{

    // smart pointer pointing to model parameters derived from raw inpu
    auto input_ptr = std::make_shared<Wrapper_Construct>();
    
    // we first look at k = 0 case
    Problem nlp;
    // variables, constraints and objectives associated with buses
    auto bus_variables_ptr = std::make_shared<BusVariables>(input_ptr, "bus_variables");
    auto bus_cost_ptr = std::make_shared<BusCosts>("bus_variables");
    //nlp.AddVariableSet(bus_variables_ptr);
    //nlp.AddCostSet(bus_cost_ptr);
    // variables, constraints and objectives assocaited with loads
    auto load_vars_ptr = std::make_shared<LoadVariables>(input_ptr, "load_variables");
    auto load_cost_ptr = std::make_shared<LoadCosts>("load_variables");
    auto load_bounds = load_vars_ptr->GetBounds();

    nlp.AddVariableSet(load_vars_ptr);
    nlp.AddCostSet(load_cost_ptr);
    //Eigen::VectorXd x = nlp.GetOptVariables()->GetValues();
    //std::cout << x.transpose() << std::endl;
    nlp.PrintCurrent();



    // 2. choose solver and options

    IpoptSolver ipopt;
    //ipopt.SetOption("linear_solver", "ma27");
    ipopt.SetOption("jacobian_approximation", "finite-difference-values");
    ipopt.Solve(nlp);
    Eigen::VectorXd new_x = nlp.GetOptVariables()->GetValues();
    std::cout << new_x.transpose() << std::endl;

    return 0;
}

