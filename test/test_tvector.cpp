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
	TDynamicVector<int> source(5);
	for (size_t i = 0; i < source.size(); i++) {
		source[i] = i;
	}
	TDynamicVector<int> copy(source);
	EXPECT_EQ(source.size(), copy.size());

	for (size_t i = 0; i < source.size(); i++) {
		EXPECT_EQ(source[i], copy[i]);
	}

}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> source(5);
	for (size_t i = 0; i < source.size(); i++) {
		source[i] = i;
	}
	TDynamicVector<int> copy(source);
	EXPECT_NE(&source[0], &copy[0]);
	source[0] = 111;
	EXPECT_NE(source[0], copy[0]);
	copy[1] = 222;
	EXPECT_NE(source[1], copy[1]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	int a;
	TDynamicVector<int> v(4);
	v[0] = 4;
	a = v[0];
	EXPECT_EQ(4, v[0]);
	EXPECT_EQ(a, 4);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[-1]=4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v[4] = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> source(5);
	for (size_t i = 0; i < source.size(); i++) {
		source[i] = i;
	}
	source = source;
	EXPECT_EQ(source.size(), 5);
	for (size_t i = 0; i < source.size(); i++) {
		EXPECT_EQ(source[i], i);
	}
	
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(5);
	v2 = v1;
	for (size_t i = 0; i < v1.size(); i++) {
		EXPECT_EQ(v1[i], v2[i]);
	}
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(2);
	v2 = v1;
	EXPECT_EQ(v1.size(), v2.size());
	for (size_t i = 0; i < v1.size(); i++) {
		EXPECT_EQ(v1[i], v2[i]);
	}
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(2);
	v2 = v1;
	EXPECT_EQ(v1.size(), v2.size());
	for (size_t i = 0; i < v1.size(); i++) {
		EXPECT_EQ(v1[i], v2[i]);
	}
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(v1);
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(3);
	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	v1 = v1 + 2;
	for (size_t i = 0; i < v1.size(); i++) {
		EXPECT_EQ(v1[i], i + 2);
	}
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	v1 = v1 - 2;
	for (size_t i = 0; i < v1.size(); i++) {
		EXPECT_EQ(v1[i], i - 2);
	}
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	v1 = v1 * 2;
	for (size_t i = 0; i < v1.size(); i++) {
		EXPECT_EQ(v1[i], i * 2);
	}
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(v1);
	TDynamicVector<int> v3(v1.size());
	v3 = v1 + v2;
	for (size_t i = 0; i < v3.size(); i++) {
		EXPECT_EQ(v3[i], i * 2);
	}

}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(3);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(v1);
	TDynamicVector<int> v3(v1.size());
	v3 = v1 - v2;
	for (size_t i = 0; i < v3.size(); i++) {
		EXPECT_EQ(v3[i], 0);
	}
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(3);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(v1);
	int n;
	n = v1 * v2;
	EXPECT_EQ(n, 30);
	
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(3);
	EXPECT_EQ(v1 * v2, 0);
}

