
#include "Rectangle.h"
#include "Collision.h"
#include "Terrain.h"

#pragma once

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

    Tank( const vector_type& v, const value_type maxSpeed=999 );

    void draw();

    void move( int quantum );

    void collide( Collision c );

    // Rectangle's functions:
    value_type half_width()  const { return WIDTH_OVER_2  * scale; }
    value_type half_length() const { return LENGTH_OVER_2 * scale; }


    void move_left( bool start );
    void move_right( bool start );
    void jump();
};
