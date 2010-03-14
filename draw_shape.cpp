
#include "draw_shape.h"

#include "glpp.h"
#include "math/Vector.h"
#include <cmath>

void draw_square( float size_over_2 )
{
    using namespace glpp;
    vertex( -size_over_2, -size_over_2 );
    vertex(  size_over_2, -size_over_2 );
    vertex(  size_over_2,  size_over_2 );
    vertex( -size_over_2,  size_over_2 );
}

void draw_rectangle( float w_over_2, float l_over_2 )
{
    using namespace glpp;
    vertex( -w_over_2, -l_over_2 );
    vertex(  w_over_2, -l_over_2 );
    vertex(  w_over_2,  l_over_2 );
    vertex( -w_over_2,  l_over_2 );
}

// Technique borrowed from http://slabode.exofire.net/circle_draw.shtml
void draw_circle( float radius, unsigned int vertecies )
{
    const float ROTATION = (2 * 3.145) / vertecies; // Change in theta.
    const float TANGENTAL_FACTOR = std::tan( ROTATION );
    const float RADIAL_FACTOR    = std::cos( ROTATION );

    Vector<float,2> rv; // Radial vector.
    rv.x( radius ); rv.y( 0.0f );

    // In the article, this is done at the beginning of the loop, then the next
    // radial vector is calculated, but that means on the last iteration, said
    // vector is calculated in vein. 
    glpp::vertex( rv.data() );

    for( unsigned int i=1; i < vertecies; i++ )
    {
        Vector<float,2> tv; // Tangential vector.
        tv.x( -rv.y() ); tv.y( rv.x() );

        rv += tv * TANGENTAL_FACTOR;
        rv *= RADIAL_FACTOR;

        glpp::vertex( rv.data() );
    }
}

// Mainly, same approach as above, but with two circles.
void draw_loop( float radInner, float radOuter, unsigned int vertecies )
{
    const float ROTATION = 2 * 3.145 / vertecies;
    const float TANGENTAL_FACTOR = std::tan( ROTATION );
    const float RADIAL_FACTOR    = std::cos( ROTATION );

    Vector<float,2> rvi; // Inner radial vector.
    Vector<float,2> rvo; // Outer radial vector.

    rvi.x( radInner ); rvi.y( 0.0f );
    rvo.x( radOuter ); rvi.y( 0.0f );

    glpp::vertex( rvo.data() );
    glpp::vertex( rvi.data() );

    for( unsigned int i=0; i < vertecies; i++ )
    {
        Vector<float,2> tvi; 
        tvi.x( -rvi.y() ); tvi.y( rvi.x() );

        Vector<float,2> tvo; 
        tvo.x( -rvo.y() ); tvo.y( rvo.x() );

        rvi += tvi * TANGENTAL_FACTOR;
        rvi *= RADIAL_FACTOR;

        rvo += tvo * TANGENTAL_FACTOR;
        rvo *= RADIAL_FACTOR;

        glpp::vertex( rvo.data() );
        glpp::vertex( rvi.data() );
    }
}
