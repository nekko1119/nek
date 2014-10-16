#ifndef NEK_TYPE_TRAITS_IS_BASE_OF_HPP
#define NEK_TYPE_TRAITS_IS_BASE_OF_HPP

#include <nek/mpl/and.hpp>
#include <nek/mpl/not.hpp>
#include <nek/mpl/or.hpp>
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/is_class.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
	namespace is_base_of_detail
	{
		template <class Base, class Derived>
		struct is_base_of_impl
		{
		private:
			template <class T>
			static nek::true_type check(Derived&, T);
			static nek::false_type check(Base&, int);

			struct host
			{
				operator Base&() const;
				operator Derived&();
			};

		public:
			using type = decltype(check(host{}, 0));
		};

		template <class Base, class Derived, bool = mpl::and_<nek::is_class<Base>, nek::is_class<Derived>, mpl::not_<nek::is_same<Base, Derived>>>::value>
		struct is_base_of_
			: public is_base_of_impl<Base, Derived>::type
		{
		};

		template <class Base, class Derived>
		struct is_base_of_<Base, Derived, false>
			: public nek::false_type
		{
		};

		template <class Base, class Derived>
		struct is_base_of_is_class
		{
		private:
			using non_cv_base = nek::remove_cv_t<Base>;
			using non_cv_derived = nek::remove_cv_t<Derived>;

		public:
			static constexpr bool value = mpl::or_<
				is_base_of_<non_cv_base, non_cv_derived>,
					mpl::and_<nek::is_class<non_cv_base>, nek::is_same<non_cv_base, non_cv_derived>>
				>::value;
		};
	}

	template <class Base, class Derived>
	struct is_base_of
		: public nek::integral_constant<bool, is_base_of_detail::is_base_of_is_class<Base, Derived>::value>
	{
	};
}

#endif
