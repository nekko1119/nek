#ifndef NEK_UTILITY_DECLVAL_HPP
#define NEK_UTILITY_DECLVAL_HPP

#include <nek/type_traits/add_rvalue_reference.hpp>

namespace nek
{
	template <class T>
	nek::add_rvalue_reference_t<T> declval() noexcept;
}

#endif