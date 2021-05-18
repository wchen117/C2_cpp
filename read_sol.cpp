#include <fstream>
#include <iostream>
#include <string>
#include <vector>
std::string read_to_string(std::string file_name)
{
    // read in case.raw file into a string
    std::ifstream input(file_name, std::ios::in | std::ios::binary);
    input.clear();
    if (input)
    {
     std::string container;
     input.seekg(0, std::ios::end);
     container.resize(input.tellg());
     input.seekg(0, std::ios::beg);
     input.read(&container[0], container.size());
     input.close();
     return container;

    }
     throw(errno);
}

std::vector<std::string> parse_on_delimiter(std::string const &input_string, std::string delimiter)
{
    std::vector<std::string> parsed_string_vector;
    std::size_t start = 0;
    std::size_t end = input_string.find(delimiter);

    while(end != std::string::npos)
    {
        parsed_string_vector.push_back(input_string.substr(start, end - start));
        start = end + delimiter.length();
        end = input_string.find(delimiter, start);
    }
    parsed_string_vector.push_back(input_string.substr(start, std::string::npos));

    return parsed_string_vector;

}
int main()
{
    struct generator {
        int i;
        int id;
        double p_gk;
        double q_gk;
        double x_gk_on;
        double x_gk_su;
        double x_gk_sd;
    };

    std::string additional_var = "additional_generator_varBASECASE.txt";

    std::string content = read_to_string(additional_var);
    std::vector<std::string> vector_string = parse_on_delimiter(content, "--");

    for (size_t idx=0; idx<vector_string.size(); idx++)
    {
        std::string const& section = vector_string.at(idx);
        std::vector<std::string> lines_vector = parse_on_delimiter(section, "\n");
        std::vector<std::shared_ptr<generator>> generator_ref_vec;
        if (lines_vector.at(0) == "generator section")
        {
            // first two lines not numbers, last line empty
            for (size_t jdx=2; jdx<lines_vector.size()-1; jdx++)
            {
                std::string const& line = lines_vector.at(jdx);
                std::vector<std::string> num_vec = parse_on_delimiter(line, ",");
                auto tmp_gen = std::make_shared<generator>();
                tmp_gen->i = std::stoi(num_vec.at(0));
                tmp_gen->id = std::stoi(num_vec.at(1));
                tmp_gen->p_gk = std::stod(num_vec.at(2));
                tmp_gen->q_gk = std::stod(num_vec.at(3));
                tmp_gen->x_gk_on = std::stod(num_vec.at(4));
                tmp_gen->x_gk_su = std::stod(num_vec.at(5));
                tmp_gen->x_gk_sd = std::stod(num_vec.at(6));
                generator_ref_vec.push_back(tmp_gen);

            }

        }



    }

}