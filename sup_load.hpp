#ifndef __SUP_LOAD_HPP__
#define __SUP_LOAD_HPP__

#include <string>
#include <vector>
#include "sup_cblock.hpp"
class Sup_Load
{
    public:
    int bus;
    std::string id;
    double tmin;
    double tmax;
    double prumax;
    double prdmax;
    double prumaxctg;
    std::vector<Sup_Cblock> blocks;

    Sup_Load();
    ~Sup_Load();


};

#endif