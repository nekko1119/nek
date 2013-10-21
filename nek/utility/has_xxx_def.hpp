#ifndef NEK_UTILITY_HAS_XXX_HPP
#define NEK_UTILITY_HAS_XXX_HPP

#include <nek/type_traits/integral_constant.hpp>

#define NEK_HAS_XXX_TYPE_DEF(type)\
namespace\
{\
    namespace type##detail\
    {\
        template <class T, class = T::##type##>\
        true_type has_##type##(int);\
    \
        template <class>\
        false_type has_##type##(long);\
    }\
\
}\
template <class T>\
struct has_##type##\
    : public decltype(type##detail::has_##type##<T>(0))\
{\
};\
namespace type##detail {}

#endif