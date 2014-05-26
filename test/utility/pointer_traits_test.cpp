#include <tuple>
#include <type_traits>
#include <utility>
#include <nek/utility/pointer_traits.hpp>
#include <gtest/gtest.h>

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

    explicit complete_smart_pointer_mock(T& p)
      : ptr_(&p)
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

  template <class T>
  class simple_smart_pointer_mock
  {
  private:
    T* ptr_ = nullptr;

  public:
    simple_smart_pointer_mock() = default;

    simple_smart_pointer_mock(T* p)
      : ptr_(p)
    {
    }

    friend bool operator==(simple_smart_pointer_mock const& l, simple_smart_pointer_mock const& r)
    {
      return l.ptr_ == r.ptr_;
    }
  };
}

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

using types = ::testing::Types<
  //        <pointer_type,                     element_type, difference_type, pointer,                          rebind<double>::other,
  std::tuple<int*, int, std::ptrdiff_t, int*, double*>,
  std::tuple<complete_smart_pointer_mock<int>, int, char, complete_smart_pointer_mock<int>, complete_smart_pointer_mock<double>>,
  std::tuple<simple_smart_pointer_mock<int>, int, std::ptrdiff_t, simple_smart_pointer_mock<int>, simple_smart_pointer_mock<double>>
>;

TYPED_TEST_CASE(pointer_traits_test, types);

TYPED_TEST(pointer_traits_test, element_type)
{
  using actual_t = typename nek::pointer_traits<ptr_t>::element_type;
  static_assert(std::is_same<actual_t, elem_t>::value, "");
}

TYPED_TEST(pointer_traits_test, difference_type)
{
  using actual_t = typename nek::pointer_traits<ptr_t>::difference_type;
  static_assert(std::is_same<actual_t, diff_t>::value, "");
}

TYPED_TEST(pointer_traits_test, pointer)
{
  using actual_t = typename nek::pointer_traits<ptr_t>::pointer;
  static_assert(std::is_same<actual_t, pointer_t>::value, "");
}

TYPED_TEST(pointer_traits_test, rebind)
{
  using actual_t = typename nek::pointer_traits<ptr_t>::template rebind<double>::other;
  using expect_t = typename std::tuple_element<4, TypeParam>::type;
  static_assert(std::is_same<actual_t, expect_t>::value, "");
}

TEST(pointer_to_test, raw_type)
{
  int val = 0;
  EXPECT_EQ(&val, nek::pointer_traits<int*>::pointer_to(val));
}

TEST(pointer_to_test, complete_smart_ptr)
{
  int val = 0;
  EXPECT_EQ(complete_smart_pointer_mock<int>(val), nek::pointer_traits<complete_smart_pointer_mock<int>>::pointer_to(val));
}

TEST(pointer_to_test, simple_smart_pointer)
{
  // if smart pointer does not provide a static member function pointer_to,
  // instantiation of this test must be a compile time error.
  //int val = 0;
  //EXPECT_EQ(simple_smart_pointer_mock<int>(&val), nek::pointer_traits<simple_smart_pointer_mock<int>>::pointer_to(val));
}