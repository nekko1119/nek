#ifndef NEK_CONTAINER_FUNCTION_POP_BACK_HPP
#define NEK_CONTAINER_FUNCTION_POP_BACK_HPP

#include <cassert>

namespace nek
{
	template <class Container>
	void pop_back(Container& con)
	{
		auto last = --con.end();
		con.erase(last, con.end());
	}
}

#endif