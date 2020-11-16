#ifndef __CASEIDENTIFICATION_HPP__
#define __CASEIDENTIFICATION_HPP__

#include <string>

class CaseIdentification
{
public:
    int ic;
    double sbase;
    int rev;
    int xfrrat;
    int nxfrat;
    double basfrq;
    string record_2;
    string record_3;


    /**constructor and desctructor**/
    CaseIdentification();
    ~CaseIdentification();

    bool check(
            );

    bool check_sbase_positive(
            );

    bool read_record_1_from_row(
            string row
            );

    bool read_from_rows(
            string rows
            );
     

}
#endif
