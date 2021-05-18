//
// Created by wchen on 5/11/21.
//

#ifndef GOC_CPP_CONTIGENCYCASE_PROBLEM_H
#define GOC_CPP_CONTIGENCYCASE_PROBLEM_H


#include <string>
#include <iostream>
#include <fstream>
#include <ifopt/problem.h>
#include <ifopt/ipopt_solver.h>

#include <variables/bus_variables_con.hpp>
#include <variables/load_variables_con.hpp>
#include <variables/line_variables_con.hpp>
#include <variables/transformer_variables_con.hpp>
#include <variables/generator_variables_con.hpp>
#include <variables/switch_shunt_variables_con.hpp>

#include <constraints/bus_constraints_con.hpp>
#include <constraints/load_constraints_con.hpp>
#include <constraints/line_constraints_con.hpp>
#include <constraints/transformer_constraints_con.hpp>
#include <constraints/generator_constraints_con.hpp>

#include <costs/bus_costs_con.hpp>
#include <costs/load_costs_con.hpp>
#include <costs/line_costs_con.hpp>
#include <costs/transformer_costs_con.hpp>
#include <costs/gen_costs_con.hpp>
class ContigencyCaseProblem {
public:
    ContigencyCaseProblem(const std::string& input_dir);
    ~ContigencyCaseProblem();
    void WriteOutputFile();
    void Solve();

private:
    const std::string K_string = "1";
    std::string input_path;

    const std::string bus_var_name = "bus_variables";
    const std::string load_var_name = "load_variables";
    const std::string line_var_name = "line_variables";
    const std::string swsh_var_name = "switch_shunt_variables";
    const std::string trans_var_name = "trans_variables";
    const std::string gen_var_name = "gen_variables";

    std::shared_ptr<Wrapper_Construct> input_ptr;
    ifopt::Problem nlp;

    std::shared_ptr<BusVariablesCon> bus_vars_ptr;
    std::shared_ptr<BusConstraintsCon> bus_cons_ptr;
    std::shared_ptr<BusCostsCon> bus_cost_ptr;

    std::shared_ptr<LoadVariablesCon> load_vars_ptr;
    std::shared_ptr<LoadConstraintsCon> load_cons_ptr;
    std::shared_ptr<LoadCostsCon> load_cost_ptr;

    std::shared_ptr<LineVariablesCon> line_vars_ptr;
    std::shared_ptr<LineConstraintsCon> line_cons_ptr;
    std::shared_ptr<LineCostsCon> line_cost_ptr;

    std::shared_ptr<SwitchShuntVariablesCon> switch_shunt_vars_ptr;

    std::shared_ptr<TransformerVariablesCon> trans_vars_ptr;
    std::shared_ptr<TransConstraintsCon> trans_cons_ptr;
    std::shared_ptr<TransformerCostsCon> trans_cost_ptr;

    std::shared_ptr<GeneratorVariablesCon> gen_vars_ptr;
    std::shared_ptr<GeneratorConstraintsCon> gen_cons_ptr;
    std::shared_ptr<GenCostsCon> gen_cost_ptr;





};

#endif //GOC_CPP_CONTIGENCYCASE_PROBLEM_H
