#ifndef __CON_HPP__
#define __CON_HPP__

#include <map>
#include <string>

#include "contigency.hpp"

class Con

{
public:
    
    map<Contigency, int> contigencies;
    
    bool check(
            );

    Contingency get_contingencies(
            );

    string construct_data_records(
            );

    string construct_end_record(
            );

    /**constructor and desctructor**/
    Con();
    ~Con();

    bool write(
            string file_name
            );
    
    // python: target_contingency default to None, how to translate? 
    bool read(
            string file_name,
            Contigency target_contingency 
            );
    
    bool row_is_file_end(
            string row
            );

    bool is_contingency_start(
            string row
            ); 
    
    bool is_end(
            string row
            );

    bool is_branch_out_event(
            string row
            );

    bool is_three_winding(
            string row
            );

    bool is_generator_out_event(
            string row
            );

    // python: target_congingency default to None
    bool read_from_rows(
            string rows,
            Contigency target_contingency
            );

    
}
#endif
