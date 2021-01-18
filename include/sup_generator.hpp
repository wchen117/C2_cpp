#ifndef __SUP_GENERATOR_HPP__
#define __SUP_GENERATOR_HPP__
#include <string>
#include <vector>
#include <unordered_map>
#include "sup_cblock.hpp"

class Sup_Generator
{
    public:
    int bus;
    std::string id;
    int suqual;
    int sdqual;
    int suqualctg;
    int sdqualctg;
    double prumax;
    double prdmax;
    double prumaxctg;
    double prdmaxctg;
    double oncost;
    double sucost;
    double sdcost;
    std::vector<Sup_Cblock> cblocks; 

    Sup_Generator();
    ~Sup_Generator();



};
#endif