
#include "Actor.h"
#include "math/Vector.h"

#pragma once

// Rectangle extends Actor's interface to include two functions. That's all.
template< typename T=float >
struct Rectangle : public Actor<T,2>
{
    typedef Actor<T,2> parent;

    // I'm not sure why these typedefs are necessary. Rectangle inherits them
    // through a template, so it needs to know value_type and vector_type are
    // tyoenames?
    typedef typename parent::vector_type vector_type;
    typedef typename parent::value_type  value_type;

    Rectangle( const vector_type& pos, const value_type maxSpeed=999 )
        : parent( pos, maxSpeed )
    {
    }

    virtual T half_width() const = 0;
    virtual T half_length() const = 0;
};
