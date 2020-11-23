#include "raw.hpp"
#include<fstream>
#include<string>
#include<cerrno>
#include<vector>
#include<iostream>
#include <sstream>

/**constructor and desctructor**/
Raw::Raw(){}

Raw::~Raw(){}


void Raw::read(std::string file_name)
{
    raw_input = read_to_string(file_name);
    string_to_section();
    std::vector<std::string> id_bus_section = lines_in_section(0); 
    std::vector<std::string> load_section = lines_in_section(1);
    std::vector<std::string> fixed_shunt_section = lines_in_section(2);
    std::vector<std::string> generator_section = lines_in_section(3);
    std::vector<std::string> nontransformerbranch_section = lines_in_section(4);

    parse_case_id_bus(id_bus_section);
    parse_load(load_section);
    parse_fixed_bus_shunt(fixed_shunt_section);
    parse_generator(generator_section);
    //parse_non_transformer_branch(nontransformerbranch_section);
    
    //this->string_to_section();
    // parse case identification data and bus data
    //parse_non_transformer_branch();
    //parse_transformer();
    //parse_area();
    //parse_two_terminal_dc_transmission_line();
    //parse_vsc_dc_transmission_line();
    //parse_transformer_impedance_correction_table();
    //parse_multisection_line_grouping();
    //parse_zone();
    //parse_interarea_transfer();
    //parse_owner();
    //parse_facts_device();
    //parse_switched_shunt();
    //parse_gne_device();
    //parse_induction_machine();
}

std::string Raw::read_to_string(std::string file_name)
{
    // read in case.raw file into a string
    std::ifstream input(file_name, std::ios::in | std::ios::binary);
    input.clear();
    if (input)  
    {   
        std::string container;
        input.seekg(0, std::ios::end);
        container.resize(input.tellg());
        input.seekg(0, std::ios::beg);
        input.read(&container[0], container.size());
        input.close();   
        return container;
    
    }
    throw(errno);
}

<<<<<<< HEAD
bool Raw::read(string file_name)
{
     

}

=======
void Raw::string_to_section()
{
    // parse the different section of case.raw file
    // The begining of each section is marked by "0 /" 
    // Note the Case Identification Data and Bus Date are not
    // separated by "0 /". 
    rows_sections = parse_on_delimiter(raw_input, "0 /");

}

std::vector<std::string> Raw::parse_on_delimiter(std::string input_string, std::string delimiter)
{
    std::vector<std::string> parsed_string_vector;
    std::size_t start = 0;
    std::size_t end = input_string.find(delimiter);

    while(end != std::string::npos)
    {
         parsed_string_vector.push_back(input_string.substr(start, end - start));
         start = end + delimiter.length();
         end = input_string.find(delimiter, start);
    }
    parsed_string_vector.push_back(input_string.substr(start, std::string::npos));

    return parsed_string_vector;

}

std::vector<std::string> Raw::lines_in_section(size_t section_num)
{
    // parse each section to vectors of lines
    std::vector<std::string> section_vector;
    std::istringstream sectionstream (rows_sections[section_num]);
    std::string temp;
    while(std::getline(sectionstream, temp))
    {
        section_vector.push_back(temp);
    }
    return section_vector;
    
}


void Raw::parse_case_id_bus(std::vector<std::string> section_lines)
{
   // case identification and bus date corresponds to
   // section_vector[0]
>>>>>>> simple

   parse_case_id(section_lines[0], section_lines[1], section_lines[2]);

   for (int idx = 3; idx<section_lines.size();idx++)
   {
       Bus tmp_bus;
       parse_bus(section_lines[idx], tmp_bus);
       buses.insert(std::make_pair(tmp_bus.i, tmp_bus));
   }
 
}

