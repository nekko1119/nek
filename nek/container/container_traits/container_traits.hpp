#ifndef NEK_CONTAINER_CONTAINER_TRAITS_CONTAINER_TRAITS_HPP
#define NEK_CONTAINER_CONTAINER_TRAITS_CONTAINER_TRAITS_HPP

#include <cstddef>
#include <nek/container/container_traits/container_tag.hpp>

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
        NEK_CONTAINER_MEMBER_TYPE_DEF(value_type, T);
        NEK_CONTAINER_MEMBER_TYPE_DEF(size_type, std::size_t);

        template <class Container>
        struct container_tag
        {
            using type = typename Container::container_tag;
        };
    }
}

#undef NEK_CONTAINER_MEMBER_TYPE_DEF

#endif
