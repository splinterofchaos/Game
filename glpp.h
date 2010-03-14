
#pragma once

#include <GL/gl.h>

namespace glpp
{

#define COLOR_FUNC4( type, t ) \
    void color( GL##type r, GL##type g, GL##type, GL##type b, \
                GL##type a = GL##type(1) ); 
COLOR_FUNC4( short,  s );
COLOR_FUNC4( int,    i );
COLOR_FUNC4( float,  f );
COLOR_FUNC4( double, d );
#undef COLOR_FUNC4

void translate( GLfloat  x, GLfloat  y, GLfloat  z );
void translate( GLdouble x, GLdouble y, GLdouble z );

#define VERTEX_FUNC2( type, t ) \
    void vertex( GL##type x, GL##type y );
VERTEX_FUNC2( float, f );
#undef VERTEX_FUNC2

#define VERTEX_FUNC3( type, t ) \
    void vertex( GL##type x, GL##type y, GL##type z );
VERTEX_FUNC3( float, f );
#undef VERTEX_FUNC3

void vertex( GLfloat x, GLfloat y, GLfloat z, GLfloat w );

#define VERTEX_FUNCV( type, t, N ) \
    void vertex( GL##type (&v)[N] );
VERTEX_FUNCV( float, f, 2 );
VERTEX_FUNCV( float, f, 3 );
VERTEX_FUNCV( float, f, 4 );
#undef VERTEX_FUNCV

} // namespace glpp
