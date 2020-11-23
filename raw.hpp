#ifndef __RAW_HPP__
#define __RAW_HPP__

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "caseidentification.hpp"
#include "bus.hpp"
#include "load.hpp"
#include "fixedshunt.hpp"
#include "generator.hpp"



class Raw
{

public:

    std::vector<std::string> rows_sections;
    std::string raw_input;
    CaseIdentification CaseIdentificationData;
    std::unordered_map<int, Bus> buses;
    std::unordered_map<int, Load> loads;
    std::unordered_map<int, FixedShunt> shunts;
    std::unordered_map<int, Generator> generators;



    /**constructor and destructor**/
    Raw();
    ~Raw();

    bool write(
            std::string file_name
            );

    void read(
            std::string file_name
            );

    std::string read_to_string(
            std::string file_name
            );

    bool row_is_file_end(
            int row
            );

    bool row_is_section_end(
            int row
            );

    void string_to_section();
    
    std::vector<std::string> lines_in_section(
            size_t section_num 
            );

    std::vector<std::string> parse_on_delimiter(
            std::string input_string,
            std::string delimiter
            );

    void parse_case_id_bus(
            std::vector<std::string> section
    );

    void parse_case_id(
            std::string line1,
            std::string line2,
            std::string line3
    );
    void parse_bus(
            std::string each_line,
            Bus& ref

    );


    void parse_load(
            std::vector<std::string> load_section
    );

    void parse_fixed_bus_shunt(
            std::vector<std::string> fixed_shunt_section
    );

    void parse_generator(
            std::vector<std::string> generator_section
    );
    
    void parse_nontransformerbranch(
            std::vector<std::string> nontransformerbranch_section
    );
    
    void parse_area();
    
    void parse_two_terminal_dc_transmission_line();
    
    void parse_vsc_dc_transmission_line();
    
    void parse_transformer_impedance_correction_table();
    
    void parse_multisection_line_grouping();
    
    void parse_zone();
    
    void parse_interarea_transfer();
    
    void parse_owner();
    
    void parse_facts_device();
    
    void parse_switched_shunt();
    
    void parse_gne_device();
    
    void parse_induction_machine();
};
#endif
