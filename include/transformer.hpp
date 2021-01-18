#ifndef __TRANSFORMER_HPP__
#define __TRANSFORMER_HPP__

#include <string>

class Transformer
{
public:
    // python: self.i = None, no default
    int i;
    // ptyhon: self.j = None, no default
    int j;
    int k;
    std::string ckt;
    int cw;
    int cz;
    int cm;
    double mag1;
    double mag2;
    int nmetr;
    std::string name;
    int stat;
    int o1;
    double f1;
    int o2;
    double f2;
    int o3;
    double f3;
    int o4;
    double f4;
    std::string vecgrp;
    double r12;
    int x12;
    double sbase12;
    double windv1;
    double nomv1;
    double ang1;
    double rata1;
    double ratb1;
    double ratc1;
    int cod1;
    int cont1;
    double rma1;
    double rmi1;
    double vma1;
    double vmi1;
    int ntp1;
    int tab1;
    double cr1;
    double cx1;
    double cnxa1;
    double windv2;
    double nomv2;

    /**constructor and destructor**/
    Transformer();
    ~Transformer();

    bool scrub(
            );

    bool check(
            );

    bool check_cod1_01(
            );

    bool check_ntp1_odd_ge_1(
            );

    bool check_tau_theta_init_feas(
            bool scrub_mode =false
            );

    bool check_k_0(
            );

    bool check_i_lt_j(
            );

    bool check_i_ne_j(
            );

    bool check_ckt_len_1_or_2(
            );

    bool check_r12_x12_nonzero(
            );

    bool check_rata1_pos(
            );

    bool check_ratc1_pos(
            );

    bool check_ratc1_rata1_consistent(
            );

    bool check_windv1_pos(
            );

    bool check_windv2_pos(
            );

    bool check_windv2_eq_1(
            );

    // python: @property decorator
    bool num_windings(
            );

    bool get_num_rows_from_row(
            std::string row
            );

    bool read_from_rows(
            std::string rows
            );

    bool pad_rows(
            std::string rows
            );

    bool flatten_rows(
            std::string rows
            );

    bool read_from_row(
            std::string row
            );




};
#endif
