#ifndef __RAW_HPP__
#define __RAW_HPP__

#include <map>
#include <memory>
#include <string>

#include "caseidentification.hpp"
#include "bus.hpp"
#include "load.hpp"
#include "fixedshunt.hpp"
#include "generator.hpp"
#include "nontransformerbranch.hpp"
#include "transformer.hpp"
#include "area.hpp"
#include "transformerimpedancecorrectiontable.hpp"
#include "switchedshunt.hpp"

class Raw
{

public:

    CaseIdentification case_identification;
    map<Bus, int> buses;
    map<Load, int> loads;
    map<FixedShunt, int> fixed_shunts;
    map<Generator, int> generators;
    map<NonTransformerBranch, int> nontransformer_branches;
    map<Transformer, int>  transformers;
    map<Area, int> area;
    map<TransformerImpedanceCorrectionTable, int> transformer_impedance_correction_tables;
    map<SwitchedShunt, int> switched_shunts;

    int num_loads_active;

    /**constructor and destructor**/
    Raw();
    ~Raw();

    bool scrub(
            );

    bool check(
            );
  
    bool add_gen_emergency_capacity(
            );

    bool scrub_switched_shunts(
            );
  
    bool check_nontransformer_branches(
            );

    bool check_nontransformer_branches(
            );

    bool scrub_nontransformer_branches(
            );   
    
    bool check_nontransformer_branches_buses_exist(
            ); 
    
    bool check_transformers(
            );

    bool scrub_transformers(
            );

    bool check_transformers_buses_exist(
            bool scrub_mode=false
            );

    bool check_case_identification(
            );
   
    bool check_buses(
            );

    bool scrub_buses(
            );

    bool remove_buses_with_ide_eq_4(
            );

    bool check_loads(
            );
   
    bool scrub_loads(
            );

    bool check_loads_bus_exists(
            bool scrub_mode=false
            );
    
    bool check_fixed_shunts(
            );

    bool check_fixed_shunts_bus_exists(
            );

    bool scrub_fixed_shunts(
            );

    bool check_generators(
            );

    bool scrub_generators(
            );

    bool check_generators_bus_exists(
            bool scrube_mode=false
            );

    bool check_switched_shunts(
            );

    bool check_switched_shunts_bus_exists(
            scrub_mode=false
            );

    bool check_switched_shunts_binit_feas(
            bool scrub_mode=false
            );

    bool check_unique_branch_per_i_j_ckt(
            );

    bool set_areas_from_buses(
            );

    std::vector<Bus> get_buses(
            );

    std::vector<Load> get_loads(
            );

    std::vector<FixedShunt> get_fixed_shunts(
            );

    std::vector<Generator> get_generators(
            );

    std::vector<NontransformerBranch> get_nontransformer_branches(
            );

    std::vector<Transformer> get_transformers(
            );

    std::vector<Area> get_areas(
            );

    std::vector<TransformerImpedanceCorrectionTable> get_transformer_impedance_correction_tables(
            );

    std::vector<SwitchedShunt> get_switched_shunts(
            );

    string construct_case_identification_section(
            );

    string construct_bus_section(
            );

    string construct_load_section(
            );

    string construct_fixed_shunt_section(
            );

    string construct_generator_section(
            );

    string construct_nontransformer_branch_section(
            );

    string construct_transformer_section(
            );

    string construct_area_section(
            );

    string construct_two_terminal_dc_section(
            );

    string construct_vsc_dc_section(
            );

    string construct_transformer_impedance_section(
            );

    string construct_multi_terminal_dc_section(
            );

    string construct_multi_section_line_section(
            );

    string construct_zone_section(
            );

    string construct_interarea_section(
            );

    string construct_owner_section(
            );

    string construct_facts_section(
            );

    string construct_switched_shunt_section(
            );

    string construct_gne_section(
            );

    string construct_induction_section(
            );

    string construct_q_record(
            );

    bool write(
            string file_name
            );

    string set_operating_point_to_offline_solution(
            );

    bool read(
            string file_name
            );
    bool row_is_file_end(
            int row
            );

    bool row_is_section_end(
            int row
            );

    // not sure type of rows here
    bool read_from_rows(
            string row
            )
    
}
#endif
