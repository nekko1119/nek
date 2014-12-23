#ifndef NEK_DETAIL_DESTROY_HPP
#define NEK_DETAIL_DESTROY_HPP

#include <nek/allocator/allocator.hpp>
#include <nek/allocator/allocator_traits.hpp>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/type_traits/is_trivially_destructible.hpp>
#include <nek/utility/addressof.hpp>

namespace nek
{
    namespace detail
    {
        namespace destroy_detail
        {
            template <class T>
            void destroy_(T* ptr)
            {
                ptr->~T();
            }

            template <class ForwardIterator>
            void destroy_(ForwardIterator, ForwardIterator, true_type)
            {
            }

            template <class ForwardIterator>
            void destroy_(ForwardIterator first, ForwardIterator last, false_type)
            {
                for (; first != last; ++first) {
                    destroy_(nek::addressof(*first));
                }
            }
        }

        template <class ForwardIterator>
        void destroy(ForwardIterator first, ForwardIterator last)
        {
            using value_type = typename nek::iterator_traits<ForwardIterator>::value_type;
            destroy_detail::destroy_(first, last, nek::is_trivially_destructible<value_type>{});
        }

        template <class ForwardIterator, class Allocator>
        void destroy(ForwardIterator first, ForwardIterator last, Allocator& allocator)
        {
            using traits = nek::allocator_traits<Allocator>;
            for (; first != last; ++first) {
                traits::destroy(allocator, nek::addressof(*first));
            }
        }

        template <class ForwardIterator, class T>
        void destroy(ForwardIterator first, ForwardIterator last, nek::allocator<T>&)
        {
            destroy(first, last);
        }

        template <class ForwardIterator, class T>
        void destroy(ForwardIterator first, ForwardIterator last, std::allocator<T>&)
        {
            destroy(first, last);
        }
    }
}

#endif