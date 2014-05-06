#ifndef NEK_ANY_ANY_EXCEPTION_HPP
#define NEK_ANY_ANY_EXCEPTION_HPP

#include <typeinfo>

namespace nek
{
  class bad_any_cast_exception
    : public std::bad_cast
  {
  public:
    virtual char const* what() const override
    {
      return "nek::bad_any_cast_exception: failed conversion";
    }
  };
}

#endif