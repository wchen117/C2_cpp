#include "con.hpp"
#include<fstream>
#include<string>
#include<cerrno>


Con::Con(){}

Con::~Con(){}


std::string Con::read(std::string file_name)
{
    std::ifstream input(file_name, std::ios::in | std::ios::binary);
    input.clear();
    if (input)  
    {
        std::string contents2;
        input.seekg(0, std::ios::end);
        contents2.resize(input.tellg());
        input.seekg(0, std::ios::beg);
        input.read(&contents2[0], contents2.size());
        input.close();
        return contents2;
    
    }
    throw(errno);
}

bool Con::read_from_rows(std::string rows)
{
    return true;
}

