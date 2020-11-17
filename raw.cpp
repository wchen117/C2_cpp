#include "raw.hpp"
#include<fstream>
#include<string>
#include<cerrno>
#include<vector>
#include<iostream>
#include <sstream>

/**constructor and desctructor**/
Raw::Raw(){}

Raw::~Raw(){}

void Raw::read(std::string file_name)
{
    raw_input = read_to_string(file_name);
    read_from_rows();
    lines_in_section(rows_sections[1]);
}

std::string Raw::read_to_string(std::string file_name)
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
         rows_sections.push_back(raw_input.substr(start, end - start));
         start = end + delimiter.length();
         end = raw_input.find(delimiter, start);
    }
    

}

std::vector<std::string> Raw::lines_in_section(std::string section)
{
    std::vector<std::string> section_vector;
    std::istringstream sectionstream (section);
    std::string temp;
    while(std::getline(sectionstream, temp))
    {
        section_vector.push_back(temp);
        std::cout<<temp<<std::endl;
    }
    return section_vector;
    
}

