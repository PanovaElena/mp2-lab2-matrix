#include "tmatrix.h"

#include <gtest.h>


template<typename T>
void FillMatrix(TDynamicMatrix<T>& m) {
    size_t size = m.size();
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < size; ++j)
            m[i][j] = static_cast<T>(i * size + j + 1);
}

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(3);
  FillMatrix(m);
  TDynamicMatrix<int> m_copy(m);
  ASSERT_EQ(m, m_copy);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(2);
  FillMatrix(m);
  TDynamicMatrix<int> m_copy(m);
  m_copy[0][0] = 100;
  ASSERT_NE(m[0][0], m_copy[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);
  ASSERT_EQ(m.size(), 4);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(2);
  m[1][1] = 42;
  ASSERT_EQ(m[1][1], 42);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(2);
  ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(2);
  ASSERT_ANY_THROW(m.at(2));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m = m;
  ASSERT_EQ(m[0][0], 1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][0] = 5;
  m2 = m1;
  ASSERT_EQ(m2, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  m1 = m2;
  ASSERT_EQ(m1.size(), 3);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  m1 = m2;
  ASSERT_EQ(m1.size(), 3);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(2), m2(2);
  FillMatrix(m1);
  FillMatrix(m2);
  ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(2);
  ASSERT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  FillMatrix(m1);
  FillMatrix(m2);
  TDynamicMatrix<int> m3 = m1 + m2;
  ASSERT_EQ(m3[0][0], m1[0][0] + m2[0][0]);
  ASSERT_EQ(m3[1][1], m1[1][1] + m2[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  FillMatrix(m1);
  FillMatrix(m2);
  TDynamicMatrix<int> m3 = m1 - m2;
  ASSERT_EQ(m3[0][0], 0);
  ASSERT_EQ(m3[1][1], 0);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_ANY_THROW(m1 - m2);
}

