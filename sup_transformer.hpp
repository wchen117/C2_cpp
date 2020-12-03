#ifndef __SUP_TRANSFORMER_HPP__
#define __SUP_TRANSFORMER_HPP__

#include <string>

class Sup_Transformer
{
public:
    int origbus;
    int destbus;
    std::string id;
    int swqual;
    double csw;

    Sup_Transformer();
    ~Sup_Transformer();


};
#endif