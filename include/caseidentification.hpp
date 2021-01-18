#ifndef __CASEIDENTIFICATION_HPP__
#define __CASEIDENTIFICATION_HPP__

#include<string>

class CaseIdentification
{
public:
    int ic;
    double sbase;
    int rev;
    int xfrrat;
    int nxfrat;
    double basfrq;
    std::string record_2;
    std::string record_3;


    /**constructor and desctructor**/
    CaseIdentification();
    ~CaseIdentification();

    bool check(
            );

    bool check_sbase_positive(
            );

    bool read_record_1_from_row(
            std::string row
            );

    bool read_from_rows(
            std::string rows
            );
     

};
#endif
