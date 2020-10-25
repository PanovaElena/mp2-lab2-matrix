#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, can_create_vector_with_max_size)
{
    ASSERT_NO_THROW(TVector<int> v(MAX_VECTOR_SIZE));
}

TEST(TVector, can_create_vector_with_zero_size)
{
    ASSERT_NO_THROW(TVector<int> v(0));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
  const int size = 3, si = 0;
  TVector<int> v1(size, si);
  for (int i = 0; i < size; i++)
      v1[i] = i;
  TVector<int> v2(v1);

  EXPECT_EQ(v1, v2);       //ожидается получить значения вектора v1 в переданном векторе v2
}

TEST(TVector, copied_vector_has_its_own_memory)
{
  const int size = 1, si = 0;
  TVector<int> v1(size, si);
  v1[0] = 5;
  TVector<int> v2(v1);

  EXPECT_NE(&v1[0], &v2[0]);
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;
  ASSERT_NO_THROW(v[0] = 4);
  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
  TVector<int> v(10, 0);

  ASSERT_ANY_THROW(v[-2]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
  TVector<int> v(10, 0);

  ASSERT_ANY_THROW(v[14]);
}

TEST(TVector, can_assign_vector_to_itself)
{
    const int size = 5, si = 0;
    TVector<int> v1(size, si);
    TVector<int> v2(size, si);
    for (int i = 0; i < size; i++)
    {
        v1[i] = i;
        v2[i] = i;
    }
    v1 = v1;

    ASSERT_NO_THROW(v1 = v1);
    EXPECT_EQ(v2, v1);  //проверка, что вектор v1 остался равен самому себе
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
    const int size = 12, si = 0;
    TVector<int> v1(size, si), v2(size, si);
    for (int i = 0; i < size; i++)
    {
      v1[i] = 2 * i;
    }
    v2 = v1;

    EXPECT_EQ(2, v2[1]);
    EXPECT_EQ(18, v2[9]);
    EXPECT_EQ(22, v2[11]);
}

TEST(TVector, assign_operator_change_vector_size)
{
    const int size1 = 2, size2 = 5, si=0;
    TVector<int> v1(size1, si), v2(size2, si);
    for (int i = 0; i < size1; i++)
    {
        v1[i]=i;
    }
    v2 = v1;

    EXPECT_EQ(2, v2.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
    const int size1 = 12, size2 = 4, si = 0;
    TVector<int> v1(size1, si), v2(size2, si);
    for (int i = 0; i < size1; i++)
    {
        v1[i] = 2 * i;
    }
    v2 = v1;

    EXPECT_EQ(2, v2[1]);
    EXPECT_EQ(18, v2[9]);
    EXPECT_EQ(22, v2[11]);
}

TEST(TVector, compare_equal_vectors_return_true)
{
    const int size = 2, si = 0;
    TVector<int> v1(size, si), v2(size, si);
    for (int i = 0; i < size; i++)
        v1[i] = 4 * i;
    v2 = v1;

    EXPECT_EQ(v1, v2);
    EXPECT_EQ(true, v1 == v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
    const int size = 2, si = 0;
    TVector<int> v1(size, si);
    for (int i = 0; i < size; i++)
        v1[i] = 4 * i;

    EXPECT_EQ(v1, v1);
    EXPECT_EQ(true, v1 == v1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
    const int size1 = 12, size2 = 4, si = 0;
    TVector<int> v1(size1, si), v2(size2, si);

    EXPECT_NE(v1, v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
    const int size = 3, si = 0;
    int a = 7;
    TVector<int> v1(size, si), v2(size, si);
    for (int i = 0; i < size; i++)
        v2[i] = 4 * i;  //0 4 8
    v1 = v2 + a;    //7 11 15
    v2[0] = 7; v2[1] = 11; v2[2] = 15;

    EXPECT_EQ(v2, v1);  //с v2 сравниваем v1
}

TEST(TVector, can_subtract_scalar_from_vector)
{
    const int size = 3, si = 0;
    int a = 4;
    TVector<int> v1(size, si), v2(size, si);
    for (int i = 0; i < size; i++)
        v2[i] = 9 * i;  //0 9 18
    v1 = v2 - a;    //-4 5 14
    v2[0] = -4; v2[1] = 5; v2[2] = 14;

    EXPECT_EQ(v2, v1);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
    const int size = 3, si = 0;
    int a = 6;
    TVector<int> v1(size, si), v2(size, si);
    for (int i = 0; i < size; i++)
        v2[i] = 2 * i +3;   //3 5 7
    v1 = v2 * a;    //18 30 42
    v2[0] = 18; v2[1] = 30; v2[2] = 42;

    EXPECT_EQ(v2, v1);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
    const int size = 4, si=0;
    TVector<int> v1(size, si), v2(size, si), v3(size, si), v4(size, si);
    for (int i = 0; i < size; i++)
    {
        v1[i] = i;
        v2[i] = 2 * i;
        v4[i] = 3 * i;
    }
    v3 = v1 + v2;

    EXPECT_EQ(v4, v3);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
    const int size1 = 4, size2 = 7, si = 0;
    TVector<int> v1(size1, si), v2(size2, si), v3(size1, si);
    for (int i = 0; i < size1; i++)
        v1[i] = i;
    for (int i=0; i<size2; i++)
        v2[i] = 2 * i;

    ASSERT_ANY_THROW(v3=v1+v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
    const int size = 4, si = 0;
    TVector<int> v1(size, si), v2(size, si), v3(size, si), v4(size, si);
    for (int i = 0; i < size; i++)
    {
        v1[i] = 3 * i;
        v2[i] = 2 * i;
        v4[i] = i;
    }
    v3 = v1 - v2;

    EXPECT_EQ(v4, v3);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
    const int size1 = 4, size2 = 7, si = 0;
    TVector<int> v1(size1, si), v2(size2, si), v3(size1, si);
    for (int i = 0; i < size1; i++)
        v1[i] = i;
    for (int i = 0; i < size2; i++)
        v2[i] = 2 * i;
    ASSERT_ANY_THROW(v3 = v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
    const int size = 4, si = 0;
    TVector<int> v1(size, si), v2(size, si);
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        v1[i] = i + 2;  //2 3 4 5 
        v2[i] = 2 * i - 1;   //-1 1 3 5  
    }
    result = v1 * v2;   //должен быть равен -2 + 3 + 12 + 25 = 38

    EXPECT_EQ(38, result);
    ASSERT_NO_THROW(v1 * v2);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
    const int size1 = 4, size2 = 7, si = 0;
    TVector<int> v1(size1, si), v2(size2, si);
    int result = 0;
    for (int i = 0; i < size1; i++)
        v1[i] = i + 2;  
    for (int i=0; i<size2; i++)
        v2[i] = 2 * i - 1;  
    
    ASSERT_ANY_THROW(result = v1 * v2);
}