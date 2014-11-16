#include "make_unsigned_test.hpp"
#include <type_traits>

enum e1 : char {};
enum class e2 : int {}; // TODO : is this valid that enum that underlying type is int -> unsigned long ?
enum class e3 : long {};

using types = ::testing::Types<
	std::tuple<e1, std::make_unsigned<e1>::type>,
    std::tuple<e2, std::make_unsigned<e2>::type>,
    std::tuple<e3, std::make_unsigned<e3>::type>
>;

INSTANTIATE_TYPED_TEST_CASE_P(enum, make_unsigned_test, types);