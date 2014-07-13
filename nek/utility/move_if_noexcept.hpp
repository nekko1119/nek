#ifndef NEK_UTILITY_MOVE_IF_NOEXCEPT_HPP
#define NEK_UTILITY_MOVE_IF_NOEXCEPT_HPP

#include <type_traits> // TODO : is_nothrow_move_constructible, is_copy_constructible
#include <nek/mpl/and.hpp>
#include <nek/mpl/if.hpp>
#include <nek/utility/move.hpp>

namespace nek
{
  // TODO : mpl::not
  template <class T>
  inline auto move_if_noexcept(T& value) noexcept
    -> mpl::if_t<
    mpl::and_c<
    !std::is_nothrow_move_constructible<T>::value,
    std::is_copy_constructible<T>::value>,
    T const&,
    T&&>
  {
    return nek::move(value);
  }
}

#endif