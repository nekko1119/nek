#include "make_unsigned_test.hpp"

using types = ::testing::Types<
  std::tuple<signed char, unsigned char>,
  std::tuple<char, unsigned char>,
  std::tuple<short, unsigned short>,
  std::tuple<int, unsigned int>,
  std::tuple<long, unsigned long>,
  std::tuple<long long, unsigned long long>
>;

INSTANTIATE_TYPED_TEST_CASE_P(signed, make_unsigned_test, types);