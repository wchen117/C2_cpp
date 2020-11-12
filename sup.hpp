#ifndef __SUP_HPP__
#define __SUP_HPP__

#include <map>
#include <string>
#include "transformer.hpp"
#include "line.hpp"
#include "generator.hpp"
#include "load.hpp"

class Sup
{
public:
    map<string, map<string, int>> sup_jsonobj;
    
    bool pcblocks_sorted;
    bool qcblocks_sorted;
    bool scblocks_sorted;

    std::set<int> generator_ids;
    std::set<int> load_ids;
    std::set<int> line_ids;
    std::set<int> transformer_ids;

    map<Transformer, int> transformers;
    map<Line, int> lines;
    map<Generator, int> generators;

    //python: scblocks_tmax = [], type unkown
    std::vector<int> scblocks_tmax;
    std::vector<int> scblacks_c;

    std::vector<int> pcblocks_pmax;
    std::vector<int> pcblocks_c;

    std::vector<int> qcblocks_qmax;
    std::vector<int> qcbloacks_c;

    bool scrub_mode;
    bool do_force_defaults;

    /**constructors and destructors**/
    Sup();
    ~Sup();

    bool scrub_pcblocks(
            map<string, int> cblock
                        );

    bool scrub_qcblocks(
            map<string, int> cblock
            );

    bool scrub_scbloacks(
            map<string, int> cblock
            );

    bool validateJson(
            string schema_path,
            string instance_path
            );

    bool assert_continue(
            bool condition,
            string error_string,
            bool scrube_info
            );


    bool scrub_pqscblocks(
            map<string, map<string, int> > scrub_info
            );
   
    bool scrub_delta(
            map<string, map<string, int> > scrub_info
            );

    bool scrub_load_tmin_tmax(
            map<string, map<string, int> > scrub_info
            );

    bool scrub_gen_prumax_nonneg(
            map<string, map<string, int> > scrub_info
            );  

    bool scrub_gen_prdmax_nonneg(
            map<string, map<string, int> > scrub_info
            );

    bool scrub_load_prumax_nonneg(
             map<string, map<string, int> > scrub_info
            );    
    bool scrub_load_prdmax_nonneg(
            map<string, map<string, int> > scrub_info
            ); 

    bool scrub_gen_prumaxctg_nonneg(
             map<string, map<string, int> > scrub_info
            );
        
    bool scrub_gen_prdmaxctg_nonneg(
            map<string, map<string, int> > scrub_info
            );    

    bool scrub_load_prumaxctg_nonneg(
            map<string, map<string, int> > scrub_info
            );
    
    bool scrub_load_prdmaxctg_nonneg(
            map<string, map<string, int> > scrub_info
            );

    bool remove_loads(
            // keys type unknown
            string keys
            );

    bool remove_generators(
            // keys type unknown
            string keys
            );

    bool remove_lines(
            string keys
            );

    bool remove_transformers(
            string keys
            );

    bool check(
            bool scrub_mode=false
            );

    bool check_system_parameters(
            //system_parameters type unknow
            string system_parameters
            );

    bool check_load(
            Load load
            );

    bool check_generator(
            Generator generator
            );

    bool check_line(
            Line line
            );

    bool check_transformer(
            Transformer transfromer
            );

    bool check_cblock(
            // max_prefix type unknown, default to None
            // cblock_prefix type unknown, default to None
            map<string, int> cblock,
            string max_prefix,
            string cblock_prefix,
            );

    bool check_pcblock(
            // pcblock type unknown
            map<string, int> pcblock
            );

    bool check_qcblock(
            //qcblock type unknown
            map<string, int> qcblock
            string max_prefix;
            string cblock_prefix  
            );

    bool check_scblock(
            //scblock type unkown
            map<string, int> scblock,
            string max_prefix,
            string cblock_prefix
            );

    bool check_qpscblocks(
            map<string, int> cblocks, 
            string pqs);

    bool get_value(
            string key
            );

    bool get_system_parameters(
            );

    bool get_loads(
            );

    bool get_generators(
            );

    bool force_defaults(
            );

    bool init(
            );

    bool init_generators(
            );

    bool init_lines(
            );

    bool init_transformers(
            );

    bool convert_generator_cblock_units(
           //base_mva type unknown
           int base_mva  
            );

    bool convert_load_cblock_units(
           //base_mva type unknown
           int base_mva
            );

    bool convert_pcblock_units(
            int base_mva  
            );
    
    bool convert_qcblock_units(
            int base_mva
            );

    bool convert_scblock_units(
            int base_mva
            );

    bool init_loads(
            );

    bool get_lines(
            );

    bool get_transformers(
            );

    bool revert_pr_maxctg_to_pr_max(
            );

    bool revert_pcblocks_to_default(
            );

    bool revert_qcblocks_to_default(
            );

    bool revert_scblocks_to_default(
            );

    bool get_pcblocks(
            );

    bool get_qcblocks(
            );

    bool get_scblocks(
            );

    bool get_generator_ids(
            );

    bool get_load_ids(
            );

    bool get_line_ids(
            );

    bool get_transformer_ids(
            );

    bool read(
         string file_name
            );

    bool write(
         string file_name
            );  
        
}
#endif
