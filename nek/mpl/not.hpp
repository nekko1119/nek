#ifndef NEK_MPL_NOT_HPP
#define NEK_MPL_NOT_HPP

#include <nek/mpl/bool.hpp>

namespace nek
{
	namespace mpl
	{
		template <bool C>
		struct not_c
			: bool_<!C>
		{
		};

		template <class T>
		struct not_
			: public bool_<!T::type::value>
		{
		};
	}
}

#endif