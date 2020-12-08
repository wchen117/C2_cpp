#include "main_1.hpp"
#include "data.hpp"
#include <string>
#include <iostream>

int main(int args, char** argv)
{
    std::string data_folder = "./sample_data/ieee14/scenario_1/";
    std::string con_name = "case.con";
    std::string raw_name = "case.raw";
    std::string sup_name = "case.json";

    Data new_data;
    new_data.read(data_folder + raw_name,\
                  data_folder + sup_name, \
                  data_folder + con_name);

    //std::string write_raw_name = "test_write.raw";
    //std::string write_con_name = "test_write.con";
    //std::string write_sup_name = "test_write.sup";
    
    //new_data.write(write_raw_name, \
    //               write_con_name, \
    //               write_sup_name);

    // case identification data from raw
    stilde = new_data.raw.CaseIdentificationData.sbase;
    double stilde_inverse = 1.0 / stilde;
    

    // bus data from raw
    int Is = new_data.raw.buses.size();
    std::vector<double> vover;
    std::vector<double> vunder;

    std::unordered_map<int, Bus>::iterator bus_it;

    for (bus_it=new_data.raw.buses.begin(); bus_it!=new_data.raw.buses.end(); bus_it++)
    {
        I.push_back()

    }
    
    

    
    
}
