#include "sup.hpp"
#include<fstream>
#include<string>
#include<cerrno>
#include<iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

Sup::Sup(){}

Sup::~Sup(){}


std::string Sup::read(std::string file_name)
{
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    rapidjson::Document d;
    d.Parse(json);

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


