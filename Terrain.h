
#include "Actor.h" // For Graphable.

#include <vector>

class Terrain : public Actor<float,2>
{
    typedef Actor<float,2> parrent;

    typedef parrent::vector_type vector_type;
    typedef parrent::value_type  value_type;

    // Represent the terrain as a list of nodes creating a polygon.
    typedef std::vector< vector_type > NodeList;
    NodeList nodes; 

    // TODO: Think of something more interesting than monotone terrains. ;p
    Vector< value_type, 4 > col; // The color of our terrain.

public:
    Terrain( const vector_type& pos )
        : parrent( pos )
    {

    }

    Terrain( const vector_type& pos, const std::vector< vector_type >& initNodes )
        : parrent( pos )
    {
        nodes = initNodes;
    }

    // Add a new node to the terrain.
    void push_back( const vector_type& v )
    {
        nodes.push_back( v );
    }

    // This is just a stub, for now. 
    // TODO: How do i want terrains moving?
    void move( int quantum )
    {
    }

    void draw()
    {
        // TODO: WHY THE HELL DO I NEED THIS parrent:: TO ACCESS s!?
        //       s IS A PUBLIC VARIABLE!!!
        glpp::translate( parrent::s.x(), parrent::s.y(), 0 );

        glBegin( GL_POLYGON );
            for( NodeList::iterator it=nodes.begin(); it != nodes.end(); it++ )
                glpp::vertex( it->data() );
        glEnd();

        glLoadIdentity();
    }

    std::vector< vector_type > collision_nodes()
    {
        std::vector< vector_type > cnodes;
        for( NodeList::iterator it=nodes.begin(); it != nodes.end(); it++ )
            cnodes.push_back( s + *it );
        return cnodes;
    }

    void collide()
    {
    }
};
