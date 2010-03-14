
// This file is basically ripped from:
// http://www.codeproject.com/KB/GDI-plus/PolygonCollision.aspx


// TODO: OK, 2D geometry collision is really difficult! Let's try just doing box collision.

#include "math/Vector.h"
#include "Rectangle.h"

#include <algorithm> // for max and min.
#include <cmath>     // for abs.

#pragma once

// TODO: Write this TODO statement.
struct Collision
{
    bool isOccuring; // True if this represents a collision that IS occurring.

    Rectangle<float> *victim1, *victim2;

    Vector<float,2> intersection; // Represents the intersection of vic1 and 2.

    Collision( Rectangle<float>* a1, Rectangle<float>* a2 )
        : victim1( a1 ), victim2( a2 )
    {
    }
};

Collision rectangle_collision( Rectangle<float>& A, Rectangle<float>& B );
