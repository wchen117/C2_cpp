#ifndef __CONTINGENCY_HPP__
#define __CONTINGENCY_HPP__

#include <string>
#include <vector>
#include "branchoutevent.hpp"
#include "generatoroutevent.hpp"

class Contingency
{
    public:
    std::string label;
    std::vector<BranchOutEvent> branch_out_events;
    std::vector<GeneratorOutEvent> generator_out_events;

    Contingency();
    ~Contingency();

};

#endif