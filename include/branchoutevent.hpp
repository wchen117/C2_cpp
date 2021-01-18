#ifndef __BRANCHOUTEVENT_HPP__
#define __BRANCHOUTEVENT_HPP__

#include <string>
class BranchOutEvent
{
public:
    // python: self.i = None, no default
    int i;
    // python: self.j = None, no default
    int j;
    // python: self.ckt = None, no default
    std::string ckt;

    BranchOutEvent();
    ~BranchOutEvent();

    /**constructor and destructor**/
    bool check(
            );

    bool read_from_row(
            std::string row
            );

    bool read_from_csv(
            std::string row
            );
    
    bool construct_record_row(
            );
};

#endif
