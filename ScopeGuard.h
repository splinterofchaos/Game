
// Based, err, ripped from ScopeGaurd (http://www.drdobbs.com/cpp/184403758).
// Scope guards provide not-quite-RAII for c-style resources.
// Usage: init_resource(); ScopeGuard guard = scope_guard( destroy_resource );

// CHANGE LIST:
//      Code conventions, naming, etc.
//      The line F _f would not compile (invalidly declared function type)
//          until a reference operator was added.
//      TODO: C++0x would eradicate the need for a Impl1, Impl2, etc.

class ScopeGuardImplBase
{
    // Disable assignment
    // TODO: For c++0x, use =delete.
    ScopeGuardImplBase& operator=( const ScopeGuardImplBase& );

public:
    void Dismiss() const throw()
    {
        dismissed_ = true;
    }

protected:
    ScopeGuardImplBase() 
        : dismissed_( false )
    {
    }

    ScopeGuardImplBase( const ScopeGuardImplBase& other )
        : dismissed_( other.dismissed_ )
    {    
        other.Dismiss(); 
    }

    ~ScopeGuardImplBase()
    {
    }

    mutable bool dismissed_;
};

typedef const ScopeGuardImplBase& ScopeGuard;

template <typename F, typename Arg>
class ScopeGuardImpl1 : public ScopeGuardImplBase
{
    F& f_;
    const Arg arg_;

public:
    ScopeGuardImpl1( const F& f, const Arg& arg )
    : f_(f), arg_(arg) 
    {
    }

    ~ScopeGuardImpl1()
    {
        if( ! dismissed_ ) 
            f_( arg_ );
    }
};

template < typename F >
class ScopeGuardImpl0 : public ScopeGuardImplBase
{
    F& f_;

public:
    ScopeGuardImpl0( const F& f )
    : f_(f)
    {
    }

    ~ScopeGuardImpl0()
    {
        if( ! dismissed_ ) 
            f_();
    }
};

template <typename F, typename Arg>
ScopeGuardImpl1< F, Arg > scope_guard( const F& f, const Arg& arg )
{
    return ScopeGuardImpl1< F, Arg >( f, arg );
}

template < typename F >
ScopeGuardImpl0< F > scope_guard( const F& f )
{
    return ScopeGuardImpl0< F >( f );
}
