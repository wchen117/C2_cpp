#include "data.hpp"
#include "iostream"
#include <string>
#include <vector>
#include "raw.hpp"
#include "con.hpp"
#include "sup.hpp"

// constructor
Data::Data() {
    Raw raw;
    Con con;
    Sup sup;
}

// destructor
Data::~Data() {

}


bool Data::read(
    std::string raw_name,
    std::string sup_name,
    std::string con_name
                )
{
    std::cout<<raw_name<<"\n";
    std::cout<<sup_name<<"\n";
    std::cout<<con_name<<"\n";

    //std::string raw_input = raw.read(raw_name);
    //std::cout<<raw_input;
    //sup.read(sup_name);
    //con.read(con_name);
    return true;
}

bool Data::write(
    std::string raw_name,
    std::string sup_name,
    std::string con_name
                 )
{
    //raw.write(raw_name);
    //sup.write(sup_name);
    //con.write(con_name);
    return true;
    
}


