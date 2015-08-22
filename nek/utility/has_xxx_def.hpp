#ifndef NEK_UTILITY_HAS_XXX_HPP
#define NEK_UTILITY_HAS_XXX_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/void_t.hpp>

#define NEK_HAS_XXX_TYPE_DEF(TYPE)\
template <class, class = void>\
struct has_##TYPE\
    : public nek::false_type\
{\
};\
\
template <class T>\
struct has_##TYPE<T, nek::void_t<typename T::TYPE>>\
    : public nek::true_type\
{\
}\

#endif