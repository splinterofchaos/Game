
#include "Actor.h"

#include "glpp.h"

class Tank : public Actor
{
    static const value_type WIDTH_OVER_2 = 0.5, LENGTH_OVER_2 = 0.25; 
    static const value_type SPEED = 0.01;

    // Needed to avoid odd error caught by g++ when -SPEED used.
    //  "[references to where -SPEED is used]: undefined reference to `Tank::SPEED'"
    static const value_type NSPEED = -0.01; // Negative SPEED.

public:
    Tank( const vector_type& v, const value_type maxSpeed=999 )
        : Actor( v, maxSpeed )
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
        std::fill( v.begin(), v.end(), 0 );

        Uint8* keyState = SDL_GetKeyState( 0 );
        if( keyState[ SDLK_w ] )
            v.y( NSPEED );
        if( keyState[ SDLK_s ] )
            v.y(  SPEED );
        if( keyState[ SDLK_a ] )
            v.x( NSPEED );
        if( keyState[ SDLK_d ] )
            v.x(  SPEED );

        Actor::move( quantum );
    }
};
