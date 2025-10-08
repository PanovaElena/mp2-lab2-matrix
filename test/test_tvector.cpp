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
  
  TDynamicVector<int> v1(v);
  
  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(3);
  v[0] = 1;
  
  TDynamicVector<int> v1(v);
  v[0] = 10;
  
  EXPECT_NE(v[0], v1[0]);
  EXPECT_EQ(1, v1[0]);
  EXPECT_EQ(0, v1[1]);
  EXPECT_EQ(0, v1[2]);
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

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(3);

  ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(3);

  ASSERT_ANY_THROW(v.at(3));
  ASSERT_ANY_THROW(v.at(10));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  ASSERT_NO_THROW(v = v);
  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(0, v[1]);
  EXPECT_EQ(0, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(3);
  v2[0] = 4;
  
  v1 = v2;
  
  EXPECT_EQ(v1, v2);
  EXPECT_EQ(4, v1[0]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(5);
  v2[0] = 4;
  
  size_t old_size = v1.size();
  v1 = v2;
  
  EXPECT_NE(old_size, v1.size());
  EXPECT_EQ(5, v1.size());
  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v1(2);
  
  TDynamicVector<int> v2(4);
  v2[0] = 3;
  ASSERT_NO_THROW(v1 = v2);
  
  EXPECT_EQ(4, v1.size());
  EXPECT_EQ(v1, v2);
  EXPECT_EQ(3, v1[0]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v1(3);

  TDynamicVector<int> v2(3);
  
  EXPECT_TRUE(v1 == v2);
  EXPECT_FALSE(v1 != v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(3);
  
  EXPECT_TRUE(v == v);
  EXPECT_FALSE(v != v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(2);
  
  EXPECT_FALSE(v1 == v2);
  EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 1;
  
  TDynamicVector<int> result = v + 5;
  
  EXPECT_EQ(6, result[0]);
  EXPECT_EQ(3, result.size());
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 5;
  
  TDynamicVector<int> result = v - 2;
  
  EXPECT_EQ(3, result[0]);
  EXPECT_EQ(3, result.size());
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 2;
  
  TDynamicVector<int> result = v * 3;
  
  EXPECT_EQ(6, result[0]);
  EXPECT_EQ(3, result.size());
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3);
  v1[0] = 1;
  
  TDynamicVector<int> v2(3);
  v2[0] = 4;
  
  TDynamicVector<int> result = v1 + v2;
  
  EXPECT_EQ(5, result[0]);
  EXPECT_EQ(3, result.size());
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(2);
  
  ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3);
  v1[0] = 5;
  
  TDynamicVector<int> v2(3);
  v2[0] = 1;
  
  TDynamicVector<int> result = v1 - v2;
  
  EXPECT_EQ(4, result[0]);
  EXPECT_EQ(3, result.size());
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(2);
  
  ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3);
  v1[0] = 1;
  
  TDynamicVector<int> v2(3);
  v2[0] = 4;
  
  int result = v1 * v2;
  EXPECT_EQ(4, result);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3);
  TDynamicVector<int> v2(2);
  
  ASSERT_ANY_THROW(v1 * v2);
}

TEST(TDynamicVector, can_move_construct_vector)
{
  TDynamicVector<int> v1(3);
  v1[0] = 10;
  TDynamicVector<int> v2(std::move(v1));
  EXPECT_EQ(3, v2.size());
  EXPECT_EQ(10, v2[0]);
  EXPECT_EQ(0, v1.size());
}

TEST(TDynamicVector, can_move_assign_vector)
{
  TDynamicVector<int> v1(3);
  v1[0] = 1;
  TDynamicVector<int> v2(2);
  v2 = std::move(v1);
  EXPECT_EQ(3, v2.size());
  EXPECT_EQ(1, v2[0]);
  EXPECT_EQ(0, v1.size());
}

