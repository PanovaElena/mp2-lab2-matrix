#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  TDynamicVector<int> v(5);

  EXPECT_EQ(v.size(), 5);
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
    EXPECT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
    EXPECT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(10);
    EXPECT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    
    TDynamicVector<int> v(5);
    for (int i = 0; i < 5; ++i) v[i] = i;

    
    TDynamicVector<int> v_copy(v);

    
    EXPECT_EQ(v, v_copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    
    TDynamicVector<int> v(3);
    TDynamicVector<int> v_copy(v);
    
    EXPECT_NE(&v[0], &v_copy[0]);
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
    
    TDynamicVector<int> v(5);

    EXPECT_ANY_THROW(v.at(-1) = 10);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    
    TDynamicVector<int> v(5);

    EXPECT_ANY_THROW(v.at(5) = 10);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    
    TDynamicVector<int> v(3);
    v[0] = 1;

    
    v = v;

    
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v.size(), 3);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    
    TDynamicVector<int> v1(3), v2(3);
    for (int i = 0; i < 3; ++i) v2[i] = i + 1;

    
    v1 = v2;

    
    EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    
    TDynamicVector<int> v1(2), v2(5);

    
    v1 = v2;

    
    EXPECT_EQ(v1.size(), 5);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    
    TDynamicVector<int> v1(2), v2(5);
    for (int i = 0; i < 5; ++i) v2[i] = i;

    
    v1 = v2;

    
    EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    
    TDynamicVector<double> v1(3), v2(3);

    for (int i = 0; i < 3; ++i)
    {
      v1[i] = (double)i + 1e-11;
      v2[i] = (double)i + 1e-12;
    }

    EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    
    TDynamicVector<int> v(3);

    EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    
    TDynamicVector<int> v1(3), v2(4);

    EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    
    TDynamicVector<int> v(3);
    for (int i = 0; i < 3; ++i) v[i] = i;

    
    TDynamicVector<int> result = v + 2;

    
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 4);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    
    TDynamicVector<int> v(3);
    for (int i = 0; i < 3; ++i) v[i] = i + 5;

    
    TDynamicVector<int> result = v - 2;

    
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 5);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    
    TDynamicVector<int> v(3);
    for (int i = 0; i < 3; ++i) v[i] = i + 1;

    
    TDynamicVector<int> result = v * 2;

    
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 6);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    
    TDynamicVector<int> v1(3), v2(3);
    for (int i = 0; i < 3; ++i) { v1[i] = i; v2[i] = i + 1; }

    
    TDynamicVector<int> result = v1 + v2;

    
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 5);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    
    TDynamicVector<int> v1(3), v2(4);

    EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    
    TDynamicVector<int> v1(3), v2(3);
    for (int i = 0; i < 3; ++i) { v1[i] = i + 3; v2[i] = i; }

    
    TDynamicVector<int> result = v1 - v2;

    
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 3);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    
    TDynamicVector<int> v1(3), v2(4);

    EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    
    TDynamicVector<int> v1(3), v2(3);
    for (int i = 0; i < 3; ++i) 
    { 
      v1[i] = i + 1; 
      v2[i] = i + 1; 
    }

    
    int result = v1 * v2;

    
    EXPECT_EQ(result, 14); // 1*1 + 2*2 + 3*3 = 14
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    
    TDynamicVector<int> v1(3), v2(4);

    EXPECT_ANY_THROW(v1 * v2);
}