void Raw::parse_bus(std::string each_line, Bus &bus_ref)
{
    std::vector<std::string> line_vector = parse_on_delimiter(each_line, ",");
    bus_ref.i = std::stoi(line_vector[0]);
    bus_ref.name = line_vector[1];
    bus_ref.baskv = std::stod(line_vector[2]);
    bus_ref.ide = std::stoi(line_vector[3]);
    bus_ref.area = std::stoi(line_vector[4]);
    bus_ref.zone = std::stoi(line_vector[5]);
    bus_ref.owner = std::stoi(line_vector[6]);
    bus_ref.vm = std::stod(line_vector[7]);
    bus_ref.va = std::stod(line_vector[8]);
    bus_ref.nvhi = std::stod(line_vector[9]);
    bus_ref.nvlo = std::stod(line_vector[10]);

}
void Raw::parse_case_id(std::string line1, std::string line2, std::string line3)
{
   std::vector<std::string> first_line = parse_on_delimiter(line1, ",");
   CaseIdentificationData.ic = std::stoi(first_line[0]);
   CaseIdentificationData.sbase = std::stod(first_line[1]);
   CaseIdentificationData.rev = std::stoi(first_line[2]);
   CaseIdentificationData.xfrrat = std::stoi(first_line[3]);
   CaseIdentificationData.nxfrat = std::stoi(first_line[4]);
   CaseIdentificationData.nxfrat = std::stod(first_line[5]);
   CaseIdentificationData.record_2 = line2;
   CaseIdentificationData.record_3 = line3;

}
void Raw::parse_load(std::vector<std::string> load_section)
{
   // case identification and bus date corresponds to
   // section_vector[0]
   // load_section[0] = "END OF BUS DATA, BEGIN LOAD DATA", skip this line

   for (int idx=1;idx<load_section.size(); idx++)
   {
       std::vector<std::string> line_vector = parse_on_delimiter(load_section[idx], ",");
       
       Load tmp_load;
       tmp_load.i = std::stoi(line_vector[0]);
       tmp_load.id = line_vector[1];
       tmp_load.status = std::stoi(line_vector[2]);
       tmp_load.area = std::stoi(line_vector[3]);
       tmp_load.zone = std::stoi(line_vector[4]);
       tmp_load.pl = std::stod(line_vector[5]);
       tmp_load.ql =  std::stod(line_vector[6]);
       tmp_load.ip = std::stod(line_vector[7]);
       tmp_load.iq = std::stod(line_vector[8]);
       tmp_load.yp = std::stod(line_vector[9]);
       tmp_load.yq = std::stod(line_vector[10]);
       tmp_load.owner = std::stoi(line_vector[11]);
       tmp_load.scale = std::stoi(line_vector[12]);
       tmp_load.intrpt = std::stoi(line_vector[13]);
       loads.insert(std::make_pair(tmp_load.i, tmp_load));
   }
}

void Raw::parse_fixed_bus_shunt(std::vector<std::string> fixed_shunt_section)
{
    // fixed_shunt_section[0] = "END OF LOAD DATA, BEGIN FIXED SHUNT DATA", skip this line;
    for (int idx=1; idx<fixed_shunt_section.size(); idx++)
    {
        std::vector<std::string> line_vector = parse_on_delimiter(fixed_shunt_section[idx], ",");
        FixedShunt tmp_shunt;
        tmp_shunt.i = std::stoi(line_vector[0]);
        tmp_shunt.id = line_vector[1];
        tmp_shunt.status = std::stoi(line_vector[2]);
        tmp_shunt.gl = std::stod(line_vector[3]);
        tmp_shunt.bl = std::stod(line_vector[4]);
        shunts.insert(std::make_pair(tmp_shunt.i, tmp_shunt));
    }   
    
}
void Raw::parse_generator(std::vector<std::string> generator_section)
{ 
    // 
    for(int idx=1; idx<generator_section.size(); idx++)
    {
        std::vector<std::string> line_vector = parse_on_delimiter(generator_section[idx], ",");
        Generator tmp_generator;
        tmp_generator.i = std::stoi(line_vector[0]);
        tmp_generator.id = line_vector[1];
        tmp_generator.pg = std::stod(line_vector[2]);
        tmp_generator.qg = std::stod(line_vector[3]);
        tmp_generator.qb = std::stod(line_vector[4]);
        tmp_generator.vs = std::stod(line_vector[5]);
        tmp_generator.ireg = std::stoi(line_vector[6]);
        tmp_generator.mbase = std::stod(line_vector[7]);
        tmp_generator.zr = std::stod(line_vector[8]);
        tmp_generator.zx = std::stod(line_vector[9]);
        tmp_generator.rt = std::stod(line_vector[10]);
        tmp_generator.xt = std::stod(line_vector[11]);
        tmp_generator.gtap = std::stod(line_vector[12]);
        tmp_generator.stat = std::stod(line_vector[13]);
        tmp_generator.rmpct = std::stod(line_vector[14]);
        tmp_generator.pt = std::stod(line_vector[15]);
        tmp_generator.pb = std::stod(line_vector[16]);
        tmp_generator.o1 = std::stoi(line_vector[17]);
        tmp_generator.f1 = std::stod(line_vector[18]);
        tmp_generator.o2 = std::stoi(line_vector[19]);
        tmp_generator.f2 = std::stod(line_vector[20]);  
        tmp_generator.o3 = std::stoi(line_vector[21]);
        tmp_generator.f3 = std::stod(line_vector[22]);
        tmp_generator.o4 = std::stoi(line_vector[23]);
        tmp_generator.f4 = std::stod(line_vector[24]);
        tmp_generator.wmod = std::stoi(line_vector[25]);
        tmp_generator.wpf = std::stoi(line_vector[26]);
        generators.insert(std::make_pair(tmp_generator.i, tmp_generator));
    }
}

void Raw::parse_nontransformerbranch(std::vector<std::string> nontranformerbranch_section)
{
    for (int idx=1; idx<nontranformerbranch_section.size(); idx++)
    {
        std::vector<std::string> line_vector = parse_on_delimiter(nontranformerbranch_section[idx], ",");

    }
}
