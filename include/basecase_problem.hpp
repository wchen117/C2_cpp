//
// Created by wchen on 4/14/21.
//

#ifndef GOC_CPP_BASECASE_PROBLEM_HPP
#define GOC_CPP_BASECASE_PROBLEM_HPP

#include <string>
#include <iostream>
#include <fstream>
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

class BaseCaseProblem{
public:
    BaseCaseProblem(const std::string& input_dir);
    ~BaseCaseProblem();
    void WriteOutputFile();
    void Solve();
private:
    const std::string K_string = "BASECASE";
    std::string input_path;

    const std::string bus_var_name = "bus_variables";
    const std::string load_var_name = "load_variables";
    const std::string line_var_name = "line_variables";
    const std::string swsh_var_name = "switch_shunt_variables";
    const std::string trans_var_name = "trans_variables";
    const std::string gen_var_name = "gen_variables";

    std::shared_ptr<Wrapper_Construct> input_ptr;
    ifopt::Problem nlp;

    std::shared_ptr<BusVariables> bus_vars_ptr;
    std::shared_ptr<BusConstraints> bus_cons_ptr;
    std::shared_ptr<BusCosts> bus_cost_ptr;

    std::shared_ptr<LoadVariables> load_vars_ptr;
    std::shared_ptr<LoadConstraints> load_cons_ptr;
    std::shared_ptr<LoadCosts> load_cost_ptr;

    std::shared_ptr<LineVariables> line_vars_ptr;
    std::shared_ptr<LineConstraints> line_cons_ptr;
    std::shared_ptr<LineCosts> line_cost_ptr;

    std::shared_ptr<SwitchShuntVariables> switch_shunt_vars_ptr;

    std::shared_ptr<TransformerVariables> trans_vars_ptr;
    std::shared_ptr<TransConstraints> trans_cons_ptr;
    std::shared_ptr<TransformerCosts> trans_cost_ptr;

    std::shared_ptr<GeneratorVariables> gen_vars_ptr;
    std::shared_ptr<GeneratorConstraints> gen_cons_ptr;
    std::shared_ptr<GenCosts> gen_cost_ptr;





};

#endif //GOC_CPP_BASECASE_PROBLEM_HPP
