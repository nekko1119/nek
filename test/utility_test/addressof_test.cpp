#include <nek/utility/addressof.hpp>
#include <gtest/gtest.h>

TEST(addressof_test, enable_apply_address_operator_type)
{
  int val = 0;
  int* val_ptr = nek::addressof(val);
  EXPECT_EQ(&val, val_ptr);
}

struct address_operator_overrided_class
{
public:
  void* operator&() const
  {
    return nullptr;
  }

  bool is_same_address(address_operator_overrided_class* right) const
  {
    return this == right;
  }
};

TEST(addressof_test, disable_apply_address_operator_type)
{
  address_operator_overrided_class ad;
  ASSERT_EQ(nullptr, &ad);
  address_operator_overrided_class* ad_ptr = nek::addressof(ad);
  EXPECT_NE(nullptr, ad_ptr);
  EXPECT_TRUE(ad.is_same_address(ad_ptr));
}