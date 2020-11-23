#ifndef __TRANSFORMERIMPEDANCECORRECTIONTABLE_HPP__
#define __TRANSFORMERIMPEDANCECORRECTIONTABLE_HPP__

#include <vector>
class TransformerImpedanceCorrectionTable
{
public:
    // python: self.i = None, no default
    int i;
    
    // assume type double for t and f
    std::vector<double> t;
    std::vector<double> f;

    /**constructor and desctructor**/

    TransformerImpedanceCorrectionTable();
    ~TransformerImpedanceCorrectionTable();

    bool read_from_row(
            std::string row
            );


};
#endif
