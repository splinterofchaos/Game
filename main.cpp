
#include "math/Vector.h"
#include "ScopeGuard.h"
#include "Tank.h"
#include "Terrain.h"
#include "Collision.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

// include shared ptr.
#if defined( __GNUC__ )
    // tr1/memory is required to include tr1/shared_ptr.h... Dunno why.
    #include <tr1/memory> 
    #include <tr1/shared_ptr.h>
#elif defined( __MSVC__ )
    #error "Insert whatever you have to to use shared_ptr here!"
#endif

#include <algorithm> // For for_each().
#include <functional> // For mem_fun_ptr.

GLenum init_gl( int w, int h )
{
    glClearColor( 1.0f, 0.0f, 1.0f, 1.0f );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, w, h, 0, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    return glGetError();
}

bool make_sdl_gl_window( int w, int h )
{
    if( ! SDL_SetVideoMode(w, h, 32, SDL_OPENGL) )
        return false;
    init_gl( w, h );
    return true;
}

void update_screen()
{
    SDL_GL_SwapBuffers();
    glClear( GL_COLOR_BUFFER_BIT );
}

// Like for_each, but acknowledging containers using pointers that need to be
// dereferenced before calling f. I thought of making a Dereference object to
// be super generic...but this is MUCH less work.
template< typename Iterator, typename F >
void for_each_ptr( Iterator begin, Iterator end, F f )
{
    for( ; begin != end; begin++ )
        f( **begin );
}

#include <iostream>

int main()
{
    // Portably suppresses unused variable compiler warnings.
    #define NOT_USED(var) ((void)(var))

    const int MAX_FRAME_TIME = 10;

    bool quit = false;

    typedef std::tr1::shared_ptr< Actor<float,2> > SmartPointer;
    typedef std::vector< SmartPointer > ActorList;
    ActorList list;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        return 1;
    make_sdl_gl_window( 1200, 800 );
    ScopeGuard quitSdl = scope_guard( SDL_Quit ); NOT_USED( quitSdl ); 

    Vector<int,2> v; v.x(20); v.y(20);
    list.push_back( SmartPointer( new Tank(v) ) );

    v.x(0); v.y(800);
    Terrain* tmp = new Terrain( v );
    v.x(   0 ); v.y(    0 ); tmp->push_back( v );
    v.x(   0 ); v.y( -100 ); tmp->push_back( v );
    v.x( 200 ); v.y( -200 ); tmp->push_back( v );
    v.x( 500 ); v.y( -150 ); tmp->push_back( v );
    v.x( 500 ); v.y(    0 ); tmp->push_back( v );
    list.push_back( SmartPointer(tmp) );

    SDL_Event event;

    int frameStart=SDL_GetTicks(), frameEnd=frameStart, frameTime=0;
    while( quit == false )
    {
		while( SDL_PollEvent( &event ) )
		{
			if( event.type == SDL_QUIT )
                quit = true;
		}

        Uint8* keyState = SDL_GetKeyState( 0 );
        if( keyState[SDLK_ESCAPE] )
            quit = true;

        // TODO: Fixed time-step. 
        for_each_ptr ( 
            list.begin(), list.end(), 
            std::bind2nd( std::mem_fun_ref( &Actor<float,2>::move ), frameTime )
        );

        for_each_ptr ( 
            list.begin(), list.end(), 
            std::mem_fun_ref( &Actor<float,2>::draw ) 
        );

        ActorList::iterator it1=list.begin(), it2;
        for( ; it1 != list.end(); it1++ )
        {
            for( it2 = it1; it2 != list.end(); it2++ )
            {
                if( collision( (**it1).collision_nodes(), (**it2).collision_nodes() ) )
                    std::cout << "HAHAHAHA!";
            }
        }

        update_screen();

        frameStart = frameEnd;
        frameEnd = SDL_GetTicks();
        frameTime = frameEnd - frameStart;
        if( frameTime > MAX_FRAME_TIME )
            frameTime = MAX_FRAME_TIME;
    }
}
