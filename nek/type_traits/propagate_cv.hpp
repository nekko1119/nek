#ifndef NEK_TYPE_TRAITS_PROPAGATE_CV_HPP
#define NEK_TYPE_TRAITS_PROPAGATE_CV_HPP

namespace nek
{
    template <class Source, class Destination>
    struct propagate_cv
    {
        typedef Destination type;
    };

    template <class Source, class Destination>
    struct propagate_cv<const Source, Destination>
    {
        typedef const Destination type;
    };

    template <class Source, class Destination>
    struct propagate_cv<volatile Source, Destination>
    {
        typedef volatile Destination type;
    };

    template <class Source, class Destination>
    struct propagate_cv<const volatile Source, Destination>
    {
        typedef const volatile Destination type;
    };
}

#endif