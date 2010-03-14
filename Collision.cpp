
#include "Collision.h"

Collision rectangle_collision( Rectangle<float>& A, Rectangle<float>& B )
{
    Collision c( &A, &B );
    c.isOccuring = true;

    //Calculate the sides of rect A
    float leftA = A.s.x() - A.half_width();
    float rightA = A.s.x() + A.half_width();
    float topA = A.s.y() - A.half_length();
    float bottomA = A.s.y() + A.half_length();
        
    //Calculate the sides of rect B
    float leftB = B.s.x() - B.half_width();
    float rightB = B.s.x() + B.half_width();
    float topB = B.s.y() - B.half_length();
    float bottomB = B.s.y() + B.half_length();
    
    if( bottomA <= topB )
        c.isOccuring = false;
    else if( topA >= bottomB )
        c.isOccuring = false;
    else // y axis intersects:
        if( A.s.y() < B.s.y() )
            c.intersection.y( std::abs(topB - bottomA) );
        else 
            c.intersection.y( std::abs(topA - bottomB) );

    if( rightA <= leftB )
        c.isOccuring = false;
    else if( leftA >= rightB )
        c.isOccuring = false;
    else // x axis intersects:
        if( A.s.x() < B.s.x() )
            c.intersection.x( std::abs(rightA - leftB) );
        else
            c.intersection.x( std::abs(leftA - rightB) );
    
    return c;
}
