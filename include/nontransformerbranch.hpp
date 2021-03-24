#ifndef __NONTRANSFORMERBRANCH_HPP__
#define __NONTRANSFORMERBRANCH_HPP__

#include<string>

class NontransformerBranch
{
public:
    int i;
    int j;
    std::string ckt;
    double r;
    double x;
    double b;
    double ratea;
    double rateb;
    double ratec;
    double gi;
    double bi;
    double gj;
    double bj;
    int st;
    int met;
    double len;
    int o1;
    double f1;
    int o2;
    double f2;
    int o3;
    double f3;
    int o4;
    double f4;

    /**constructor and destructor**/
    NontransformerBranch();
    ~NontransformerBranch();

    bool scrub(
            );

    bool check(
            );

    bool check_i_lt_j(
            );

    bool check_i_ne_j(
            );

    bool check_ckt_len_1_or_2(
            );

    bool check_r_x_nonzero(
            );
    
    bool check_ratea_pos(
            );
  
    bool check_ratec_pos(
            );

    bool check_ratec_ratea_consistent(
            );

    bool read_from_row(
            );

};
#endif
