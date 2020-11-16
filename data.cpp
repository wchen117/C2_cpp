#include "data.hpp"
#include "iostream"
#include <string>
#include <vector>

// constructor
Data::Data() {
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
    std::string raw_input = raw.read(raw_name);
    std::string sup_input = sup.read(sup_name);
    std::string con_input = con.read(con_name);

    std::cout<<raw_input<<"\n";
    std::cout<<sup_input<<"\n";
    std::cout<<con_input<<"\n";

    return true;
}

bool Data::write(
    std::string raw_name,
    std::string sup_name,
    std::string con_name
                 )
{
    return true;
    
}


