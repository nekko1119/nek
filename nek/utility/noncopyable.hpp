#ifndef NEK_UTILITY_NONCOPYABLE_HPP
#define NEK_UTILITY_NONCOPYABLE_HPP

namespace nek
{
	//protection from ADL
	namespace noncopyable_
	{
		//using CRTP is a solution of EBO with multiple inheritance.
		template <class T>
		class noncopyable
		{
		protected:
			noncopyable(){}
			~noncopyable(){}//protected non virtual destructor
		private:
			noncopyable(const noncopyable&);//no defined
			noncopyable& operator=(const noncopyable&);//no defined
		};
	}
	using namespace noncopyable_;
}

#endif