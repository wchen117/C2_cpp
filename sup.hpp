#ifndef __SUP_HPP__
#define __SUP_HPP__

#include <map>
#include <string>

class Sup
{
public:
    /**constructors and destructors**/
    Sup();
    ~Sup();

    bool read(
         std::string file_name
            );

    bool write(
         std::string file_name
            );  
        
};
#endif
