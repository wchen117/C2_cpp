#ifndef __CON_HPP__
#define __CON_HPP__

#include <map>
#include <string>

<<<<<<< HEAD
#include "contingency.hpp"
=======
>>>>>>> simple

class Con

{
public:

    std::string con_input;

    Con();
    ~Con();

    bool write(
            std::string file_name
            );
    
    // python: target_contingency default to None, how to translate? 
    std::string read(
            std::string file_name
            );
    // python: target_congingency default to None
    bool read_from_rows(
            std::string rows
            );

    
};
#endif
