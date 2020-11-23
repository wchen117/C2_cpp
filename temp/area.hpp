#ifndef __AREA_HPP__
#define __AREA_HPP__

#include <string>

class Area
{
public:
    // python: self.i = None, no default
    int i;
    int isw;
    double pdes;
    double ptol;
    string arname;

    /**constructor and destructor**/
    Area();
    ~Area();

    bool clean_arname(
            );
    
    bool check(
            );

    bool check_i_pos(
            );

    bool read_from_row(
            string row
            );

}
#endif

