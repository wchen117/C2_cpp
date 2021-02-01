//#include "wrapper_construct.hpp"
#include "map_input.hpp"
#include <string>
#include <iostream>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
#include <bus_variables.hpp>
#include <constraints.hpp>
#include <costs.hpp>

using namespace ifopt;

int main(int args, char** argv)
{

    // smart pointer pointing to model parameters derived from raw inpu
    auto data_holder = std::make_shared<Wrapper_Construct>();
    
    // we first look at k = 0 case
    Problem nlp;
    nlp.AddVariableSet(std::make_shared<BusVariables>(data_holder, "bus_variables"));
    nlp.PrintCurrent();
    /**
    
    nlp.AddConstraintSet(std::make_shared<ExConstraint>());
    nlp.AddCostSet      (std::make_shared<ExCost>());
    

    // 2. choose solver and options
    IpoptSolver ipopt;
    ipopt.SetOption("linear_solver", "ma97");
    ipopt.SetOption("jacobian_approximation", "exact");

    // 3 . solve
    ipopt.Solve(nlp);
    Eigen::VectorXd x = nlp.GetOptVariables()->GetValues();
    std::cout << x.transpose() << std::endl;

    // 4. test if solution correct
    double eps = 1e-5; //double precision
    assert(1.0-eps < x(0) && x(0) < 1.0+eps);
    assert(0.0-eps < x(1) && x(1) < 0.0+eps);

    **/   
    return 0;
}

