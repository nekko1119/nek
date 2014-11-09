#ifndef NEK_UTILITY_HAS_XXX_HPP
#define NEK_UTILITY_HAS_XXX_HPP

#include <nek/type_traits/integral_constant.hpp>

#define NEK_HAS_XXX_TYPE_DEF(type)\
namespace type##_detail\
{\
	template <class T, class = typename T::type>\
	nek::true_type has_##type(int);\
\
	template <class>\
	nek::false_type has_##type(long);\
}\
template <class T>\
struct has_##type\
	: public decltype(type##_detail::has_##type<T>(0))\
{\
}

#endif