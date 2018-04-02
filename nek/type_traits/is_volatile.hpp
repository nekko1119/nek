#ifndef NEK_TYPE_TRAITS_IS_VOLATILE_HPP
#define NEK_TYPE_TRAITS_IS_VOLATILE_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_extends.hpp>

namespace nek
{
    namespace is_volatile_detail
    {
        template <class T>
        struct is_volatile_
            : public false_type
        {
        };

        template <class T>
        struct is_volatile_<T volatile>
            : public true_type
        {
        };
    }

    template <class T>
    struct is_volatile
        : public is_volatile_detail::is_volatile_<nek::remove_extends_t<T>>
    {
    };
}

#endif
