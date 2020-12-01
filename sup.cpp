#include "sup.hpp"
#include <fstream>
#include <string>
#include <cerrno>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

Sup::Sup(){}

Sup::~Sup(){}

using namespace rapidjson;

void Sup::string_to_json()
{
    rapidjson::Document d;
    d.Parse(sup_input);

    std::cout<<d["systemparameters"]["delta"]<<std::endl;

}

std::string Sup::read_to_string(std::string file_name)
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

std::string Sup::read(std::string file_name)
{
    sup_input = read_to_string(file_name);
    string_to_json();


}


