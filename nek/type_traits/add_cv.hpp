#ifndef NEK_TYPE_TRAITS_ADD_CV_HPP
#define NEK_TYPE_TRAITS_ADD_CV_HPP

#include <nek/type_traits/add_const.hpp>
#include <nek/type_traits/add_volatile.hpp>

namespace nek
{
    template <class T>
    struct add_cv
    {
        using type = add_const_t<add_volatile_t<T>>;
    };

    template <class T>
    using add_cv_t = typename add_cv<T>::type;
}

#endif