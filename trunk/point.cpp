#include "point.h"

namespace ScLe
{

bool
operator< (const Point &p1, const Point &p2)
{
    if (p1.y != p2.y)
        return p1.y < p2.y;
    else
        return p1.x < p2.x;
}

bool
operator<= (const Point& p1, const Point& p2)
{
    if ((p1.x == p2.x) && (p1.y == p2.y))
        return true;

    if (p1.y != p2.y)
        return p1.y < p2.y;
    else
        return p1.x < p2.x;
}

bool
operator== (const Point& p1, const Point &p2)
{
    return ((p1.x == p2.x) && (p1.y == p2.y));
}

Point&
operator+= (Point& p1, const Point& p2)
{
    p1.y += p2.y;
    p1.x += p2.x;

    return p1;
}

Point&
operator-= (Point& p1, const Point& p2)
{
    p1.y -= p2.y;
    p1.x -= p2.x;

    return p1;
}

}
