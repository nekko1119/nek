#ifndef NEK_MPL_BOOL_FWD_HPP
#define NEK_MPL_BOOL_FWD_HPP

namespace nek
{
	namespace mpl
	{
		template <bool C>
		struct bool_;

		using true_ = bool_<true>;
		using false_ = bool_<false>;
	}
}

#endif