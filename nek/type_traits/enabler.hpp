#ifndef NEK_TYPE_TRAITS_ENABLER_HPP
#define NEK_TYPE_TRAITS_ENABLER_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
	typedef integral_constant<void*, nullptr> enabler_t;
	extern enabler_t enabler;
}

#endif