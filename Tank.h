
#include "Actor.h"

#include "glpp.h"

class Tank : public Actor<float,2>
{
    typedef Actor<float,2> parrent;


    static const value_type WIDTH_OVER_2 = 0.5, LENGTH_OVER_2 = 0.25; 
    static const value_type SPEED = 0.11;

    // Needed to avoid odd error caught by g++ when -SPEED used.
    //  "[references to where -SPEED is used]: undefined reference to `Tank::SPEED'"
    static const value_type NSPEED = -0.11; // Negative SPEED.

public:
    typedef parrent::vector_type vector_type;
    typedef parrent::value_type value_type;

    Tank( const vector_type& v, const value_type maxSpeed=999 )
        : parrent( v, maxSpeed )
    {
        scale = value_type(20);
    }

    void draw()
    {
        using namespace glpp;

        translate( s.x(), s.y(), s.z() );

        color( 0,1,0,1 );
        glBegin( GL_QUADS );
            draw_rectangle( WIDTH_OVER_2*scale, LENGTH_OVER_2*scale );
        glEnd();

        glLoadIdentity();
    }

    void move( int quantum )
    {
        std::fill( a.begin(), a.end(), 0 );

        a.y( value_type(0.001) ); // Gravity.

        Uint8* keyState = SDL_GetKeyState( 0 );
        if( keyState[ SDLK_w ] )
            v.y( v.y() + NSPEED );
        if( keyState[ SDLK_s ] )
            v.y( v.y() +  SPEED );
        if( keyState[ SDLK_a ] )
            v.x( v.x() + NSPEED );
        if( keyState[ SDLK_d ] )
            v.x( v.x() +  SPEED );

        parrent::move( quantum );

        // Erase the user inputs from v. This lets us keep momentum without
        // the user altering it. 
        if( keyState[ SDLK_w ] )
            v.y( v.y() +  SPEED );
        if( keyState[ SDLK_s ] )
            v.y( v.y() + NSPEED );
        if( keyState[ SDLK_a ] )
            v.x( v.x() +  SPEED );
        if( keyState[ SDLK_d ] )
            v.x( v.x() + NSPEED );
    }
};

