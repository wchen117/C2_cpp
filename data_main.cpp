<<<<<<< HEAD
#include <iostream>

using namespace std;

int main(int args, char** argv)
{
    std::cout<<"Hello World!"<<"\n";
    return 0;
=======
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
>>>>>>> simple
}
