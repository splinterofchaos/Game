
// This file is basically ripped from:
// http://www.codeproject.com/KB/GDI-plus/PolygonCollision.aspx


// TODO: OK, 2D geometry collision is really difficult! Let's try just doing box collision.

#include "math/Vector.h"
#include <algorithm> // for max and min.

// TODO: Write this TODO statement.
struct Collision
{
};

template< typename VectorT >
bool line_line_collision( VectorT line1Start, VectorT line1End,
                          VectorT line2Start, VectorT line2End )
{
    typedef typename VectorT::value_type T;

    // I can only write this function using my algebra exp.
    // y = ax + b;

    VectorT tmp = line1End - line1Start;
    T a1 = tmp.y() / tmp.x();
    T b1 = line1Start.y();

    tmp = line2End - line2Start;
    T a2 = tmp.y() / tmp.x();
    T b2 = line2Start.y();

    // a_1*x + b_1 = a_2*x + b_2
    // a_1*x - a_2*x = b_2 - b_1
    // x ( a_1 - a_2 ) = b_2 - b_1
    // x = (b_2-b_1) / (a_1-a_2)
    T x = (b2 - b1) / (a1 - a2);

    // Assuming a collision, either line will have x within its range.
    if( x > line1Start.x() && x < line1End.x() )
        return true;
    if( x < line1Start.x() && x > line1End.x() )
        return true;
    return false;
}

template< typename NodeList >
bool collision( NodeList a, NodeList b )
{
    typedef typename NodeList::iterator I;
    for( I it1 = a.begin(); it1 != a.end()-1; it1++ )
        for( I it2 = b.begin(); it2 != b.end()-1; it2++ )
            if( line_line_collision( *it1, *(it1+1), *it2, *(it2+1) ) )
                return true;
    return false;
}

template< typename VectorT, typename VecList >
void project_polygon( VectorT axis, VecList list )
{

}
