#ifndef __ZONE_HPP__
#define __ZONE_HPP__

#include<string>

class Zone
{
public:
    //python self.i = None, no default
    int i;
    std::string zoname;

    /**constructor and destructor**/
    Zone();
    ~Zone();

    bool clean_zoname(
            );

    bool check(
            );

    bool check_i_pos(
            );

    bool read_from_row(
            std::string row
            );  

};
#endif
