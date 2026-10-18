#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(5);
	for (int i = 0; i < 5; ++i) v[i] = i + 1;

	TDynamicVector<int> v1(v);

	EXPECT_EQ(v.size(), v1.size());
	EXPECT_TRUE(v == v1);
	EXPECT_FALSE(v != v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	TDynamicVector<int> v1(v);
	v1[0] = 100;
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(100, v1[0]);

	v[1] = 200;
	EXPECT_EQ(2, v1[1]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, const_operator_bracket_works)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	const TDynamicVector<int>& cv = v;
	EXPECT_EQ(1, cv[0]);
	EXPECT_EQ(3, cv[2]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(5));
	ASSERT_ANY_THROW(v.at(100));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 4;

	TDynamicVector<int> original(v);
	v = v;

	EXPECT_EQ(original.size(), v.size());
	EXPECT_TRUE(v == original);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> a(3), b(3);
	a[0] = 1; a[1] = 2; a[2] = 3;
	b[0] = 4; b[1] = 5; b[2] = 6;

	a = b;

	EXPECT_EQ(3, a.size());
	EXPECT_TRUE(a == b);
	EXPECT_EQ(4, a[0]);
	EXPECT_EQ(5, a[1]);
	EXPECT_EQ(6, a[2]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> a(3), b(5);
	a = b;
	EXPECT_EQ(5, a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> a(2), b(4);
	a[0] = 1; a[1] = 2;
	b[0] = 10; b[1] = 20; b[2] = 30; b[3] = 40;

	a = b;

	EXPECT_EQ(4, a.size());
	EXPECT_TRUE(a == b);
	EXPECT_EQ(10, a[0]);
	EXPECT_EQ(40, a[3]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> a(3), b(3);
	a[0] = 1; a[1] = 2; a[2] = 3;
	b[0] = 1; b[1] = 2; b[2] = 3;

	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(4);
	v[0] = 7; v[1] = 8; v[2] = 9; v[3] = 10;
	EXPECT_TRUE(v == v);
	EXPECT_FALSE(v != v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> a(3), b(4);
	EXPECT_FALSE(a == b);
	EXPECT_TRUE(a != b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	TDynamicVector<int> res = v + 10;

	EXPECT_EQ(3, res.size());
	EXPECT_EQ(11, res[0]);
	EXPECT_EQ(12, res[1]);
	EXPECT_EQ(13, res[2]);
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(2, v[1]);
	EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 10; v[1] = 20; v[2] = 30;

	TDynamicVector<int> res = v - 5;

	EXPECT_EQ(5, res[0]);
	EXPECT_EQ(15, res[1]);
	EXPECT_EQ(25, res[2]);
	EXPECT_EQ(10, v[0]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	TDynamicVector<int> res = v * 2;

	EXPECT_EQ(2, res[0]);
	EXPECT_EQ(4, res[1]);
	EXPECT_EQ(6, res[2]);
	EXPECT_EQ(1, v[0]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> a(3), b(3);
	a[0] = 1; a[1] = 2; a[2] = 3;
	b[0] = 10; b[1] = 20; b[2] = 30;

	TDynamicVector<int> res = a + b;

	EXPECT_EQ(11, res[0]);
	EXPECT_EQ(22, res[1]);
	EXPECT_EQ(33, res[2]);
	EXPECT_EQ(1, a[0]);
	EXPECT_EQ(10, b[0]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(2), b(3);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> a(3), b(3);
	a[0] = 10; a[1] = 20; a[2] = 30;
	b[0] = 1;  b[1] = 2;  b[2] = 3;

	TDynamicVector<int> res = a - b;

	EXPECT_EQ(9, res[0]);
	EXPECT_EQ(18, res[1]);
	EXPECT_EQ(27, res[2]);
	EXPECT_EQ(10, a[0]);
	EXPECT_EQ(1, b[0]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(2), b(3);
	ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> a(3), b(3);
	a[0] = 1; a[1] = 2; a[2] = 3;
	b[0] = 4; b[1] = 5; b[2] = 6;

	int dot = a * b;

	EXPECT_EQ(32, dot);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(2), b(3);
	ASSERT_ANY_THROW(a * b);
}

TEST(TDynamicVector, move_constructor_transfers_ownership)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	int* oldPtr = &v[0];

	TDynamicVector<int> v1(std::move(v));

	EXPECT_EQ(3, v1.size());
	EXPECT_EQ(1, v1[0]);
	EXPECT_EQ(0, v.size());
	EXPECT_EQ(oldPtr, &v1[0]);
}

TEST(TDynamicVector, move_assignment_transfers_ownership)
{
	TDynamicVector<int> a(2), b(3);
	b[0] = 10; b[1] = 20; b[2] = 30;
	a = std::move(b);
	EXPECT_EQ(3, a.size());
	EXPECT_EQ(10, a[0]);
	EXPECT_EQ(0, b.size());
}

TEST(TDynamicVector, equal_size_but_different_elements_are_not_equal)
{
	TDynamicVector<int> a(3), b(3);
	a[0] = 1; a[1] = 2; a[2] = 3;
	b[0] = 1; b[1] = 2; b[2] = 999;
	EXPECT_FALSE(a == b);
	EXPECT_TRUE(a != b);
}
