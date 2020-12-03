#include "sup.hpp"
#include <fstream>
#include <string>
#include <cerrno>
#include <iostream>

#include "rapidjson/pointer.h"

Sup::Sup(){}

Sup::~Sup(){}

using namespace rapidjson;

void Sup::read(std::string file_name)
{
    sup_input = read_to_string(file_name);
    //std::cout<<sup_input<<std::endl;
    // parse the entire file into a rapidjson::Document object
    read_json();
}


void Sup::read_json()
{
    sup_doc.Parse(sup_input.c_str());
    
    const Value& sys_prms = sup_doc["systemparameters"];
    const Value& loads = sup_doc["loads"];
    const Value& generators = sup_doc["generators"];
    const Value& lines = sup_doc["lines"];
    const Value& transformers = sup_doc["transformers"];
    const Value& pcblocks = sup_doc["pcblocks"];
    const Value& qcblocks = sup_doc["qcblocks"];
    const Value& scblocks = sup_doc["scblocks"];
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



