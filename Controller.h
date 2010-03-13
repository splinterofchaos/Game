
#include <SDL/SDL_keyboard.h> // For SDL_GetKeyState().

struct Controller
{
    virtual void do_input() = 0;
    virtual bool check_input() = 0;

    void update()
    {
        if( check_input() )
            do_input();
    }
};

struct Keyboard
{
    static Uint8* keyState;

    static void refresh()
    {
        keyState = SDL_GetKeyState( 0 );
    }
};
Uint8* Keyboard::keyState = 0;

template< typename T, typename F >
struct BasicControllerButton : public Controller
{
    size_t key;
    T& target;
    F  f;

    BasicControllerButton( size_t key, T& target, F f )
        : key( key ), target( target ), f( f )
    {
    }
};

template< typename T, typename F > 
class PressedButton : public BasicControllerButton< T, F >
{
    typedef BasicControllerButton< T, F > parent;

    // TODO: For whatever reason, i can't get the typedefs from parent to
    // inherit properly. Maybe this is a g++ problem, maybe my code.

    bool isPressed;

public:
    PressedButton( size_t key, T& target, F f )
        : parent( key, target, f ), isPressed( false )
    {
    }

    bool check_input()
    {
        if( isPressed != Keyboard::keyState[ parent::key ] ) {
            isPressed = ! isPressed;
            return true;
        }

        return false;
    }

    void do_input()
    {
        parent::f( parent::target, isPressed );
    }
};

template< typename T, typename F > 
class SimpleButton : public BasicControllerButton< T, F >
{
    typedef BasicControllerButton< T, F > parent;

public:
    SimpleButton( size_t key, T& target, F f )
        : parent( key, target, f )
    {
    }

    bool check_input()
    {
        return Keyboard::keyState[ parent::key ];
    }

    void do_input()
    {
        parent::f( parent::target );
    }
};

// Helper functions. Honestly, i wonder if there's a better way.
template< typename T, typename F >
PressedButton<T,F>* new_pressed_button( size_t key, T& target, F f )
{
    return new PressedButton<T,F>( key, target, f );
}

template< typename T, typename F >
SimpleButton<T,F>* new_simple_button( size_t key, T& target, F f )
{
    return new SimpleButton<T,F>( key, target, f );
}
