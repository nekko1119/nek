#ifndef NEK_CONTAINER_FUNCTION_IS_EMPTY_HPP
#define NEK_CONTAINER_FUNCTION_IS_EMPTY_HPP

#include <cstddef>
#include <nek/container/container_traits.hpp>

namespace nek
{
    namespace is_empty_detail
    {
        template <class Container, class Tag>
        inline bool is_empty_(Container const& con, Tag) noexcept
        {
            return con.is_empty();
        }

        template <class Container>
        inline bool is_empty_(Container const& con, container_traits::std_container_tag) noexcept
        {
            return con.empty();
        }

        template <class Container>
        inline bool is_empty_(Container const& con, container_traits::nek_container_tag) noexcept
        {
            return con.begin() == con.end();
        }
    }

    template <class Container>
    inline bool is_empty(Container const& con) noexcept
    {
        using tag = typename container_traits::container_tag<Container>::type;
        return is_empty_detail::is_empty_(con, tag{});
    }

        template <class T, std::size_t N>
    inline constexpr bool is_empty(T (&)[N]) noexcept
    {
        // return true if N == 0. but N is never 0.
        return false;
    }
}

#endif
