#ifndef __SUP_LINE_HPP__
#define __SUP_LINE_HPP__

#include <string>

class Sup_Line
{
public:
    int origbus;
    int destbus;
    std::string id;
    int swqual;
    double csw;

    Sup_Line();
    ~Sup_Line();

};

#endif