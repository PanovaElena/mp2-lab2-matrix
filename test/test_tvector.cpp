#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)//+
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)//+
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, can_create_vector_with_max_size)//+
{
    ASSERT_NO_THROW(TVector<int> v(MAX_VECTOR_SIZE));
}

TEST(TVector, can_create_vector_with_zero_size)//+
{
    ASSERT_NO_THROW(TVector<int> v(0));
}

TEST(TVector, throws_when_create_vector_with_negative_length)//+
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)//+
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)//+
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)//+?
{
    const int size = 4;
    TVector<int> v1(size);
    for (size_t i=0; i < size; i++) {
        v1[i] = i;
    }
    TVector<int> v2(v1);
    EXPECT_EQ(v1, v2);
}

TEST(TVector, copied_vector_has_its_own_memory)//+
{
    TVector<int> v1;
    TVector<int> v2;
    EXPECT_NE(&v2, &v1);
}

TEST(TVector, can_get_size)//+
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)//+
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)//+
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)//+
{
    TVector<int> v;
    ASSERT_ANY_THROW(v[-3]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)//+
{
    TVector<int> v(MAX_VECTOR_SIZE);
    ASSERT_ANY_THROW(v[MAX_VECTOR_SIZE+1]);
}

TEST(TVector, can_assign_vector_to_itself)//+
{
    TVector<int> v1(3);
    v1 = v1;
    EXPECT_EQ(v1,v1);
    ASSERT_NO_THROW(v1=v1);
}

TEST(TVector, can_assign_vectors_of_equal_size)//+
{
    const int size = 3;
    TVector<int> v1(size), v2(size);
    for (size_t i = 0; i < size; i++)
        v1[i] = i;
    v2 = v1;
    EXPECT_EQ(v2, v1);
    ASSERT_NO_THROW(v2 = v1);
}

TEST(TVector, assign_operator_change_vector_size)//+
{
    const int size1 = 2, size2 = 5;
    TVector<int> v1(size1), v2(size2);
    for (size_t i = 0; i < size1; i++)
        v1[i] = i;
    v2 = v1;

    EXPECT_EQ(2, v2.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)//+
{
    const int size1 = 2, size2 = 5;
    TVector<int> v1(size1), v2(size2);
    for (size_t i = 0; i < size1; i++)
        v1[i] = i;
    v2 = v1;

    EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_equal_vectors_return_true)//+?
{
    TVector<int> v1(2), v2(2);
    for (size_t i = 0; i < v1.GetSize(); i++)
        v1[i] = 3;
    v2 = v1;
    EXPECT_EQ(v1, v2);
}

TEST(TVector, compare_vector_with_itself_return_true)//+?
{
    TVector<int> v;
    for (size_t i = 0; i < v.GetSize(); i++){
        v[i] = 1;
    }
    EXPECT_EQ(v,v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)//+
{
    const int size1 = 5, size2 = 2;
    TVector<int> v1(size1);
    TVector<int> v2(size2);
    EXPECT_NE(v1, v2);
}

TEST(TVector, can_add_scalar_to_vector)//+
{
    int scalar = 3;
    const int size = 5;
    TVector<int> v1(size), v2(size);

    for (size_t i = 0; i < v1.GetSize(); i++) {
        v1[i] = 5;
        v2[i] = 2;
    }
    EXPECT_EQ(v1, v2+scalar);
    ASSERT_NO_THROW(v2 + scalar);
}

TEST(TVector, can_subtract_scalar_from_vector)//+
{
    int scalar = 3;
    const int size = 5;
    TVector<int> v1(size),v2(size);

    for (size_t i = 0; i < v1.GetSize(); i++) {
        v1[i] = 5;
        v2[i] = 2;
    }
    EXPECT_EQ(v1-scalar, v2);
    ASSERT_NO_THROW(v1 - scalar);
}

TEST(TVector, can_multiply_scalar_by_vector)//+
{
    int scalar = 3;
    const int size = 5;
    TVector<int> v1(size), v2(size);

    for (size_t i = 0; i < v1.GetSize(); i++) {
        v1[i] = 6;
        v2[i] = 2;
    }
    EXPECT_EQ(v1, v2*scalar);
    ASSERT_NO_THROW(v2 *scalar);
}

TEST(TVector, can_add_vectors_with_equal_size)//+
{
    const int size = 5;
    TVector<int> v1(size), v2(size), v3(size);

    for (size_t i = 0; i < v1.GetSize(); i++) {
        v1[i] = 6;
        v2[i] = 2;
        v3[i] = 8;
    }
    EXPECT_EQ(v3, v1+v2);
    ASSERT_NO_THROW(v1 + v2);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
    const int size1 = 5, size2 = 3;
    TVector<int> v1(size1), v2(size2);
    ASSERT_ANY_THROW(v1+v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
    const int size = 5;
    TVector<int> v1(size), v2(size), v3(size);

    for (size_t i = 0; i < v1.GetSize(); i++) {
        v1[i] = 6;
        v2[i] = 2;
        v3[i] = 8;
    }
    EXPECT_EQ(v1, v3 - v2);
    ASSERT_NO_THROW(v3 - v2);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
    const int size1 = 5, size2 = 3;
    TVector<int> v1(size1), v2(size2);
    ASSERT_ANY_THROW(v1 - v2);

}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
    int scalar=2;
    const int size = 2;
    TVector<int> v1(size), v2(size);

    for (size_t i = 0; i < size; i++) {
        v1[i] = i;
        v2[i] = i+1;
    }
    EXPECT_EQ(scalar, v1 * v2);
    ASSERT_NO_THROW(v1 * v2);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
    const int size1 = 5, size2 = 3;
    TVector<int> v1(size1), v2(size2);
    ASSERT_ANY_THROW(v1 * v2);
}

