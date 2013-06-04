#ifndef NEK_REMOVE_REFERENCE_HPP
#define NEK_REMOVE_REFERENCE_HPP

namespace nek
{
    template <class T>
    struct remove_reference
    {
        typedef T type;
    };

    template <class T>
    struct remove_reference<T&>
    {
        typedef T type;
    };

    template <class T>
    struct remove_reference<T&&>
    {
        typedef T type;
    };
}

#endif