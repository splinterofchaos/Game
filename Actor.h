
#include "math/Vector.h"
#include "glpp.h"
#include "draw_shape.h"

#include <GL/gl.h>
#include <SDL/SDL.h>
#include <algorithm>
#include <vector>

#pragma once

struct Collision; // Prototype; defined elsewhere.

// A subclass for any object that can be graphed. It provides some
// genericy in typedefs, but not functionality or data.
template< typename T=float, unsigned int N_DIMENTIONS=3 >
struct Graphable
{
    static const int DIMENTIONS = N_DIMENTIONS;

    typedef Vector<T,N_DIMENTIONS> vector_type;
    typedef T                      value_type;
};

// Any object that can be drawn, moved, and graphed can use Actor as its base.
// It does not determine how its derivative is drawn, moved, or graphed.
template< typename T=float, size_t N_DIMENTIONS=3 >
class Actor : public Graphable<T,N_DIMENTIONS>
{
    typedef Graphable< T, N_DIMENTIONS > parrent;

    void init()
    {
        std::fill( v.begin(), v.end(), 0 );
        std::fill( a.begin(), a.end(), 0 );
    }
   
protected:
    Actor()
    {
    }

public:
    typedef typename parrent::vector_type vector_type;
    typedef typename parrent::value_type  value_type;

    // Single-letter vars used in order to be close to the mathematical 
    // equations.
    vector_type s; // State, or position.
    vector_type v; // Velocity.
    vector_type a; // Acceleration.

    vector_type previousS;

    value_type maxSpeed;

    value_type scale; // At what magnification to draw the Actor.

    bool isSurface;

    Actor( const vector_type& pos, const value_type maxSpeed=999 )
        : s(pos), previousS(s), maxSpeed(maxSpeed), scale( 1 )
    {
        init();
    }

    // This class does not care whether its derivatives draw with vectors,
    // bitmaps, or what-have-you.
    virtual void draw() = 0;

    // This class does not care about how the object is moved, but does set
    // up a simple, generic state integration.
    virtual void move( int quantum )
    {
        previousS = s;

        value_type speed = magnitude( v );
        if( false )
        {
            value_type k = maxSpeed / speed;
            v *= k;
        }

        v += a * quantum;
        s += v * quantum;
    }

    // Whether all Actors should have collision is undecided.
    virtual void collide( Collision c ) = 0;

    virtual ~Actor()
    {
    }
};

