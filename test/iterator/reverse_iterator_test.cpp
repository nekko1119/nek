#include <nek/iterator/reverse_iterator.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../type_traits/static_assert.hpp"

class reverse_iterator_test
	: public ::testing::Test
{
protected:
	using mock_type = std::vector<std::string>;
	using iter_type = mock_type::iterator;
	using type = nek::reverse_iterator<iter_type>;

	mock_type mock;
	type sut;

	reverse_iterator_test()
		: mock{{"this", "is", "a", "test"}},
		sut{mock.end()}
	{
	}
};

TEST_F(reverse_iterator_test, member_type)
{
	STATIC_ASSERT_EQ(type::value_type, std::string);
	STATIC_ASSERT_EQ(type::iterator_type, iter_type);
	STATIC_ASSERT_EQ(type::iterator_category, std::random_access_iterator_tag);
	STATIC_ASSERT_EQ(type::pointer, mock_type::pointer);
	STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
	STATIC_ASSERT_EQ(type::reference, std::string&);
}

TEST_F(reverse_iterator_test, default_constructor)
{
	nek::reverse_iterator<iter_type> instance;
}

TEST_F(reverse_iterator_test, assign_constructor)
{
	nek::reverse_iterator<iter_type> instance{mock.end()};
	EXPECT_EQ(mock.end(), instance.base());
	EXPECT_EQ(*--mock.end(), *instance);
}

TEST_F(reverse_iterator_test, copy_constructor)
{
	nek::reverse_iterator<iter_type> copied{sut};
	EXPECT_EQ(sut, copied);
}

TEST_F(reverse_iterator_test, base)
{
	EXPECT_EQ(mock.end(), sut.base());
}

TEST_F(reverse_iterator_test, dereference)
{
	EXPECT_EQ(*--mock.end(), *sut);
}

TEST_F(reverse_iterator_test, arrow)
{
	EXPECT_EQ(mock.begin()->length(), sut->length());
}

TEST_F(reverse_iterator_test, prefix_increment)
{
	++sut;
	auto expected = ----mock.end();
	EXPECT_EQ(*expected, *sut);
}

TEST_F(reverse_iterator_test, suffix_increment)
{
	auto actual = sut++;
	auto expected = ----mock.end();
	EXPECT_EQ(*--mock.end(), *actual);
	EXPECT_EQ(*expected, *sut);
}

TEST_F(reverse_iterator_test, prefix_decrement)
{
	type end{mock.begin()};
	--end;
	auto expected = mock.begin();
	EXPECT_EQ(*expected, *end);
}

TEST_F(reverse_iterator_test, subscript)
{
	EXPECT_EQ(sut[3], mock[0]);
}

TEST_F(reverse_iterator_test, plus)
{
	auto actual1 = sut + 2;
	auto actual2 = 2 + sut;
	sut += 2;
	auto expected = mock.end() - 2;
	EXPECT_EQ(expected, actual1.base());
	EXPECT_EQ(expected, actual2.base());
	EXPECT_EQ(expected, sut.base());
}

TEST_F(reverse_iterator_test, minus)
{
	type end{mock.begin()};
	auto actual = end - 2;
	end -= 2;
	auto expected = mock.begin() + 2;
	EXPECT_EQ(expected, actual.base());
	EXPECT_EQ(expected, end.base());
}

TEST_F(reverse_iterator_test, compare)
{
	nek::reverse_iterator<iter_type> begin{mock.end()};
	nek::reverse_iterator<iter_type> end{mock.begin()};
	EXPECT_LT(begin, end);
	EXPECT_LE(begin, end);
	EXPECT_GT(end, begin);
	EXPECT_GE(end, begin);
}

TEST_F(reverse_iterator_test, equal)
{
	nek::reverse_iterator<iter_type> begin{mock.end()};
	nek::reverse_iterator<iter_type> end{mock.begin()};
	EXPECT_EQ(begin, begin);
	EXPECT_NE(begin, end);
}
