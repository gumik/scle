#ifndef _SC_LE_POINT_H_
#define _SC_LE_POINT_H_

namespace ScLe
{

// Punkt o wspolrzednych calkowitych
struct Point
{
    Point (int _y = 0, int _x = 0) : x(_x), y(_y) {}
    int x, y;

    friend bool operator< (const Point&, const Point&);
    friend bool operator<= (const Point&, const Point&);
    friend bool operator== (const Point& p1, const Point &p2);
    friend Point& operator+= (Point&, const Point&);
    friend Point& operator-= (Point&, const Point&);
};

}

#endif /* _SC_LE_POINT_H_ */
