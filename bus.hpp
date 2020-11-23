#ifndef __BUS_HPP__
#define __BUS_HPP__

#include<string>

class Bus
{
public:
    //python: self.i = None, no default allowed
    int i;
    std::string name;
    double baskv;
    int ide;
    int area;
    int zone;
    int owner;
    double vm;
    double va;
    double nvhi;
    double nvlo;
    double evhi;
    double evlo;

    /**constructor and destructor**/
    Bus();
    ~Bus();

    bool scrub(
            );

    bool check(
            );

    bool clean_name(
            );

    bool check_ide_ne_4(
            );

    bool check_i_pos(
            );

    bool check_area_pos(
            );

    bool check_vm_pos(
            );

    bool check_nvhi_pos(
            );

    bool check_nvlo_pos(
            );

    bool check_evhi_pos(
            );

    bool check_evlo_pos(
            );

    bool check_nvhi_nvlo_consistent(
            );

    bool check_evhi_evlo_consistent(
            );

    bool check_evhi_nvhi_consistent(
            );

    bool check_nvlo_evlo_consistent(
            );

    bool read_from_row(
            std::string row
            );


};
#endif
