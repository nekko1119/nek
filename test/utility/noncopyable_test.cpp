#include <nek/utility/noncopyable.hpp>
#include <gtest/gtest.h>

namespace
{
	struct noncopyable : private nek::noncopyable<noncopyable>
	{
		noncopyable() = default;

		// visual C++ 12.0 still doesn't support move constructor and move assign operator.
		noncopyable(noncopyable&&)
		{
		}

		noncopyable& operator=(noncopyable&&)
		{
			return *this;
		}
	};
}

TEST(noncopyable_test, copy)
{
	// comment out statements should be a complie error.
	// move is valid

	noncopyable a;

	//noncopyable b = a; // copy
	//b = a; // copy assign

	noncopyable d = std::move(a); // move
	noncopyable e;
	e = std::move(d); // move assign

	SUCCEED();
}