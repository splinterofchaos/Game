
#include "Rectangle.h"
#include "Terrain.h"
#include "glpp.h"

#include <cmath> // for abs.

class Tank : virtual public Actor<float,2>, virtual public Rectangle<float>
{
    // Rectangle is not recognized as a parent because it isn't, functionally.
    typedef Actor<float,2> parent; 

    static const value_type WIDTH_OVER_2 = 0.5, LENGTH_OVER_2 = 0.25; 
    static const value_type SPEED = 0.11;
    static const value_type JUMP_SPEED = -0.11;

    // Needed to avoid odd error caught by g++ when -SPEED used.
    //  "[references to where -SPEED is used]: undefined reference to `Tank::SPEED'"
    static const value_type NSPEED = -0.11; // Negative SPEED.

    Terrain* surface;
    
public:
    typedef parent::vector_type vector_type;
    typedef parent::value_type value_type;

    Tank( const vector_type& v, const value_type maxSpeed=999 )
        : parent( v, maxSpeed ), surface( 0 )
    {
        scale = value_type( 20 );
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

    void move_left( bool flip )
    {
        if( flip )
            v.x( v.x() + NSPEED );
        else
            v.x( v.x() +  SPEED );
    }

    void move( int quantum )
    {
        const float TOUCHING_RANGE = 0.001;

        if( surface ) {
            if( surface->s.x()+surface->half_width() < s.x() - half_width() ||
                surface->s.x()-surface->half_width() > s.x() + half_width() )
                surface = 0;
            else if( (surface->s.y()-s.y())-(surface->half_length()+half_length()) > TOUCHING_RANGE )
                surface = 0;
        }
             
        Uint8* keyState = SDL_GetKeyState( 0 );
        if( keyState[ SDLK_a ] )
            v.x( v.x() + NSPEED );
        if( keyState[ SDLK_d ] )
            v.x( v.x() +  SPEED );

        if( surface ) {
            if( keyState[ SDLK_w ] ) {
                v.y( v.y() + JUMP_SPEED );
                s.y( s.y() - TOUCHING_RANGE );
                surface = 0;
            }
        } else {
            a.y( value_type(0.0001) ); // Gravity.
        }

        parent::move( quantum );

        // Erase the user inputs from v. This lets us keep momentum without
        // the user altering it. 
        if( keyState[ SDLK_a ] )
            v.x( v.x() +  SPEED );
        if( keyState[ SDLK_d ] )
            v.x( v.x() + NSPEED );

         //if( surface && keyState[ SDLK_w ] )
         //    v.y( v.y() - JUMP_SPEED );
    }

    std::vector< vector_type > collision_nodes()
    {
        std::vector< vector_type > nodes;
        vector_type tmp;

        float w_over_2 = WIDTH_OVER_2 * scale;
        float l_over_2 = LENGTH_OVER_2 * scale;

        tmp.x( WIDTH_OVER_2*scale ); tmp.y( LENGTH_OVER_2*scale );
        nodes.push_back( tmp + s );

        tmp.x( -w_over_2 ); tmp.y( LENGTH_OVER_2*scale );
        nodes.push_back( tmp + s );

        tmp.x( -w_over_2 ); tmp.y( -l_over_2 );
        nodes.push_back( tmp + s );

        tmp.x( WIDTH_OVER_2*scale ); tmp.y( -l_over_2 );
        nodes.push_back( tmp + s );

        return nodes;
    }

    void collide( Collision c )
    {
        Rectangle<float>* other;
        if( c.victim1 == this )
            other = c.victim2;
        else
            other = c.victim1;

        // TODO: Not use reinterpret_cast?
        if( other->isSurface )
            surface = reinterpret_cast<Terrain*>( other );

        if( c.intersection.y() < half_length() )
        {
            if( previousS.y() < other->s.y() ) {
                s.y( s.y() - c.intersection.y() );
                v.y( 0 );
            } else if( previousS.y() > other->s.y() ) {
                s.y( s.y() + c.intersection.y() );
                v.y( 0 );
            }
        }
        if( c.intersection.x() < half_width() )
        {
            if( previousS.x() < other->s.x() ) {
                s.x( s.x() - c.intersection.x() );
                v.x( 0 );
            } else if( previousS.x() > other->s.x() ) {
                s.x( s.x() + c.intersection.x() );
                v.x( 0 );
            }
        }
    }

    // Rectangle's functions:
    value_type half_width()  const { return WIDTH_OVER_2  * scale; }
    value_type half_length() const { return LENGTH_OVER_2 * scale; }
};

