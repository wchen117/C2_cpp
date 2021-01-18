#ifndef __DATA_HPP__
#define __DATA_HPP__
#include "raw.hpp"
#include "con.hpp"
#include "sup.hpp"


#include <string>

class Data
{
    /**In physical units, i.e. data convention, i.e. input and output data files**/
public:

    Raw raw;
    Con con;
    Sup sup;

        /**constructor and destructor**/
    Data();
    ~Data();

    bool read(
        /**three input raw, sup, and con name**/
        std::string raw_name,
        std::string sup_name,
        std::string con_name
            );
    
    bool write(
        /**three output raw, sup and con name**/
        std::string raw_name,
        std::string sup_name,
        std::string con_name 
            );

};
#endif
