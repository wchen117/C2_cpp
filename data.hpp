#ifndef __DATA_HPP__
#define __DATA_HPP__

#include <string>
#include "raw.hpp"
#include "con.hpp"
#include "sup.hpp"

class Data
{
    /**In physical units, i.e. data convention, i.e. input and output data files**/
public:

    Sup sup;
    Con con; 
    Raw raw;
     
        /**constructor and destructor**/
    Data();
    ~Data();

    bool read(
        /**three input raw, sup, and con name**/
        string raw_name,
        string sup_name,
        string con_name, 
            );
    
    bool write(
        /**three output raw, sup and con name**/
        string raw_name,
        string sup_name,
        string con_name, 
            )
    bool check(
        /**check grid optimization competition assumptions**/
            );
    
    bool scrub(
        /** modified certain data elements to meet grid optimization competition assumptions**/
            );
    
    bool convert_to_offline(
        /**converts the operating point to the office starting point**/
            );
    
    bool check_connectedness(
            bool scrub_mode
            );
    
    bool check_gen_implies_cost_gen(
            );

    bool check_cost_gen_implies_gen(
            );

    bool remove_generators_in_sup_not_in_raw(
            );
    
    bool check_generator_base_case_ramp_constraints_feasible(
            );

    bool check_load_base_case_ramp_constraints_feasible(
            );

    bool check_no_loads_in_sup_not_in_raw(
            );

    bool remove_loads_in_sup_not_in_raw(
            );

    bool check_no_loads_in_raw_not_in_sup(
            );

    bool check_no_lines_in_sup_not_in_raw(
            );

    bool remove_lines_in_sup_not_in_raw(
            );

    bool check_no_lines_in_raw_not_in_sup(
            );

    bool check_no_transformers_in_sup_not_in_raw(
            );

    bool remove_transformers_in_sup_not_in_raw(
            );

    bool check_no_transformers_in_raw_not_in_sup(
            );

    bool check_gen_costs(
            );

    bool check_load_costs(
            );

    bool scrub_gen_costs(
            );

    bool scrub_load_costs(
            );

    bool check_no_generators_in_con_not_in_raw(
            );

    bool check_no_branches_in_con_not_in_raw(
            );

    bool check_no_offline_generators_in_contingencies(
            );

    bool remove_contingencies_with_generators_not_in_raw(
            );

    bool remove_contingencies_with_branches_not_in_raw(
            );

    bool remove_contingencies_with_offline_generators(
            );

    bool check_no_offline_lines_in_contingencies(
            );

    bool remove_contingencies_with_offline_lines(
            );

    bool check_no_offline_transformers_in_contingencies(
            );

    bool remove_contingencies_with_offline_transformers(
            );

}
#endif
