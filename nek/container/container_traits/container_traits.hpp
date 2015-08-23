#ifndef NEK_CONTAINER_CONTAINER_TRAITS_CONTAINER_TRAITS_HPP
#define NEK_CONTAINER_CONTAINER_TRAITS_CONTAINER_TRAITS_HPP

#include <cstddef>
#include <nek/container/container_traits/container_tag.hpp>
#include <nek/mpl/identity.hpp>
#include <nek/mpl/eval_if.hpp>
#include <nek/type_traits/is_array.hpp>
#include <nek/utility/has_xxx_def.hpp>

#ifdef NEK_CONTAINER_MEMBER_TYPE_DEF
#   undef NEK_CONTAINER_MEMBER_TYPE_DEF
#endif
#define NEK_CONTAINER_MEMBER_TYPE_DEF(TYPE, ARRAY_TYPE)\
template <class Container>\
struct TYPE\
{\
    using type = typename Container::TYPE;\
};\
\
template <class T, std::size_t N>\
struct TYPE<T[N]>\
{\
    using type = ARRAY_TYPE;\
};\
\
template <class T>\
struct TYPE<T[]>\
{\
    using type = ARRAY_TYPE;\
};\
\
template <class Container>\
using TYPE##_t = typename TYPE<Container>::type

namespace nek
{
    namespace container_traits
    {
        namespace container_traits_detail
        {
            NEK_HAS_XXX_TYPE_DEF(container_tag);
            template <class Container>
            struct get_container_tag
            {
                using type = typename Container::container_tag;
            };
        }
        NEK_CONTAINER_MEMBER_TYPE_DEF(value_type, T);
        NEK_CONTAINER_MEMBER_TYPE_DEF(size_type, std::size_t);

        template <class Container>
        struct container_tag
        {
            using type = mpl::if_t<
                nek::is_array<Container>,
                array_container_tag,
                typename mpl::eval_if_t<container_traits_detail::has_container_tag<Container>,
                container_traits_detail::get_container_tag<Container>,
                mpl::identity<unknown_container_tag>>>;
        };

        template <class Container>
        using container_tag_t = typename container_tag<Container>::type;
    }
}

#undef NEK_CONTAINER_MEMBER_TYPE_DEF

#endif
