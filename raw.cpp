#include "raw.hpp"
#include<fstream>
#include<string>
#include<cerrno>

/**constructor and desctructor**/
Raw::Raw(){}

Raw::~Raw(){}

std::string Raw::read(std::string file_name)
{
    std::ifstream input(file_name, std::ios::in | std::ios::binary);
    input.clear();
    if (input)  
    {
        std::string contents;
        input.seekg(0, std::ios::end);
        contents.resize(input.tellg());
        input.seekg(0, std::ios::beg);
        input.read(&contents[0], contents.size());
        input.close();
        return contents;
    
    }
    throw(errno);
}

bool Raw::read_from_rows(std::string rows)
{
    return true;
}

