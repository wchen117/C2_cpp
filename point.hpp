#ifndef __POINT_HPP__
#define __POINT_HPP__
class Point
{
public:
    //python: self.x = None;
    int x;
    //python: self.y = None;
    int y;

    /**constructor and desctuctor**/
    Point();
    ~Point();

    bool read_from_vow(
            string row
            );
}

#endif
