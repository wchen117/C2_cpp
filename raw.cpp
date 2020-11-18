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
    string_to_section();
    std::vector<std::string> section_one = lines_in_section(0); 
    std::cout<<(section_one[0]).empty()<<std::endl;
    parse_case_id_bus(section_one);
    
    //this->string_to_section();
    // parse case identification data and bus data
    //parse_case_id_bus();
    //parse_load();
    //parse_fixed_bus_shunt();
    //parse_generator();
    //parse_non_transformer_branch();
    //parse_transformer();
    //parse_area();
    //parse_two_terminal_dc_transmission_line();
    //parse_vsc_dc_transmission_line();
    //parse_transformer_impedance_correction_table();
    //parse_multisection_line_grouping();
    //parse_zone();
    //parse_interarea_transfer();
    //parse_owner();
    //parse_facts_device();
    //parse_switched_shunt();
    //parse_gne_device();
    //parse_induction_machine();
}

std::string Raw::read_to_string(std::string file_name)
{
    // read in case.raw file into a string
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

void Raw::string_to_section()
{
    // parse the different section of case.raw file
    // The begining of each section is marked by "0 /" 
    // Note the Case Identification Data and Bus Date are not
    // separated by "0 /". 
    rows_sections = parse_on_delimiter(raw_input, "0 /");

}

std::vector<std::string> Raw::parse_on_delimiter(std::string input_string, std::string delimiter)
{
    std::vector<std::string> parsed_string_vector;
    std::size_t start = 0;
    std::size_t end = raw_input.find(delimiter);

    while(end != std::string::npos)
    {
         parsed_string_vector.push_back(input_string.substr(start, end - start));
         start = end + delimiter.length();
         end = raw_input.find(delimiter, start);
    }

    return parsed_string_vector;

}

std::vector<std::string> Raw::lines_in_section(size_t section_num)
{
    // parse each section to vectors of lines
    std::vector<std::string> section_vector;
    std::istringstream sectionstream (rows_sections[section_num]);
    std::string temp;
    while(std::getline(sectionstream, temp))
    {
        section_vector.push_back(temp);
    }
    return section_vector;
    
}


void Raw::parse_case_id_bus(std::vector<std::string> section)
{
   // case identification and bus date corresponds to
   // section_vector[0]
   for (int idx = 0; idx< 3; idx++)
    {
        if(!section[idx].empty())
        {

        }
    }

    for (int idx=3; idx<section.size(); idx++)
    {
        //std::cout<<"Line "<<idx<<" is "<<section[idx]<<std::endl;
    }


 
}

void Raw::parse_load()
{
   // case identification and bus date corresponds to
   // section_vector[0]

}

