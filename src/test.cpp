#include "wrapper_construct.hpp"
#include "map_input.hpp"
#include <string>
#include <iostream>
//#include "data.hpp"

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

    
    return 0;
}

