#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(7));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 5));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-7));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(8);
	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(3);
	v1[0] = 2; v1[1] = 3; v1[2] = 4;

	TDynamicVector<int> v2(v1);

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(3);
	v1[0] = 5; v1[1] = 6; v1[2] = 7;

	TDynamicVector<int> v2(v1);
	v2[0] = 15;

	EXPECT_NE(v1[0], v2[0]);
	EXPECT_EQ(5, v1[0]);
	EXPECT_EQ(15, v2[0]);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(5);
	EXPECT_EQ(5, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 7;

	EXPECT_EQ(7, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(v.at(5));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(3);
	v[0] = 2; v[1] = 3; v[2] = 4;

	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(2, v[0]);
	EXPECT_EQ(3, v[1]);
	EXPECT_EQ(4, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(3);
	v1[0] = 2; v1[1] = 3; v1[2] = 4;

	TDynamicVector<int> v2(3);
	v2 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(6);

	v2 = v1;

	EXPECT_EQ(3, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(3);
	v1[0] = 2; v1[1] = 3; v1[2] = 4;

	TDynamicVector<int> v2(5);
	v2 = v1;

	EXPECT_EQ(v1, v2);
	EXPECT_EQ(3, v2.size());
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(3);
	v1[0] = 2; v1[1] = 3; v1[2] = 4;

	TDynamicVector<int> v2(3);
	v2[0] = 2; v2[1] = 3; v2[2] = 4;

	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(3);
	v[0] = 2; v[1] = 3; v[2] = 4;

	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(5);

	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(3);
	v1[0] = 2; v1[1] = 3; v1[2] = 4;

	TDynamicVector<int> v2 = v1 + 6;

	EXPECT_EQ(8, v2[0]);
	EXPECT_EQ(9, v2[1]);
	EXPECT_EQ(10, v2[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(3);
	v1[0] = 7; v1[1] = 8; v1[2] = 9;

	TDynamicVector<int> v2 = v1 - 3;

	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
	EXPECT_EQ(6, v2[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(3);
	v1[0] = 2; v1[1] = 3; v1[2] = 4;

	TDynamicVector<int> v2 = v1 * 4;

	EXPECT_EQ(8, v2[0]);
	EXPECT_EQ(12, v2[1]);
	EXPECT_EQ(16, v2[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	v1[0] = 2; v1[1] = 3; v1[2] = 4;

	TDynamicVector<int> v2(3);
	v2[0] = 5; v2[1] = 6; v2[2] = 7;

	TDynamicVector<int> v3 = v1 + v2;

	EXPECT_EQ(7, v3[0]);
	EXPECT_EQ(9, v3[1]);
	EXPECT_EQ(11, v3[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(5);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	v1[0] = 8; v1[1] = 9; v1[2] = 10;

	TDynamicVector<int> v2(3);
	v2[0] = 2; v2[1] = 3; v2[2] = 4;

	TDynamicVector<int> v3 = v1 - v2;

	EXPECT_EQ(6, v3[0]);
	EXPECT_EQ(6, v3[1]);
	EXPECT_EQ(6, v3[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(5);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	v1[0] = 2; v1[1] = 3; v1[2] = 4;

	TDynamicVector<int> v2(3);
	v2[0] = 5; v2[1] = 6; v2[2] = 7;

	int result = v1 * v2;

	EXPECT_EQ(56, result);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(5);

	ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, move_constructor_works_correctly)
{
	TDynamicVector<int> original(4);
	original[0] = 10; original[1] = 20; original[2] = 30; original[3] = 40;

	TDynamicVector<int> moved(std::move(original));

	EXPECT_EQ(4, moved.size());
	EXPECT_EQ(10, moved[0]);
	EXPECT_EQ(20, moved[1]);
	EXPECT_EQ(30, moved[2]);
	EXPECT_EQ(40, moved[3]);
	EXPECT_EQ(0, original.size());
}

TEST(TDynamicVector, move_assignment_works_correctly)
{
	TDynamicVector<int> source(3);
	source[0] = 15; source[1] = 25; source[2] = 35;

	TDynamicVector<int> destination(2);
	destination = std::move(source);

	EXPECT_EQ(3, destination.size());
	EXPECT_EQ(15, destination[0]);
	EXPECT_EQ(25, destination[1]);
	EXPECT_EQ(35, destination[2]);
	EXPECT_EQ(0, source.size());
}

TEST(TDynamicVector, swap_function_exchanges_contents)
{
	TDynamicVector<int> a(2);
	a[0] = 5; a[1] = 10;

	TDynamicVector<int> b(3);
	b[0] = 15; b[1] = 20; b[2] = 25;

	swap(a, b);

	EXPECT_EQ(3, a.size());
	EXPECT_EQ(15, a[0]);
	EXPECT_EQ(20, a[1]);
	EXPECT_EQ(25, a[2]);

	EXPECT_EQ(2, b.size());
	EXPECT_EQ(5, b[0]);
	EXPECT_EQ(10, b[1]);
}