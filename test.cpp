#include "wrapper_construct.hpp"
#include <string>
#include <iostream>
//#include "data.hpp"

int main(int args, char** argv)
{
    std::string data_folder = "./sample_data/ieee14/scenario_1/";
    
    Wrapper_Construct new_model(data_folder);
    //new_model.initiate(folder_path);
    //std::cout<< new_model.s_tilde_inverse<<std::endl;
    return 0;
}