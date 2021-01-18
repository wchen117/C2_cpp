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
#include "sup_pcblock.hpp"
#include "sup_qcblock.hpp"
#include "sup_scblock.hpp"


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
    
    std::unordered_map<std::string, double> sys_prms;
    std::vector<Sup_Load> loads;
    std::vector<Sup_Line> lines;
    std::vector<Sup_Generator> generators;
    std::vector<Sup_Transformer> transformers;

    std::vector<Sup_Pcblock> pcblocks;
    std::vector<Sup_Qcblock> qcblocks;
    std::vector<Sup_Scblock> scblocks;

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
         rapidjson::Value&  system_parameters
          );
    void parse_loads(
         rapidjson::Value&  tmp_loads
          );
    void parse_generators(
         rapidjson::Value& tmp_generators
         );
    void parse_lines(
         rapidjson::Value& local_lines
         ); 
    void parse_transformers(
         rapidjson::Value& local_transformers
         );
    void parse_pcblocks(
       std::vector<Sup_Pcblock>& dest_attr,
       rapidjson::Value& local_blocks
       );
    void parse_qcblocks(
       std::vector<Sup_Qcblock>& dest_attr,
       rapidjson::Value& local_blocks
       );
    void parse_scblocks(
       std::vector<Sup_Scblock>& dest_attr,
       rapidjson::Value& local_blocks
       );
};
#endif
