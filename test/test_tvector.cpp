#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> vector(555));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> vector(MAX_VECTOR_SIZE + 3));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> vector(-55));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> vector(123);
  ASSERT_NO_THROW(TDynamicVector<int> vector1(vector));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> vector1(7);
  vector1[0] = 10;
  vector1[4] = 15;
  TDynamicVector<int> vector2(vector1);
  EXPECT_EQ(vector1, vector2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> vector1(5);
  vector1[0] = 10;
  TDynamicVector<int> vector2(vector1);
  vector1[0] = 20;
  EXPECT_NE(vector1[0], vector2[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> vector(4);
  EXPECT_EQ(4, vector.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> vector(4);
  vector[0] = 4;
  EXPECT_EQ(4, vector[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> vector(5);
  ASSERT_ANY_THROW(vector.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> vector(5);
  ASSERT_ANY_THROW(vector.at(5));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> vector(5);
  vector[0] = 7;
  ASSERT_NO_THROW(vector = vector);
  EXPECT_EQ(7, vector[0]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> vector1(5), vector2(5);
  vector1[0] = 8;
  vector2 = vector1;
  EXPECT_EQ(8, vector2[0]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> vector1(5), vector2(10);
  vector2 = vector1;
  EXPECT_EQ(5, vector2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> vector1(5), vector2(10);
  vector1[0] = 42;
  vector2 = vector1;
  EXPECT_EQ(42, vector2[0]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> vector1(5), vector2(5);
  vector1[2] = 3;
  vector2[2] = 3;
  EXPECT_TRUE(vector1 == vector2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> vector(5);
  EXPECT_TRUE(vector == vector);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> vector1(5), vector2(10);
  EXPECT_TRUE(vector1 != vector2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> vector(3);
  vector[0] = 1; vector[1] = 2; vector[2] = 3;
  TDynamicVector<int> result = vector + 5;
  EXPECT_EQ(6, result[0]);
  EXPECT_EQ(7, result[1]);
  EXPECT_EQ(8, result[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> vector(3);
  vector[0] = 5; vector[1] = 6; vector[2] = 7;
  TDynamicVector<int> result = vector - 2;
  EXPECT_EQ(3, result[0]);
  EXPECT_EQ(4, result[1]);
  EXPECT_EQ(5, result[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> vector(3);
  vector[0] = 2; vector[1] = 3; vector[2] = 4;
  TDynamicVector<int> result = vector * 3;
  EXPECT_EQ(6, result[0]);
  EXPECT_EQ(9, result[1]);
  EXPECT_EQ(12, result[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> vector1(3), vector2(3);
  vector1[0] = 1; vector2[0] = 9;
  vector1[1] = 2; vector2[1] = 8;
  TDynamicVector<int> result = vector1 + vector2;
  EXPECT_EQ(10, result[0]);
  EXPECT_EQ(10, result[1]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> vector1(7), vector2(5);
  ASSERT_ANY_THROW(vector1 + vector2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> vector1(6), vector2(6);
  vector1[0] = 10; vector2[0] = 3;
  TDynamicVector<int> result = vector1 - vector2;
  EXPECT_EQ(7, result[0]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> vector1(3), vector2(5);
  ASSERT_ANY_THROW(vector1 - vector2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> vector1(3), vector2(3);
  vector1[0] = 2; vector2[0] = 3;
  vector1[1] = 4; vector2[1] = 5;
  vector1[2] = 6; vector2[2] = 2;
  int dot_product = vector1 * vector2;
  EXPECT_EQ(38, dot_product);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> vector1(3), vector2(15);
  ASSERT_ANY_THROW(vector1 * vector2);
}