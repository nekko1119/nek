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

TEST(swap_test, user_class)
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
  using std::begin;
  using std::end;
  using std::copy;
  using std::equal;

  int const expect1[] = {1, 2, 3};
  int actual1[3];
  copy(begin(expect1), end(expect1), begin(actual1));
  int const expect2[] = {10, 20, 30};
  int actual2[3];
  copy(begin(expect2), end(expect2), begin(actual2));

  // exersice
  nek::swap(actual1, actual2);

  // verify
  EXPECT_TRUE(equal(begin(expect1), end(expect1), begin(actual2)));
  EXPECT_TRUE(equal(begin(expect2), end(expect2), begin(actual1)));
}

TEST(swap_test, array_of_array_of_int)
{
  // setup
  using std::begin;
  using std::end;
  using std::copy;
  using std::equal;
  int const row = 2;
  int const column = 3;

  int const expect1[column][row] = {{1, 2}, {3, 4}, {5, 6}};
  int actual1[column][row];
  for (int i = 0; i < column; ++i) {
    copy(begin(expect1[i]), end(expect1[i]), begin(actual1[i]));
  }

  int const expect2[column][row] = {{7, 8}, {9, 10}, {11, 12}};
  int actual2[column][row];
  for (int i = 0; i < column; ++i) {
    copy(begin(expect2[i]), end(expect2[i]), begin(actual2[i]));
  }

  // exersice
  nek::swap(actual1, actual2);

  // verify
  for (int i = 0; i < column; ++i) {
    EXPECT_TRUE(equal(begin(expect1[i]), end(expect1[i]), begin(actual2[i])));
  }
  for (int i = 0; i < column; ++i) {
    EXPECT_TRUE(equal(begin(expect2[i]), end(expect2[i]), begin(actual1[i])));
  }
}
