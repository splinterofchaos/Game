
#include "Terrain.h"

Terrain::Terrain( const vector_type& pos, value_type size_over_2 )
    : parent( pos ), size_over_2( size_over_2 )
{
    isSurface = true;
}

// This is just a stub, for now. 
// TODO: How do i want terrains moving?
void Terrain::move( int quantum )
{
}

void Terrain::draw()
{
    glpp::translate( s.x(), s.y(), 0 );

    glBegin( GL_POLYGON );
        draw_square( size_over_2 );
    glEnd();

    glLoadIdentity();
}

void Terrain::collide( Collision c )
{
    // Do nothing.
}
