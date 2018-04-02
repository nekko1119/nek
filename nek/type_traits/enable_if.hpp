#ifndef NEK_TYPE_TRAITS_ENABLE_IF_HPP
#define NEK_TYPE_TRAITS_ENABLE_IF_HPP

namespace nek
{
    template <bool C, class T = void>
    struct enable_if_c
    {
        using type = T;
    };

    template <class T>
    struct enable_if_c<false, T>
    {
    };

    template <class Cond, class T = void>
    struct enable_if
        : public enable_if_c<Cond::value, T>
    {
    };

    template <class Cond, class T = void>
    using enable_if_t = typename enable_if<Cond, T>::type;

    template <bool C, class T = void>
    struct disable_if_c
    {
        using type = T;
    };

    template <class T>
    struct disable_if_c<true, T>
    {
    };

    template <class Cond, class T = void>
    struct disable_if
        : public disable_if_c<Cond::value, T>
    {
    };

    template <class Cond, class T = void>
    using disable_if_t = typename disable_if<Cond, T>::type;
}

#endif
