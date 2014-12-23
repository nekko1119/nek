#ifndef NEK_UTILITY_HAS_XXX_HPP
#define NEK_UTILITY_HAS_XXX_HPP

#include <nek/type_traits/integral_constant.hpp>

#define NEK_HAS_XXX_TYPE_DEF(TYPE)\
namespace TYPE##_detail\
{\
    template <class T, class = typename T::TYPE>\
    nek::true_type test(T*);\
\
    template <class>\
    nek::false_type test(...);\
}\
template <class T>\
struct has_##TYPE\
    : public decltype(TYPE##_detail::test<T>(nullptr))\
{\
}

#endif