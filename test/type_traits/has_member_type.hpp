#ifndef NEK_TYPE_TRAITS_TEST_HAS_MEMBER_TYPE_HPP
#define NEK_TYPE_TRAITS_TEST_HAS_MEMBER_TYPE_HPP

namespace
{
    struct has_member_type
    {
        using NEK_MEMBER_TYPE = int;
    };

    struct has_member_func
    {
        void NEK_MEMBER_TYPE() {}
    };

    struct has_member_obj
    {
        int NEK_MEMBER_TYPE;
    };
}

#define NEK_HAS_MEMBER_TYPE(type)\
  STATIC_ASSERT_TRUE_VALUE(type<has_member_type>);\
  STATIC_ASSERT_FALSE_VALUE(type<has_member_func>);\
  STATIC_ASSERT_FALSE_VALUE(type<has_member_obj>);

#endif
