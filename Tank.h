
#include "Rectangle.h"
#include "Terrain.h"
#include "glpp.h"

#include <cmath> // for abs.

class Tank : virtual public Actor<float,2>, virtual public Rectangle<float>
{
public:
    // Rectangle is not recognized as a parent because it isn't, functionally.
    typedef Actor<float,2> parent; 

    static const value_type WIDTH_OVER_2 = 0.5, LENGTH_OVER_2 = 0.25; 
    static const value_type SPEED = 0.11;
    static const value_type JUMP_SPEED = -0.11;
    static const value_type TOUCHING_RANGE = 0.001;


    // Needed to avoid odd error caught by g++ when -SPEED used.
    //  "[references to where -SPEED is used]: undefined reference to `Tank::SPEED'"
    static const value_type NSPEED = -0.11; // Negative SPEED.

    Terrain* surface;
    
    typedef parent::vector_type vector_type;
    typedef parent::value_type  value_type;

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

    void move_along_x( bool start, value_type speed )
    {
        if( start )
            v.x( v.x() + speed );
        else
            v.x( v.x() - speed );
    }

    void move( int quantum )
    {
        if( surface ) {
            if( surface->s.x()+surface->half_width() < s.x() - half_width() ||
                surface->s.x()-surface->half_width() > s.x() + half_width() )
                surface = 0;
            else if( (surface->s.y()-s.y())-(surface->half_length()+half_length()) > TOUCHING_RANGE )
                surface = 0;
        }
             
        if( ! surface )
            a.y( value_type(0.0001) ); // Gravity.

        parent::move( quantum );
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

    // Rectangle's functions:
    value_type half_width()  const { return WIDTH_OVER_2  * scale; }
    value_type half_length() const { return LENGTH_OVER_2 * scale; }
};

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
