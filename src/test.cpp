#include <string>
#include <iostream>

#include <basecase_problem.hpp>
#include <contigencycase_problem.hpp>

int main(int args, char** argv)
{   //BaseCaseProblem bcp("./SandboxData_C2S7_20210305/C2S7N00617/scenario_001/");
    BaseCaseProblem bcp("./sample_data/ieee14/scenario_3/");
    bcp.Solve();
    bcp.WriteOutputFile();
    ContigencyCaseProblem conp("./sample_data/ieee14/scenario_3/");
    conp.Solve();

    return 0;
}


