#ifndef __LOAD_HPP__
#define __LOAD_HPP__
#include <string>

class Load
{
public:
    //python, self.i = None, no default allowed
    int i;
    std::string id;
    int status;
    int area;
    int zone;
    double pl;
    double ql;
    double ip;
    double iq;
    double yp;
    double yq;
    int owner;
    int scale;
    int intrpt;

    /**constructor and desctructor**/
    Load();
    ~Load();
    
    bool check(
            );

    bool scrub(
            );

    bool check_id_len_1_or_2(
            );

    bool read_from_row(
            std::string row
            );



};

#endif
