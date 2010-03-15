
#include "Actor.h" // For Graphable.
#include "Rectangle.h"
#include "Collision.h"

#pragma once

class Terrain : public Rectangle<float> 
{
    typedef Actor<float,2> parent;

    value_type size_over_2;

public:
    typedef parent::vector_type vector_type;
    typedef parent::value_type  value_type;

    Terrain( const vector_type& pos, value_type size_over_2 );

    void move( int quantum );

    void draw();

    void collide( Collision c );

    // Rectangle's functions:
    value_type half_length() const { return size_over_2; }
    value_type half_width() const { return size_over_2; }

};
