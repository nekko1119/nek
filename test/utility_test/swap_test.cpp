#include <algorithm>
#include <string>
#include <nek/utility/swap.hpp>
#include <gtest/gtest.h>

namespace swap_test_ns
{
  class swap_test_mock
  {
  private:
    int data_;

    static int& copy_count_ref()
    {
      static int count = 0;
      return count;
    }

    static int& swap_count_ref()
    {
      static int count = 0;
      return count;
    }

  public:
    swap_test_mock(int data)
      : data_(data)
    {}

    swap_test_mock(swap_test_mock const& right)
    {
      data_ = right.data_;
      ++copy_count_ref();
    }

    swap_test_mock& operator=(swap_test_mock const& right)
    {
      data_ = right.data_;
      ++copy_count_ref();
      return *this;
    }

    void swap(swap_test_mock& right)
    {
      int temp = data_;
      data_ = right.data_;
      right.data_ = temp;
      ++swap_count_ref();
    }

    int get() const
    {
      return data_;
    }

    static void reset()
    {
      copy_count_ref() = 0;
      swap_count_ref() = 0;
    }

    static int copy_count()
    {
      return copy_count_ref();
    }

    static int swap_count()
    {
      return swap_count_ref();
    }
  };

  bool operator==(swap_test_mock const& l, swap_test_mock const& r)
  {
    return l.get() == r.get();
  }

  void swap(swap_test_mock& l, swap_test_mock& r)
  {
    l.swap(r);
  }
}
TEST(swap_test, primitive)
{
  // setup
  int const expect1 = 1;
  int actual1 = expect1;
  int const expect2 = 2;
  int actual2 = expect2;

  // exercise
  nek::swap(actual1, actual2);

  // verify
  EXPECT_EQ(expect1, actual2);
  EXPECT_EQ(expect2, actual1);
}

TEST(swap_test, std_string)
{
  // setup
  std::string const expect1 = "abc";
  std::string actual1 = expect1;
  std::string const expect2 = "def";
  std::string actual2 = expect2;

  // exercise
  nek::swap(actual1, actual2);

  // verify
  EXPECT_EQ(expect1, actual2);
  EXPECT_EQ(expect2, actual1);
}

TEST(Swap_test, user_class)
{
  // setup
  using type = swap_test_ns::swap_test_mock;
  type const expect1{1};
  type actual1 = expect1;
  type const expect2{2};
  type actual2 = expect2;

  // exercise
  type::reset();
  nek::swap(actual1, actual2);

  // verify
  EXPECT_EQ(expect1, actual2);
  EXPECT_EQ(expect2, actual1);
  EXPECT_EQ(0, type::copy_count());
  EXPECT_EQ(1, type::swap_count());
}

TEST(swap_test, array_of_int)
{
  // setup
  int const expect1[] = {1, 2, 3};
  int actual1[3];
  std::copy(std::begin(expect1), std::end(expect1), std::begin(actual1));
  int const expect2[] = {10, 20, 30};
  int actual2[3];
  std::copy(std::begin(expect2), std::end(expect2), std::begin(actual2));

  // exersice
  nek::swap(actual1, actual2);

  // verify
  EXPECT_TRUE(std::equal(std::begin(expect1), std::end(expect1), std::begin(actual2)));
  EXPECT_TRUE(std::equal(std::begin(expect2), std::end(expect2), std::begin(actual1)));
}
