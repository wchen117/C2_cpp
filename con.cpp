#include "con.hpp"
#include <fstream>
#include <string>
#include <cerrno>
#include <vector>
#include <iostream>


Con::Con(){} 

Con::~Con(){}

void Con::read(std::string file_name)
{
    con_input = read_to_string(file_name);
    read_from_rows();

}

std::string Con::read_to_string(std::string file_name)
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

std::vector<std::string> Con::parse_on_delimiter(std::string input_string, std::string delimiter)
{
    std::vector<std::string> parsed_string_vector;
    std::size_t start = 0;
    std::size_t end = input_string.find(delimiter);

    while(end != std::string::npos)
    {
         parsed_string_vector.push_back(input_string.substr(start, end - start));
         start = end + delimiter.length();
         end = input_string.find(delimiter, start);
    }
    parsed_string_vector.push_back(input_string.substr(start, std::string::npos));

    return parsed_string_vector;

}
void Con::read_from_rows()
{
    // parse on "END"
    con_vector = parse_on_delimiter(con_input, "END");
    std::vector<std::string> test_v = parse_on_delimiter(con_vector[0], " ");
 
    // two "END" at the end of file
     for (int idx=0; idx<con_vector.size()-1; idx++)
    {
        // parse each section to vector of strings
        std::vector<std::string> tmp_vect = parse_on_delimiter(con_vector[idx], " ");
        if (tmp_vect[2] == "REMOVE")
        {
            // generator out event
            GeneratorOutEvent tmp_gen_event;
            parse_generatorout(tmp_vect, tmp_gen_event);
        }
        else if (tmp_vect[2] == "OPEN")
        {
            // branch out event
            BranchOutEvent tmp_branch_event;
            parse_branchout(tmp_vect, tmp_branch_event);
        }
        else
        {
            // display error
        }
        
    }    
}

void Con::parse_branchout(std::vector<std::string> branchout_vector, BranchOutEvent& branch_event)
{
    branch_event.label = branchout_string_vector[1];

    

}

void Con::parse_generatorout(std::vector<std::string> genout_vector, GeneratorOutEvent& gen_event)
{

}
