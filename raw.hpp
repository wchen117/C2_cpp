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
#include "nontransformerbranch.hpp"
#include "transformer.hpp"
#include "area.hpp"
#include "transformerimpedancecorrectiontable.hpp"
#include "zone.hpp"
#include "owner.hpp"
#include "switchedshunt.hpp"




class Raw
{

public:

    std::vector<std::string> rows_sections;
    std::string raw_input;
    CaseIdentification CaseIdentificationData;
    Zone zone;
    Owner owner;
    std::unordered_map<int, Bus> buses;
    std::unordered_map<int, Load> loads;
    std::unordered_map<int, FixedShunt> shunts;
    std::unordered_map<int, Generator> generators;
    std::unordered_map<int, NontransformerBranch> nontransformerbranches;
    std::unordered_map<int, Transformer> transformers;
    std::unordered_map<int, Area> areas;
    std::unordered_map<int, SwitchedShunt> switchedshunts;
    std::unordered_map<int, TransformerImpedanceCorrectionTable> TFICTs;




    /**constructor and destructor**/
    Raw();
    ~Raw();

    void parse_token(
            int& value,
            std::string input_string,
            int default_value

    );
    
    void parse_token(
            double& value,
            std::string input_string,
            double default_value
 
    );

    void parse_token(
            std::string& value, 
            std::string input_string, 
            std::string& default_value
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

    void parse_transformer(
            std::vector<std::string> transformer_section
    );

    void parse_area(
            std::vector<std::string> area_section
    );
    
    void parse_two_terminal_dc_transmission_line(
            std::vector<std::string> ttdc_transmission_line
    );
    
    void parse_vsc_dc_transmission_line(
            std::vector<std::string> vsc_dc_transmission_section
    );
    
    void parse_transformer_impedance_correction_table(
            std::vector<std::string> impedance_data_section
    );
    
    void parse_multi_terminal_dc(
            std::vector<std::string> multi_terminal_dc_section
    );
    
    void parse_multi_section_line(
            std::vector<std::string> multi_section_line
    );

    void parse_multisection_line_grouping();
    
    void parse_zone(
            std::vector<std::string> zone_section
    );
    
    void parse_interarea_transfer(
            std::vector<std::string> interarea_transfer_section
    );
    
    void parse_owner(
            std::vector<std::string> owner_section
    );
    
    void parse_facts_control_device(
            std::vector<std::string> facts_control_device_section
    );
    
    void parse_switched_shunt(
            std::vector<std::string> switched_shunt_section
    );
    
    void parse_gne_device(
            std::vector<std::string> gne_device_section
    );
    
    void parse_induction_machine(
            std::vector<std::string> induction_machine_section
    );

    void write(
            std::string write_file_name
    );

    void write_case_id(
            std::ofstream& OutputFile
    );

    void write_bus(
            std::ofstream& OutputFile
    );

    void write_load(
            std::ofstream& OutputFile
    );

};
#endif
