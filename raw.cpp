#include "raw.hpp"
#include<fstream>
#include<string>
#include<cerrno>
#include<vector>
#include<iostream>

/**constructor and desctructor**/
Raw::Raw(){}

Raw::~Raw(){}

std::string Raw::read(std::string file_name)
{
    std::ifstream input(file_name, std::ios::in | std::ios::binary);
    input.clear();
    if (input)  
    {
        
        input.seekg(0, std::ios::end);
        raw_input.resize(input.tellg());
        input.seekg(0, std::ios::beg);
        input.read(&raw_input[0], raw_input.size());
        input.close();    
    }
    throw(errno);
}

bool Raw::read_from_rows()
{
    std::string delimiter = "0 /";
    std::size_t start = 0;
    std::size_t end = raw_input.find(delimiter);
    std::vector<std::string> rows_sections;
    while(end != std::string::npos)
    {
         std::cout << raw_input.substr(start, end - start) << std::endl;
         rows_sections.push_back(raw_input.substr(start, end - start));
         start = end + delimiter.length();
         end = raw_input.find(delimiter, start);
    }
    rows_sections.push_back(raw_input.substr(start, end));

    return true;
}

