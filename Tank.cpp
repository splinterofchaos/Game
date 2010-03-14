
#include "Tank.h"

#include "glpp.h"

#include <cmath> // for abs.

Tank::Tank( const vector_type& v, const value_type maxSpeed )
    : parent( v, maxSpeed ), surface( 0 ) 
{
    scale = value_type( 20 );
} 

void Tank::draw()
{
    using namespace glpp;

    translate( s.x(), s.y(), s.z() );

    color( 0,1,0,1 );
    glBegin( GL_QUADS );
        draw_rectangle( WIDTH_OVER_2*scale, LENGTH_OVER_2*scale );
    glEnd();

    glLoadIdentity();
}

void Tank::move( int quantum )
{
    if( surface ) {
        if( surface->s.x()+surface->half_width() < s.x() - half_width() ||
            surface->s.x()-surface->half_width() > s.x() + half_width() )
            surface = 0;
        else if( (surface->s.y()-s.y()) - 
                 (surface->half_length()+half_length()) > 
                 TOUCHING_RANGE )
            surface = 0;
    }
         
    if( ! surface )
        a.y( value_type(0.0001) ); // Gravity.

    parent::move( quantum );
}

void Tank::collide( Collision c )
{
    Rectangle<float>* other;
    if( c.victim1 == this )
        other = c.victim2;
    else
        other = c.victim1;

    if( c.intersection.y() < half_length() )
    {
        if( previousS.y() < other->s.y() ) {
            s.y( s.y() - c.intersection.y() );
            v.y( 0 );
            
            // TODO: Not use reinterpret_cast?
            if( other->isSurface )
                surface = reinterpret_cast<Terrain*>( other );
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

void move_left( Tank& tank, bool start )
{
    if( start )
        tank.v.x( tank.v.x() + Tank::NSPEED );
    else
        tank.v.x( tank.v.x() + Tank:: SPEED );
}

void move_right( Tank& tank, bool start )
{
    if( start )
        tank.v.x( tank.v.x() + Tank:: SPEED );
    else
        tank.v.x( tank.v.x() + Tank::NSPEED );
}

void jump( Tank& tank )
{
    if( tank.surface ) {
        tank.v.y( tank.v.y() + Tank::JUMP_SPEED );
        tank.s.y( tank.s.y() - Tank::TOUCHING_RANGE );
        tank.surface = 0;
    }
}
