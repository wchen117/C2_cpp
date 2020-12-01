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
    raw.read(raw_name);
    con.read(con_name);
    
  

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


