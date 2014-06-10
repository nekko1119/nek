#include "make_unsigned_test.hpp"

enum e1 : char {};
enum class e2 : int {}; // TODO : is this valid that enum (underlying type is int) -> unsigned long ?
enum class e3 : long {};

using types = ::testing::Types<
  std::tuple<e1, unsigned char>,
  std::tuple<e2, unsigned int>,
  std::tuple<e3, unsigned int>
>;

INSTANTIATE_TYPED_TEST_CASE_P(enum, make_unsigned_test, types);