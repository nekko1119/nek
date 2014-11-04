#ifndef NEK_MATM_GCD_HPP
#define NEK_MATH_GCD_HPP

namespace nek
{
	namespace math
	{
		template <class T>
		T gcd(T a, T b)
		{
			while (b != static_cast<T>(0)) {
				auto const r = a % b;
				a = b;
				b = r;
			}
			return a < 0 ? -a : a; // TODO : abs
		}
	}
}

#endif
