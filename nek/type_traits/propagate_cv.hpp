#ifndef NEK_TYPE_TRAITS_PROPAGATE_CV_HPP
#define NEK_TYPE_TRAITS_PROPAGATE_CV_HPP

namespace nek
{
    template <class Source, class Destination>
    struct propagate_cv
    {
        using type = Destination;
    };

    template <class Source, class Destination>
    struct propagate_cv<Source const, Destination>
    {
        using type = Destination const;
    };

    template <class Source, class Destination>
    struct propagate_cv<Source volatile, Destination>
    {
        using type = Destination volatile;
    };

    template <class Source, class Destination>
    struct propagate_cv<Source const volatile, Destination>
    {
        using type = const volatile Destination;
    };

    template <class Source, class Destination>
    using propagate_cv_t = typename propagate_cv<Source, Destination>::type;
}

#endif