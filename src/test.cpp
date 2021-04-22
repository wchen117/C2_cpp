#include <string>
#include <iostream>

#include <basecase_problem.hpp>


int main(int args, char** argv)
{
    //BaseCaseProblem bcp("/Users/wchen/Projects/GOC_competition/SandboxData_C2S7_20210305/C2S7N00617/scenario_001/");
    BaseCaseProblem bcp("./sample_data/ieee14/scenario_2/");
    bcp.Solve();
    bcp.WriteOutputFile();

    return 0;
}


