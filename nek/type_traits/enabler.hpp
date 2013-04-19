#ifndef NEK_TYPE_TRAITS_ENABLER_HPP
#define NEK_TYPE_TRAITS_ENABLER_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
	typedef void* enabler_t;
	extern enabler_t enabler;
}

#endif