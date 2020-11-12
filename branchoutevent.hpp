#ifndef __BRANCHOUTEVENT_HPP__
#define __BRANCHOUTEVENT_HPP__

class BranchOutEvent
{
public:
    // python: self.i = None, no default
    int i;
    // python: self.j = None, no default
    int j;
    // python: self.ckt = None, no default
    string ckt;

    /**constructor and destructor**/
    bool check(
            );

    bool read_from_row(
            string row
            );

    bool read_from_csv(
            string row
            );
    
    bool construct_record_row(
            );
}

#endif
