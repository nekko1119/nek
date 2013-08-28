#ifndef NEK_UTILITY_IS_XXX_HPP
#define NEK_UTILITY_IS_XXX_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

#define NEK_IS_XXX(name)\
namespace name##detail\
{\
    template <class T>\
    struct is_##name\
        : public false_type\
    {\
    };\
\
    template <>\
    struct is_##name<name>\
        : public true_type\
    {\
    };\
}\
\
template <class T>\
struct is_##name\
    : public name##detail::is_##name<typename remove_cv<T>::type>\
{\
}\

#endif