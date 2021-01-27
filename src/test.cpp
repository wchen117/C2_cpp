//#include "wrapper_construct.hpp"
#include "map_input.hpp"
#include <string>
#include <iostream>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>
#include <variables.hpp>
#include <constraints.hpp>
#include <costs.hpp>

using namespace ifopt;

int main(int args, char** argv)
{

    auto data_holder = std::make_shared<Wrapper_Construct>();
    std::cout<<data_holder->s_tilde<<std::endl;
    // p_ikn+, p_ikn-, q_ikn+, q_ikn-, z_ik
    std::cout<<data_holder->Is<<std::endl;
    std::cout<<data_holder->Np<<std::endl;
    std::cout<<data_holder->Is * data_holder->Np<<std::endl;
    
    //int p_ikn_size = data_holder->Is * data_holder->Np;
    //GocVariables p_ikn_plus(p_ikn_size, "p_ikn+");
    //GocVariables p_ikn_minus(p_ikn_size, "p_ikn-");
    //int q_ikn_size = new_model.Is * new_model.Nq;
    //GocVariables q_ikn_plus(p_ikn_size, "q_ikn+");
    //GocVariables q_ikn_minus(p_ikn_size, "q_ikn-");
    //p_ikn_plus.ReadinData(new_model);

    //Problem nlp;
    //nlp.AddVariableSet  (std::make_shared<p_ikn_plus>());
    //nlp.PrintCurrent();
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

