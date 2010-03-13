
#include "Actor.h" // For Graphable.

#include <vector>

#pragma once

class Terrain : virtual public Actor<float,2>, virtual public Rectangle<float> 
{
    typedef Actor<float,2> parent;

    value_type size_over_2;

public:
    typedef parent::vector_type vector_type;
    typedef parent::value_type  value_type;

    Terrain( const vector_type& pos, value_type size_over_2 )
        : parent( pos ), size_over_2( size_over_2 )
    {
        isSurface = true;
    }

    // This is just a stub, for now. 
    // TODO: How do i want terrains moving?
    void move( int quantum )
    {
    }

    void draw()
    {
        glpp::translate( s.x(), s.y(), 0 );

        glBegin( GL_POLYGON );
            draw_square( size_over_2 );
        glEnd();

        glLoadIdentity();
    }

    std::vector< vector_type > collision_nodes()
    {
        return std::vector<vector_type>(); // Obvious stub?
    }

    void collide( Collision c )
    {
        // Do nothing.
    }

    // Rectangle's functions:
    value_type half_length() const { return size_over_2; }
    value_type half_width() const { return size_over_2; }

};
