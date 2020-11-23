#ifndef __GENERATOROUTEVENT_HPP__
#define __GENERATOROUTEVENT_HPP__

class GeneratorOutEvent
{
public:
    // python: self.i = None, no default
    int i;
    // python: self.i = None, no default
    int id;

    bool check(
            );

    bool read_from_csv(
            );

    bool read_from_row(
            );

    bool construct_record_row(
            );

}
#endif
