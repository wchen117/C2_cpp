#ifndef __GENERATOR_HPP__
#define __GENERATOR_HPP__

#include<string>
class Generator
{
public:
    int i;
    std::string id;
    double pg;
    double qg;
    double qt;
    double qb;
    double vs;
    int ireg;
    double mbase;
    double zr;
    double zx;
    double rt;
    double xt;
    double gtap;
    double stat;
    double rmpct;
    double pt;
    double pb;
    int o1;
    double f1;
    int o2;
    double f2;
    int o3;
    double f3;
    int o4;
    double f4;
    int wmod;
    double wpf;

    /**generator and destructor**/
    Generator();
    ~Generator();

    bool check(
            );

    bool scrub(
            );

    bool add_emergency_capacity(
            );

    bool check_pg_nonnegative(
            );

    bool scrub_pg_nonnegative(
            );

    bool check_id_len_1_or_2(
            );

    bool check_pg_stat_consistent(
            );

    bool check_qg_stat_consistent(
            );

    bool check_qt_qb_consistent(
            );

    bool check_pt_pb_consistent(
            );

    bool scrub_pg_stat_consistent(
            );

    bool scrub_qg_stat_consistent(
            );

    bool check_pb_nonnegative(
            );

    bool read_from_row(
            std::string row
            );
    
      

};

#endif
