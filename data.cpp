#include "data.hpp"
#include "iostream"
#include <string>

// constructor
Data::Data() {
    Raw raw = new Raw();
    Con con = new Con();
    Sup sup = new Sup();
}

// destructor
Data::~Data() {
    ~Raw();
    ~Con();
    ~Sup();
}


bool Data::read(
    string raw_name,
    string sup_name,
    string con_name
                )
{
    raw.read(raw_name);
    sup.read(sup_name);
    con.read(con_anme);
    return true;
}

bool Data::write(
    string raw_name,
    string sup_name,
    string con_name
                 )
{
    raw.write(raw_name);
    sup.write(sup_name);
    con.write(con_name);
    return true;
    
}
bool Data::check()
{
    raw.check();
    sup.check();
    con.check();
    check_gen_implies_cost_gen();
    check_cost_gen_implies_gen();
    check_no_generators_in_con_not_in_raw();
    check_no_branches_in_con_not_in_raw();
    check_no_loads_in_sup_not_in_raw();
    check_no_loads_in_raw_not_in_sup();
    check_no_lines_in_sup_not_in_raw();
    check_no_lines_in_raw_not_in_sup();
    check_no_transformers_in_sup_not_in_raw();
    check_no_transformers_in_raw_not_in_sup();
    check_generator_base_case_ramp_constraints_feasible();
    check_load_base_case_ramp_constraints_feasible();
    check_connectedness(scrub_mode=False);
    return true;
}
bool Data::scrub()
{
    raw.scrub();
    remove_contingencies_with_generators_not_in_raw();
    remove_contingencies_with_branches_not_in_raw();
    remove_loads_in_sup_not_in_raw();
    remove_lines_in_sup_not_in_raw();
    remove_transformers_in_sup_not_in_raw();
    remove_generators_in_sup_not_in_raw();
    sup.check(scrub_mode=true);
    check_connectedness(scrub_mode=True);
    return true;
}
bool convert_to_offline()
{
    raw.set_operating_point_to_offline_solution();
    return true;
        
}

bool check_connectedness(
     scrub_mode=false
                         )
{
    
}

}
