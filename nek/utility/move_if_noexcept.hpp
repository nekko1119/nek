#ifndef NEK_UTILITY_MOVE_IF_NOEXCEPT_HPP
#define NEK_UTILITY_MOVE_IF_NOEXCEPT_HPP

#include <type_traits> // TODO : is_nothrow_move_constructible, is_copy_constructible
#include <nek/mpl/if.hpp>
#include <nek/utility/move.hpp>

namespace nek
{
  // TODO : mpl::and, mpl::not
  template <class T>
  inline auto move_if_noexcept(T& value) noexcept
    -> nek::mpl::if_c_t<
    !std::is_nothrow_move_constructible<T>::value &&
    std::is_copy_constructible<T>::value,
    T const&,
    T&&>
  {
    return nek::move(value);
  }
}

#endif