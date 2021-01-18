#ifndef __SWITCHEDSHUNT_HPP__
#define __SWITCHEDSHUNT_HPP__

#include <string>
#include <vector>
class SwitchedShunt
{
public:
    //python: self.i = None, no default
    int i;
    int modsw;
    int adjm;
    int stat;
    double vswhi;
    double vswlo;
    int swrem;
    double rmpct;
    std::string rmidnt;
    double binit;
    int n1;
    double b1;
    int n2;
    double b2;
    int n3;
    double b3;
    int n4;
    double b4;
    int n5;
    double b5;
    int n6;
    double b6;
    int n7;
    double b7;
    int n8;
    double b8;
    std::vector<int> n;
    std::vector<double> b;
    int swsh_susc_count;

    /**constructor and destructor**/
    SwitchedShunt();
    ~SwitchedShunt();

    bool scrub(
            );

    bool scrub_binit(
            );

    bool scrub_swrem(
            );

    bool clean_rmidnt(
            );

    bool compute_bmin_bmax(
            );

    bool check(
            );

    bool check_swrem_zero(
            );

    bool check_b1_b2_opposite_signs(
            );

    bool check_n1_0_implies_b1_0_n2_0_b2_0(
            );

    bool check_b1_0_implies_n1_0_n2_0_b2_0(
            );

    bool check_n1_nonneg(
            );

    bool check_n2_nonneg(
            );

    bool check_n3_nonneg(
            );

    bool check_n4_nonneg(
            );

    bool check_n5_nonneg(
            );

    bool check_n6_nonneg(
            );

    bool check_n7_nonneg(
            );

    bool check_n8_nonneg(
            );

    bool check_n1_max(
            );

    bool check_n2_max(
            );

    bool check_n3_max(
            );

    bool check_n4_max(
            );

    bool check_n5_max(
            );

    bool check_n6_max(
            );

    bool check_n7_max(
            );

    bool check_n8_max(
            );

    bool check_n1_le_1(
            );

    bool check_n2_le_1(
            );

    bool check_n3_zero(
            );

    bool check_n4_zero(
            );

    bool check_n5_zero(
            );

    bool check_n6_zero(
            );

    bool check_n7_zero(
            );

    bool check_n8_zero(
            );

    bool check_b3_zero(
            );

    bool check_b4_zero(
            );

    bool check_b5_zero(
            );

    bool check_b6_zero(
            );

    bool check_b7_zero(
            );

    bool check_b8_zero(
            );

    bool check_bmin_le_binit_le_bmax(
            );

    bool read_from_row(
            std::string row
            );

};
#endif
