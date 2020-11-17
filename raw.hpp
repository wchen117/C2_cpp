#ifndef __RAW_HPP__
#define __RAW_HPP__

#include <map>
#include <memory>
#include <string>
#include <vector>

class Raw
{

public:

    std::vector<std::string> rows_sections;
    std::string raw_input;
    /**constructor and destructor**/
    Raw();
    ~Raw();

    bool write(
            std::string file_name
            );

    void read(
            std::string file_name
            );
    std::string read_to_string(
            std::string file_name
            );

    bool row_is_file_end(
            int row
            );

    bool row_is_section_end(
            int row
            );

    // not sure type of rows here
    void read_from_rows();
    
    std::vector<std::string> lines_in_section(
            std::string section
            );
        
};
#endif
