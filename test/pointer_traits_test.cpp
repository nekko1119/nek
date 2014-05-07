#include <tuple>
#include <type_traits>
#include <utility>
#include <nek/utility/pointer_traits.hpp>
#include <gtest/gtest.h>

template <class T>
class pointer_traits_test
  : public ::testing::Test
{
protected:
  using ptr_t = typename std::tuple_element<0, T>::type;
  using elem_t = typename std::tuple_element<1, T>::type;
  using diff_t = typename std::tuple_element<2, T>::type;
  using pointer_t = typename std::tuple_element<3, T>::type;
};

TYPED_TEST_CASE_P(pointer_traits_test);

TYPED_TEST_P(pointer_traits_test, element_type)
{
  using actual_t = typename nek::pointer_traits<ptr_t>::element_type;
  static_assert(std::is_same<actual_t, elem_t>::value, "");
}

TYPED_TEST_P(pointer_traits_test, difference_type)
{
  using actual_t = typename nek::pointer_traits<ptr_t>::difference_type;
  static_assert(std::is_same<actual_t, diff_t>::value, "");
}

TYPED_TEST_P(pointer_traits_test, pointer)
{
  using actual_t = typename nek::pointer_traits<ptr_t>::pointer;
  static_assert(std::is_same<actual_t, pointer_t>::value, "");
}

TYPED_TEST_P(pointer_traits_test, rebind)
{
  using actual_t = typename nek::pointer_traits<ptr_t>::template rebind<double>::other;
  using expect_t = typename std::tuple_element<4, TypeParam>::type;
  static_assert(std::is_same<actual_t, expect_t>::value, "");
}

namespace
{
  template <class Ptr, class T>
  auto address_or_self_helper(T& val, std::true_type)
  {
    return &val;
  }

  template <class Ptr, class T>
  auto address_or_self_helper(T& val, std::false_type)
  {
    return Ptr(val);
  }

  template <class Ptr, class T>
  auto address_or_self(T& val)
  {
    return address_or_self_helper<Ptr>(val, std::is_pointer<Ptr>());
  }
}

TYPED_TEST_P(pointer_traits_test, pointer_to)
{
  elem_t val = 0;
  EXPECT_EQ(address_or_self<ptr_t>(val), nek::pointer_traits<ptr_t>::pointer_to(val));
}

REGISTER_TYPED_TEST_CASE_P(
  pointer_traits_test,
  element_type,
  difference_type,
  pointer,
  rebind,
  pointer_to);

namespace
{
  template <class T>
  class complete_smart_pointer_mock
  {
  private:
    T* ptr_ = nullptr;

  public:
    using element_type = T;
    using difference_type = char;

    complete_smart_pointer_mock() = default;

    complete_smart_pointer_mock(T&)
    {
    }

    template <class U>
    struct rebind
    {
      using other = complete_smart_pointer_mock<U>;
    };

    static complete_smart_pointer_mock pointer_to(T& p)
    {
      return complete_smart_pointer_mock(p);
    }

    friend bool operator==(complete_smart_pointer_mock const& l, complete_smart_pointer_mock const& r)
    {
      return l.ptr_ == r.ptr_;
    }
  };
}
using types = ::testing::Types<
  //        <pointer_type,                     element_type, difference_type, pointer,                          rebind<double>::other,
  std::tuple<int*,                             int,          std::ptrdiff_t,  int*,                             double*>,
  std::tuple<complete_smart_pointer_mock<int>, int,          char,            complete_smart_pointer_mock<int>, complete_smart_pointer_mock<double>>
>;

INSTANTIATE_TYPED_TEST_CASE_P(parameterized, pointer_traits_test, types);