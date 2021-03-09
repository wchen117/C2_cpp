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


};
#endif
