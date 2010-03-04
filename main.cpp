
#include "math/Vector.h"
#include "ScopeGuard.h"
#include "Tank.h"

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

GLenum init_gl( int w, int h )
{
    glClearColor( 1.0f, 1.0f, 0.0f, 0.0f );

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

#include <iostream>

int main()
{
    // Portably suppresses unused variable compiler warnings.
    #define NOT_USED(var) ((void)(var))

    const int MAX_FRAME_TIME = 1000;

    bool quit = false;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        return 1;
    ScopeGuard quitSdl = scope_guard( SDL_Quit ); 
    NOT_USED( quitSdl ); 
    make_sdl_gl_window( 1200, 900 );

    Vector<int,3> v; 
    std::fill( v.begin(), v.end(), 0 );
    Tank tank(v);

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

        glClear( GL_COLOR_BUFFER_BIT );

        tank.move( frameTime );
        tank.draw();

        SDL_GL_SwapBuffers();

        frameStart = frameEnd;
        frameEnd = SDL_GetTicks();
        frameTime = frameEnd - frameStart;
        if( frameTime > MAX_FRAME_TIME )
            frameTime = MAX_FRAME_TIME;
    }
}
