#include <vector>
#include <string>

#include "branchoutevent.hpp"
#include "generatoroutevent.hpp"

class Contingency
{

public:
    string label;
    vector<BranchOutEvent> branch_out_events;
    vector<GeneratorOutEvent> generator_out_events;

    /**constructor and desctructor**/
    Contingency();
    ~Contingency();

    bool check(
            );

    bool clean_label(
            );

    bool check_branch_out_events(
            );

    bool check_generator_out_events(
            );

    bool check_at_most_one_branch_out_event(
            );

    bool check_at_most_one_generator_out_event(
            );

    bool check_at_most_one_branch_or_generator_out_event(
            );

    bool check_at_least_one_branch_or_generator_out_event(
            );

    bool construct_record_rows(
            );

}
