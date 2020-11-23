#ifndef __SUP_HPP__
#define __SUP_HPP__

#include <map>
#include <string>

class Sup
{
public:

    std::string sup_input;
    /**constructors and destructors**/
    Sup();
    ~Sup();

    std::string read(
         std::string file_name
            );

    bool write(
         std::string file_name
            );  
        
};
#endif
