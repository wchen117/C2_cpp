#ifndef __RAW_HPP__
#define __RAW_HPP__

#include <map>
#include <memory>
#include <string>
#include <vector>

class Raw
{

public:

    std::string raw_input;
    /**constructor and destructor**/
    Raw();
    ~Raw();

    bool write(
            std::string file_name
            );

    std::string read(
            std::string file_name
            );
    bool row_is_file_end(
            int row
            );

    bool row_is_section_end(
            int row
            );

    // not sure type of rows here
    bool read_from_rows(
            std::string row
            );
    
};
#endif
