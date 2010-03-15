
#include "Actor.h"
#include "math/Vector.h"

#pragma once

// Rectangle extends Actor's interface to include two functions. That's all.
template< typename T=float >
struct Rectangle : public Actor<T,2>
{
    virtual T half_width() const = 0;
    virtual T half_length() const = 0;
};
