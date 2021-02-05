#include <string>
#include <iostream>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
#include <variables/bus_variables.hpp>
#include <constraints/bus_constraints.hpp>
#include <costs/bus_costs.hpp>

using namespace ifopt;

int main(int args, char** argv)
{

    // smart pointer pointing to model parameters derived from raw inpu
    auto input_ptr = std::make_shared<Wrapper_Construct>();
    
    // we first look at k = 0 case
    Problem nlp;
    auto bus_variables_ptr = std::make_shared<BusVariables>(input_ptr, "bus_variables");
    auto bus_constraints_ptr = std::make_shared<BusConstraints>(input_ptr, "bus_constraints");
    auto bus_cost_ptr = std::make_shared<BusCosts>("bus_variables");
    nlp.AddVariableSet(bus_variables_ptr);
    nlp.AddConstraintSet(bus_constraints_ptr);
    nlp.AddCostSet(bus_cost_ptr);
    nlp.PrintCurrent();

    IpoptSolver ipopt;
    ipopt.SetOption("linear_solver", "ma97");
    ipopt.SetOption("jacobian_approximation", "finite-difference-values");
    ipopt.Solve(nlp);
    Eigen::VectorXd x = nlp.GetOptVariables()->GetValues();
    //std::cout << x << std::endl;
    /**
    
    nlp.AddConstraintSet(std::make_shared<ExConstraint>());
    nlp.AddCostSet      (std::make_shared<ExCost>());
    

    // 2. choose solver and options
    
    

    // 3 . solve
    
    

    // 4. test if solution correct
    double eps = 1e-5; //double precision
    assert(1.0-eps < x(0) && x(0) < 1.0+eps);
    assert(0.0-eps < x(1) && x(1) < 0.0+eps);

    **/   
    return 0;
}

