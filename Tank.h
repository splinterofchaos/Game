
#include "Actor.h"

#include "glpp.h"

class Tank : public Actor
{
public:
    Tank( const vector_type& v, const value_type maxSpeed=999 )
        : Actor( v, maxSpeed )
    {
    }

    void draw()
    {
        using namespace glpp;

        translate( s.x(), s.y(), s.z() );

        color( 1,1,1,1 );
        glBegin( GL_QUADS );
            vertex( -10, -10 );
            vertex( -10,  10 );
            vertex(  10,  10 );
            vertex(  10, -10 );
        glEnd();
    }

    void move( int quantum )
    {
        
    }
};
