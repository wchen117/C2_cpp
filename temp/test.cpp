#include "wrapper_construct.hpp"
#include "map_input.hpp"
#include <string>
#include <iostream>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
#include <test_vars_constr_cost.h>

using namespace ifopt;

void bus_obej_constraints(Wrapper_Construct &new_model, Map_Input &new_input)
{
    for(size_t idx=0; idx<new_model.Is; idx++)
    {
        std::cout<<new_model.I.at(idx)<<std::endl;
    }
}
int main(int args, char** argv)
{
    std::string data_folder = "./sample_data/ieee14/scenario_1/";
    
    Wrapper_Construct new_model;
    Map_Input new_input;
    new_input.test_a = new_model.s_tilde_inverse;
    
    bus_obej_constraints(new_model, new_input);

    Problem nlp;
    nlp.AddVariableSet  (std::make_shared<ExVariables>());
    nlp.AddConstraintSet(std::make_shared<ExConstraint>());
    nlp.AddCostSet      (std::make_shared<ExCost>());
    nlp.PrintCurrent();

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

   
    return 0;
}

