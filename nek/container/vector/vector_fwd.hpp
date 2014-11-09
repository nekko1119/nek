#ifndef NEK_CONTAINER_VECTOR_VECTOR_FWD_HPP
#define NEK_CONTAINER_VECTOR_VECTOR_FWD_HPP

namespace nek
{
	template <class T, class Allocator>
	class vector;

    template <class T, class Allocator>
    auto size(vector<T, Allocator> const& v) noexcept;

}

#endif