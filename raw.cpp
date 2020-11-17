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
        std::string container;
        input.seekg(0, std::ios::end);
        container.resize(input.tellg());
        input.seekg(0, std::ios::beg);
        input.read(&container[0], container.size());
        input.close();   
        return container;
    }
    throw(errno);
}

void Raw::read_from_rows()
{
    // parse the different section of case.raw file
    std::string delimiter = "0 / ";
    std::size_t start = 0;
    std::size_t end = raw_input.find(delimiter);

   
    while(end != std::string::npos)
    {
         //std::cout << raw_input.substr(start, end - start) << std::endl;
         rows_sections.push_back(raw_input.substr(start, end - start));
         start = end + delimiter.length();
         end = raw_input.find(delimiter, start);
    }
    
    for(int idx=0; idx<1; idx++)
    {
        std::cout<<rows_sections[idx]<<std::endl;
    }
    //rows_sections.push_back(raw_input.substr(start, end));
}

