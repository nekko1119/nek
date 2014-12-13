#include "make_unsigned_test.hpp"

using types = ::testing::Types<
    std::tuple<unsigned char, unsigned char>,
    std::tuple<unsigned short, unsigned short>,
    std::tuple<unsigned int, unsigned int>,
    std::tuple<unsigned long, unsigned long>,
    std::tuple<unsigned long long, unsigned long long>
>;

INSTANTIATE_TYPED_TEST_CASE_P(unsigned, make_unsigned_test, types);