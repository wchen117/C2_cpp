#ifndef __SUP_HPP__
#define __SUP_HPP__

#include <string>
#include <set>
#include <unordered_map>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "sup_generator.hpp"
#include "sup_transformer.hpp"
#include "sup_line.hpp"
#include "sup_load.hpp"


class Sup
{
public:

    // string representation of *.json file input
    std::string sup_input;
    // json representation of sup_input
    rapidjson::Document sup_doc;

    bool pcblocks_sorted;
    bool qcblocks_sorted;
    bool scblocks_sorted;
    std::set<int> generator_ids;
    std::set<int> load_ids;
    std::set<int> line_ids;
    std::set<int> transformer_ids;
    
    std::unordered_map<int, std::string> sys_prms;
    std::vector<Sup_Load> loads;
    std::vector<Sup_Line> lines;
    std::vector<Sup_Generator> generators;
    std::vector<Sup_Transformer> transformers;

 
    std::vector<double> scblocks_tmax;
    std::vector<double> scblocks_c;

    std::vector<double> pcblocks_pmax;
    std::vector<double> pcblocks_c;

    std::vector<double> qcblocks_qmax;
    std::vector<double> qcblocks_c;

    /**constructors and destructors**/
    Sup();
    ~Sup();

    void read(
         std::string file_name
            );
    
    void read_json(
    );
    
    std::string read_to_string(
       std::string file_name
    );

    bool write(
         std::string file_name
            );  
        
    void parse_system_parameters(
         rapidjson::Value& sys_prms
          );
};
#endif
