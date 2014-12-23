#ifndef NEK_UTILITY_IS_XXX_HPP
#define NEK_UTILITY_IS_XXX_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

#define NEK_IS_XXX_DEF(TYPE)\
namespace TYPE##_detail\
{\
    template <class T>\
    struct is_##TYPE\
	: public false_type\
        {\
        }; \
    \
    template <>\
    struct is_##TYPE<TYPE>\
    : public true_type\
        {\
        }; \
}\
\
template <class T>\
struct is_##TYPE\
    : public TYPE##_detail::is_##TYPE<typename remove_cv<T>::type>\
{\
}\

#endif