#ifndef NEK_TYPE_TRAITS_ADD_CV_HPP
#define NEK_TYPE_TRAITS_ADD_CV_HPP

#include <nek/type_traits/add_const.hpp>
#include <nek/type_traits/add_volatile.hpp>

namespace nek
{
    template <class T>
    struct add_cv
    {
        typedef typename add_const<typename add_volatile<T>::type>::type type;
    };
}

#endif