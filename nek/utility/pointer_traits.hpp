#ifndef NEK_UTILITY_POINTER_TRAITS_HPP
#define NEK_UTILITY_POINTER_TRAITS_HPP

#include <cstddef>
#include <nek/mpl/if.hpp>
#include <nek/type_traits/has_difference_type.hpp>
#include <nek/type_traits/has_element_type.hpp>
#include <nek/type_traits/is_void.hpp>
#include <nek/utility/addressof.hpp>

namespace nek
{
    namespace detail
    {
        template <class T, bool = nek::has_element_type<T>::value>
        struct element_type
        {
            typedef typename T::element_type type;
        };

        template <template <class, class...> class Ptr, class T, class... Args>
        struct element_type<Ptr<T, Args...>, false>
        {
            typedef T type;
        };

        template <class T, bool = nek::has_difference_type<T>::value>
        struct difference_type
        {
            typedef typename T::difference_type type;
        };

        template <class T>
        struct difference_type<T, false>
        {
            typedef std::ptrdiff_t type;
        };

        template <class T, class U, class V = typename T::template rebind<U>::other>
        true_type has_rebind_impl(int);

        template <class, class>
        false_type has_rebind_impl(long);

        template <class T, class U>
        struct has_rebind
            : public decltype(has_rebind_impl<T, U>(0))
        {
        };

        template <class T, class U, bool = has_rebind<T, U>::value>
        struct rebind
        {
            typedef typename T::template rebind<U>::other type;
        };

        template <template <class, class...> class Ptr, class U, class T, class... Args>
        struct rebind<Ptr<T, Args...>, U, false>
        {
            typedef Ptr<U, Args...> type;
        };
    }

    template <class Ptr>
    struct pointer_traits
    {
    public:
        typedef Ptr pointer;
        typedef typename detail::element_type<Ptr>::type element_type;
        typedef typename detail::difference_type<Ptr>::type difference_type;

        template <class U>
        struct rebind
        {
            typedef typename detail::rebind<Ptr, U>::type other;
        };

    private:
        typedef typename mpl::if_<is_void<element_type>, char, element_type>::type not_void;

    public:
        static pointer pointer_to(not_void& value)
        {
            return Ptr::pointer_to(value);
        }
    };

    template <class T>
    struct pointer_traits<T*>
    {
    public:
        typedef T* pointer;
        typedef T element_type;
        typedef std::ptrdiff_t difference_type;

        template <class U>
        struct rebind
        {
            typedef U* other;
        };

    private:
        typedef typename mpl::if_<is_void<element_type>, char, element_type>::type not_void;

    public:
        static pointer pointer_to(not_void& value)
        {
            return addressof(value);
        }
    };
}

#endif