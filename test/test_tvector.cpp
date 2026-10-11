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
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  TDynamicVector<int> v_1(v);


  EXPECT_EQ(v_1, v);
}
TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  TDynamicVector<int> v1(v);

  v[0] = 10;
  
  EXPECT_NE(&v[0], &v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);

  int bad_index = -1;

  ASSERT_ANY_THROW(v.at(bad_index));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);

  ASSERT_ANY_THROW(v.at(5 ));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);

  v = v;

  ASSERT_NO_THROW(v.at(0));
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v[0], 1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {2,3,4,1,5};
  TDynamicVector<int> v1(arr1, 5);

  v1 = v;

  EXPECT_EQ(v1, v);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {2,3,4,5};
  TDynamicVector<int> v1(arr1, 4);

  v1 = v;

  EXPECT_EQ(v1.size(), 5);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {2,3,4,5};
  TDynamicVector<int> v1(arr1, 4);

  v1 = v;
  EXPECT_EQ(v1, v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {1,2,3,4,5};
  TDynamicVector<int> v1(arr1, 5);

  EXPECT_TRUE(v == v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);

  EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {2,3,4,5};
  TDynamicVector<int> v1(arr1, 4);

  EXPECT_FALSE(v.size() == v1.size());
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {2,3,4,5,6};
  TDynamicVector<int> v1(arr1, 5);

  int scalar = 1;
  v = v + scalar;

  EXPECT_EQ(v,v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {0,1,2,3,4};
  TDynamicVector<int> v1(arr1, 5);

  int scalar = 1;
  v = v - scalar;

  EXPECT_EQ(v,v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {2,4,6,8,10};
  TDynamicVector<int> v1(arr1, 5);

  int scalar = 2;
  v = v * scalar;

  EXPECT_EQ(v,v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {2,3,4,5,6};
  TDynamicVector<int> v1(arr1, 5);
  int arr2[] = {3, 5, 7, 9, 11};
  TDynamicVector<int>  v2(arr2, 5);

  EXPECT_EQ(v + v1, v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {3,4,5,6};
  TDynamicVector<int> v1(arr1, 4);

  ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {2,3,4,5,6};
  TDynamicVector<int> v1(arr1, 5);
  int arr2[] = {-1, -1, -1, -1, -1};
  TDynamicVector<int>  v2(arr2, 5);

  EXPECT_EQ(v - v1, v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {3,4,5,6};
  TDynamicVector<int> v1(arr1, 4);

  ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {1,1,1,1,1};
  TDynamicVector<int> v1(arr1, 5);

  int results = v * v1;
  int true_results = 15;

  EXPECT_EQ(results, true_results);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  int arr[] = {1,2,3,4,5};
  TDynamicVector<int> v(arr, 5);
  int arr1[] = {3,4,5,6};
  TDynamicVector<int> v1(arr1, 4);

  ASSERT_ANY_THROW(v * v1);
}

