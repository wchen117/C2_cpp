#ifndef __TRANSFORMERIMPEDANCECORRECTIONTABLE_HPP__
#define __TRANSFORMERIMPEDANCECORRECTIONTABLE_HPP__

#include <vector>
class TransformerImpedanceCorrectionTable
{
public:
    // python: self.i = None, no default
    int i;
    double t1;
    double f1;
    double t2;
    double f2;
    double t3;
    double f3;
    double t4;
    double f4;
    double t5;
    double f5;
    double t6;
    double f6;
    double t7;
    double f7;
    double t8;
    double f8;
    double t9;
    double f9;
    double t10;
    double f10;
    double t11;
    double f11;
    
    // assume type double for t and f
    vector<double> t;
    vector<double> f;

    /**constructor and desctructor**/

    TransformerImpedanceCorrectionTable();
    ~TransformerImpedanceCorrectionTable();

    bool read_from_row(
            string row
            );


}

#endif
