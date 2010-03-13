
#include <SDL/SDL_keyboard.h> // For SDL_GetKeyState().

struct Controller
{
    virtual void do_input() = 0;
    virtual bool check_input() = 0;

    virtual void update()
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

template< typename P, typename F >
struct BasicControllerButton : public Controller
{
    typedef P      Pointer;
    typedef size_t size_type;

    size_type key;
    Pointer target;
    F f;

    BasicControllerButton( size_type key, Pointer target, F f )
        : key( key ), target( target ), f( f )
    {
    }
};

template< typename P, typename F > 
class PressedButton : public BasicControllerButton< P, F >
{
    typedef BasicControllerButton< P, F > parent;

    // TODO: For whatever reason, i can't get the typedefs from parent to
    // inherit properly. Maybe this is a g++ problem, maybe my code.

    bool isPressed;

public:
    PressedButton( size_t key, P target, F f )
        : parent( key, target, f ), isPressed( false )
    {
    }

    bool check_input()
    {
        // Consider revising to meet 1-exit-point principle, or keep it?
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

template< typename P, typename F > 
class SimpleButton : public BasicControllerButton< P, F >
{
    typedef BasicControllerButton< P, F > parent;

public:
    SimpleButton( size_t key, P target, F f )
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

template< typename P, typename F >
PressedButton<P,F>* new_pressed_button( size_t key, P target, F f )
{
    return new PressedButton<P,F>( key, target, f );
}

template< typename P, typename F >
SimpleButton<P,F>* new_simple_button( size_t key, P target, F f )
{
    return new SimpleButton<P,F>( key, target, f );
}
