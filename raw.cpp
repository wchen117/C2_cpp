#include "raw.hpp"

/**constructor and desctructor**/
Raw::Raw(){
    case_identification = CaseIdentification();
    num_loads_activate = 0;
}

Raw::~Raw(){}

bool Raw::scrub()
{
    scrub_buses();
    scrub_loads();
    scrub_fixed_shunts();
    scrub_nontransformer_branches();
    scrub_transformers();
    scrub_generators();
    scrub_switched_shunts();
    return true;
}

bool Raw::read()
{

}

bool Raw::read_from_rows(string rows)
{

}

