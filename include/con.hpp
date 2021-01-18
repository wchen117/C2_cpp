#ifndef __CON_HPP__
#define __CON_HPP__


#include <string>
#include <vector>
#include "generatoroutevent.hpp"
#include "branchoutevent.hpp"
#include "contingency.hpp"


class Con

{
public:
    // con_input stores entire file into a string
    std::string con_input;
    // con_vector stores the vectore of string from con_input
    std::vector<std::string> con_vector;
    // vector to store all contingencies
    std::vector<Contingency> contingencies;

    Con();
    ~Con();

    bool write(
            std::string file_name
            );
    
    // python: target_contingency default to None, how to translate? 
    void read(
            std::string file_name
            );
    std::string read_to_string(
            std::string file_name
            );
    // python: target_congingency default to None
    void read_from_rows(
            );

    std::vector<std::string> parse_on_delimiter(
            std::string input_string, 
            std::string delimiter
            );
    void parse_branchout(
            std::vector<std::string> branchout_vector,
            BranchOutEvent& branch_event
    );
    void parse_generatorout(
            std::vector<std::string> generatorout_vector,
            GeneratorOutEvent& gen_event

    );
    
};
#endif
