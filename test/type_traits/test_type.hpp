#ifndef NEK_TYPE_TRAITS_TEST_TEST_TYPE_HPP
#define NEK_TYPE_TRAITS_TEST_TEST_TYPE_HPP

namespace type_traits_test
{
  struct empty_type
  {
    empty_type() = default;
    ~empty_type() = default;
    empty_type(empty_type const&) = default;
    empty_type& operator=(empty_type const&) = default;
  };

  struct class_type
  {
    int x;

    class_type() = default;
    ~class_type() = default;
    class_type(class_type const&) = default;
    class_type& operator=(class_type const&) = default;

    void f1();
    int f2();
    int f3(int);
    int f4(int) const;
  };

  enum enum_type
  {
    first,
    second,
    third
  };

  union union_type
  {
    ~union_type() = default;
    int x;
    double y;
  };

  struct standard_layout_type
    : public class_type
  {
    standard_layout_type(){}
    ~standard_layout_type(){}
    standard_layout_type(standard_layout_type const&){}
    standard_layout_type& operator=(standard_layout_type const&){ return *this; }
  };

  struct trivially_copyable_type
    : public class_type
  {
    double y;

    trivially_copyable_type(){}
    ~trivially_copyable_type() = default;
    trivially_copyable_type(trivially_copyable_type const&) = default;
    trivially_copyable_type& operator=(trivially_copyable_type const&) = default;
  };

  struct pod_type
    : public class_type
  {
    pod_type() = default;
    ~pod_type() = default;
    pod_type(pod_type const&) = default;
    pod_type& operator=(pod_type const&) = default;
  };

  class nothrow_type
  {
    nothrow_type() noexcept {}
    ~nothrow_type() noexcept {}
    nothrow_type(nothrow_type const&) noexcept {}
    nothrow_type& operator=(nothrow_type const&) noexcept { return *this; }
  };

  using f1_type = void (*)();
  using f2_type = int (*)();
  using f3_type = int (*)(int);
  using mf1_type = void (class_type::*)();
  using mf2_type = int (class_type::*)();
  using mf3_type = int (class_type::*)(int);
  using mf4_type = int (class_type::*)(int) const;
}

#endif