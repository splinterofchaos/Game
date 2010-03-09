
// This file is basically ripped from:
// http://www.codeproject.com/KB/GDI-plus/PolygonCollision.aspx


// TODO: OK, 2D geometry collision is really difficult! Let's try just doing box collision.

#include "math/Vector.h"
#include "Rectangle.h"

#include <algorithm> // for max and min.
#include <cmath>     // for abs.

#pragma once

// TODO: Write this TODO statement.
struct Collision
{
    bool isOccuring; // True if this represents a collision that IS occurring.

    Rectangle<float> *victim1, *victim2;

    Vector<float,2> intersection; // Represents the intersection of vic1 to 2.

    Collision( Rectangle<float>* a1, Rectangle<float>* a2 )
        : victim1( a1 ), victim2( a2 )
    {
    }
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

    //              y1 = y2
    //     a_1*x + b_1 = a_2*x + b_2
    //   a_1*x - a_2*x = b_2 - b_1
    // x ( a_1 - a_2 ) = b_2 - b_1
    // x = ( b_2 - b_1 ) / ( a_1 - a_2 )
    T x = (b2 - b1) / (a1 - a2);

    // Assuming a collision, either line will have x within its range.
    return ( x > line1Start.x() && x < line1End.x() ) || 
           ( x < line1Start.x() && x > line1End.x() );
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

Collision rectangle_collision( Rectangle<float>& A, Rectangle<float>& B )
{
    Collision c( &A, &B );
    c.isOccuring = true;

    //The sides of the rectangles
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.s.x() - A.half_width();
    rightA = A.s.x() + A.half_width();
    topA = A.s.y() - A.half_length();
    bottomA = A.s.y() + A.half_length();
        
    //Calculate the sides of rect B
    leftB = B.s.x() - B.half_width();
    rightB = B.s.x() + B.half_width();
    topB = B.s.y() - B.half_length();
    bottomB = B.s.y() + B.half_length();
    
    if( bottomA <= topB )
        c.isOccuring = false;
    else if( topA >= bottomB )
        c.isOccuring = false;
    else // x axis intersects:
    {
        c.intersection.x( std::abs(rightB - leftA) );
    }

    if( rightA <= leftB )
        c.isOccuring = false;
    else if( leftA >= rightB )
        c.isOccuring = false;
    else
    {
        c.intersection.y( std::abs(topB - bottomA) );
    }
    
    return c;
}
