#ifndef __FIXEDSHUNT_HPP__
#define __FIXEDSHUNT_HPP__

#include <string>

class FixedShunt
{
public:
    // python: self.i = None, no default allowed
    int i;
    std::string id;
    int status;
    double gl;
    double bl;

    /**constructor and desctructor**/

    FixedShunt();
    ~FixedShunt();

    bool check(
            );

    bool scrub(
            );

    bool check_id_len_1_or_2(
            );

    bool read_from_row(
            std::string row
            ); 


};
#endif
