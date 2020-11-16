#include "data.hpp"
#include "iostream"
#include <string>
#include <vector>

// constructor
Data::Data() {
    Raw raw = Raw();
    Con con = Con();
    Sup sup = Sup();
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
    sup.read(sup_name);
    con.read(con_name);
    return true;
}

bool Data::write(
    std::string raw_name,
    std::string sup_name,
    std::string con_name
                 )
{
    raw.write(raw_name);
    sup.write(sup_name);
    con.write(con_name);
    return true;
    
}


