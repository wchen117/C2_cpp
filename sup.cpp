#include "sup.hpp"
#include <fstream>
#include <string>
#include <cerrno>
#include <iostream>
#include <assert.h>

#include "rapidjson/pointer.h"

Sup::Sup(){}

Sup::~Sup(){}

using namespace rapidjson;

void Sup::read(std::string file_name)
{
    sup_input = read_to_string(file_name);
    // parse the entire file into a rapidjson::Document object
    read_json();
}


void Sup::read_json()
{
    sup_doc.Parse(sup_input.c_str());
    
    // references points to each section in input json document
    Value& system_parameters = sup_doc["systemparameters"];
    Value& ref_loads = sup_doc["loads"];
    Value& ref_generators = sup_doc["generators"];
    Value& ref_lines = sup_doc["lines"];
    Value& ref_transformers = sup_doc["transformers"];
    Value& ref_pcblocks = sup_doc["pcblocks"];
    Value& ref_qcblocks = sup_doc["qcblocks"];
    Value& ref_scblocks = sup_doc["scblocks"];

    parse_system_parameters(system_parameters);
    parse_loads(ref_loads);
    parse_generators(ref_generators);
    parse_lines(ref_lines);
    parse_transformers(ref_transformers);



}

std::string Sup::read_to_string(std::string file_name)
{
    std::ifstream input(file_name, std::ios::in | std::ios::binary);
    input.clear();
    if (input)  
    {
        std::string contents2;
        input.seekg(0, std::ios::end);
        contents2.resize(input.tellg());
        input.seekg(0, std::ios::beg);
        input.read(&contents2[0], contents2.size());
        input.close();
        return contents2;
    
    }
    throw(errno);
}

void Sup::parse_system_parameters(Value& system_parameters)
{
    sys_prms.insert(std::make_pair( "delta", system_parameters["delta"].GetDouble()));
    sys_prms.insert(std::make_pair( "deltactg", system_parameters["deltactg"].GetDouble()));
    sys_prms.insert(std::make_pair( "deltar", system_parameters["deltar"].GetDouble()));
    sys_prms.insert(std::make_pair( "deltarctg", system_parameters["deltarctg"].GetDouble()));
}

void Sup::parse_loads(Value& tmp_loads)
{
    assert(tmp_loads.IsArray());

    for(SizeType idx = 0; idx < tmp_loads.Size(); idx++)
    {
        Sup_Load tmp_sup_load;
        
        tmp_sup_load.bus = tmp_loads[idx]["bus"].GetInt();
        tmp_sup_load.id = tmp_loads[idx]["id"].GetString();
        tmp_sup_load.tmin = tmp_loads[idx]["tmin"].GetDouble();
        tmp_sup_load.tmax = tmp_loads[idx]["tmax"].GetDouble();
        tmp_sup_load.prumax = tmp_loads[idx]["prumax"].GetDouble();
        tmp_sup_load.prdmax = tmp_loads[idx]["prdmax"].GetDouble();
        tmp_sup_load.prumaxctg = tmp_loads[idx]["prumaxctg"].GetDouble();
        Value& cblock_list = tmp_loads[idx]["cblocks"];
        for (SizeType jdx = 0; jdx < cblock_list.Size(); jdx++)
        {
            Sup_Cblock tmp_sup_cblock;
            tmp_sup_cblock.pmax = cblock_list[jdx]["pmax"].GetDouble();
            tmp_sup_cblock.c = cblock_list[jdx]["c"].GetDouble();
            tmp_sup_load.cblocks.push_back(tmp_sup_cblock);
        }

        loads.push_back(tmp_sup_load);
        
    } 

}   

void Sup::parse_generators(Value& tmp_generators)
{
    assert(tmp_generators.IsArray());
    for(SizeType idx = 0; idx < tmp_generators.Size(); idx++)
    {
        Sup_Generator tmp_sup_generator;
        tmp_sup_generator.bus = tmp_generators[idx]["bus"].GetInt();
        tmp_sup_generator.id = tmp_generators[idx]["id"].GetString();
        tmp_sup_generator.suqual = tmp_generators[idx]["suqual"].GetInt();
        tmp_sup_generator.sdqual = tmp_generators[idx]["sdqual"].GetInt();
        tmp_sup_generator.suqualctg = tmp_generators[idx]["suqualctg"].GetInt();
        tmp_sup_generator.sdqualctg = tmp_generators[idx]["sdqualctg"].GetInt();
        tmp_sup_generator.prumax = tmp_generators[idx]["prumax"].GetDouble();
        tmp_sup_generator.prdmax = tmp_generators[idx]["prdmax"].GetDouble();
        tmp_sup_generator.prumaxctg = tmp_generators[idx]["prumaxctg"].GetDouble();
        tmp_sup_generator.prdmaxctg = tmp_generators[idx]["prdmaxctg"].GetDouble();
        tmp_sup_generator.oncost = tmp_generators[idx]["oncost"].GetDouble();
        tmp_sup_generator.sucost = tmp_generators[idx]["sucost"].GetDouble();
        tmp_sup_generator.sdcost = tmp_generators[idx]["sdcost"].GetDouble();
        Value& cblock_list = tmp_generators[idx]["cblocks"];
        for (SizeType jdx = 0; jdx < cblock_list.Size(); jdx++)
        {
            Sup_Cblock tmp_sup_cblock;
            tmp_sup_cblock.pmax = cblock_list[jdx]["pmax"].GetDouble();
            tmp_sup_cblock.c = cblock_list[jdx]["c"].GetDouble();
            tmp_sup_generator.cblocks.push_back(tmp_sup_cblock);
        }
        generators.push_back(tmp_sup_generator);

    }
}

void Sup::parse_lines(Value& local_lines)
{
    assert(local_lines.IsArray());
    for(SizeType idx = 0; idx < local_lines.Size(); idx++)
    {
        Sup_Line tmp_sup_line;
        tmp_sup_line.origbus = local_lines[idx]["local_lines"].GetInt();
        tmp_sup_line.destbus = local_lines[idx]["destbus"].GetInt();
        tmp_sup_line.id = local_lines[idx]["id"].GetString();
        tmp_sup_line.swqual = local_lines[idx]["swqual"].GetInt();
        tmp_sup_line.csw = local_lines[idx]["csw"].GetDouble();
        lines.push_back(tmp_sup_line);
    }


}

void Sup::parse_transformers(Value& local_transformers)
{
    assert(local_transformers.IsArray());
    for(SizeType idx = 0; idx < local_transformers.Size(); idx++)
    {
        Sup_Transformer tmp_sup_tran;
        tmp_sup_tran.origbus = local_transformers[idx]["origbus"].GetInt();
        tmp_sup_tran.destbus = local_transformers[idx]["destbus"].GetInt();
        tmp_sup_tran.id = local_transformers[idx]["id"].GetString();
        tmp_sup_tran.swqual = local_transformers[idx]["swqual"].GetInt();
        tmp_sup_tran.csw = local_transformers[idx]["csw"].GetDouble();
        transformers.push_back(tmp_sup_tran);
        
    }

}