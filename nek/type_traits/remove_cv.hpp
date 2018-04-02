#ifndef NEK_TYPE_TRAITS_REMOVE_CV_HPP
#define NEK_TYPE_TRAITS_REMOVE_CV_HPP

#include <nek/type_traits/remove_const.hpp>
#include <nek/type_traits/remove_volatile.hpp>

namespace nek
{
    template <class T>
    struct remove_cv
    {
        using type = remove_const_t<remove_volatile_t<T>>;
    };

    template <class T>
    using remove_cv_t = typename remove_cv<T>::type;
}

#endif
