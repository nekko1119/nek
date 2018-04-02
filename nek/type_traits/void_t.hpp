#ifndef NEK_TYPE_TRAITS_VOID_T_HPP
#define NEK_TYPE_TRAITS_VOID_T_HPP

namespace nek
{
    // workaround http://cpplover.blogspot.jp/2014/03/2014-02-post-issaquah-n3910-n3919.html
    template <class...>
    struct voider
    {
        using type = void;
    };

    template <class ...T>
    using void_t = typename voider<T...>::type;
}

#endif
