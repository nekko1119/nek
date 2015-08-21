#include <nek/type_traits/is_constructible.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "static_assert.hpp"

namespace
{
    struct x
    {
        explicit x(int) {}
        x(x const&) = delete;
    };

    class y
    {
        y() {}
    };

    struct base
    {
        virtual ~base() {}
    };

    struct derived
        : public base
    {
    };
}

TEST(is_constructible_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_constructible<int, int>>();
}

TEST(is_constructible_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_constructible<int, void>>();
}

TEST(is_constructible_test, yes)
{
    using i_type = nek::is_constructible<int>;
    using ii_type = nek::is_constructible<int, int>;
    using id_type = nek::is_constructible<int, double>;
    using xi_type = nek::is_constructible<x, int>;
    using iter_type = std::vector<double>::iterator;
    using vin_type = nek::is_constructible<std::vector<int>, std::initializer_list<int>>;
    using vii_type = nek::is_constructible<std::vector<int>, iter_type, iter_type>; // vector(Iterator, Iterator)
    using bd_type = nek::is_constructible<base, derived>;
    using pbpd_type = nek::is_constructible<base*, derived*>;
    using rbrd_type = nek::is_constructible<base&, derived&>;
    using brd_type = nek::is_constructible<base, derived&>;
    STATIC_ASSERT_TRUE_VALUE(i_type);
    STATIC_ASSERT_TRUE_VALUE(ii_type);
    STATIC_ASSERT_TRUE_VALUE(id_type);
    STATIC_ASSERT_TRUE_VALUE(xi_type);
    STATIC_ASSERT_TRUE_VALUE(vin_type);
    STATIC_ASSERT_TRUE_VALUE(vii_type);
    STATIC_ASSERT_TRUE_VALUE(bd_type);
    STATIC_ASSERT_TRUE_VALUE(pbpd_type);
    STATIC_ASSERT_TRUE_VALUE(rbrd_type);
    STATIC_ASSERT_TRUE_VALUE(brd_type);
}

TEST(is_constructible_test, no)
{
    using xx_type = nek::is_constructible<x, x>;
    using fi_type = nek::is_constructible<void(*)(int), int>;
    using vi_type = nek::is_constructible<void, int>;
    using y_type = nek::is_constructible<y>;
    using vvv_type = nek::is_constructible<std::vector<int>, void, void>;
    using rbd_type = nek::is_constructible<base&, derived>;

    STATIC_ASSERT_FALSE_VALUE(xx_type);
    STATIC_ASSERT_FALSE_VALUE(fi_type);
    STATIC_ASSERT_FALSE_VALUE(vi_type);
    STATIC_ASSERT_FALSE_VALUE(y_type);
    STATIC_ASSERT_FALSE_VALUE(vvv_type);
    STATIC_ASSERT_FALSE_VALUE(rbd_type);
}
