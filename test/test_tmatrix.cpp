#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(7));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 3));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-100));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(50);
  ASSERT_NO_THROW(TDynamicMatrix<int> matrix1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> matrix1(50);
  matrix1[1][6] = 7;
  TDynamicMatrix<int> matrix2(matrix1);
  EXPECT_EQ(matrix1, matrix2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> matrix1(12);
  matrix1[2][2] = 1;
  TDynamicMatrix<int> matrix2(matrix1);
  matrix1[2][2] = 99;
  EXPECT_NE(matrix1[2][2], matrix2[2][2]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(100);
  EXPECT_EQ(100, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[1][2] = 42;
  EXPECT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(9);
  ASSERT_ANY_THROW(m.at(9));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 5;
  ASSERT_NO_THROW(m = m);
  EXPECT_EQ(5, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> matrix1(3), matrix2(3);
  matrix1[0][0] = 15;
  matrix2 = matrix1;
  EXPECT_EQ(15, matrix2[0][0]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> matrix1(3), matrix2(5);
  matrix2 = matrix1;
  EXPECT_EQ(3, matrix2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> matrix1(3), matrix2(5);
  matrix1[0][0] = 9;
  matrix2 = matrix1;
  EXPECT_EQ(9, matrix2[0][0]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> matrix1(3), matrix2(3);
  matrix1[1][1] = 5;
  matrix2[1][1] = 5;
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(3);
  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> matrix1(3), matrix2(5);
  EXPECT_TRUE(matrix1 != matrix2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> matrix1(2), matrix2(2);
  matrix1[0][0] = 1; matrix2[0][0] = 2;
  matrix1[1][1] = 3; matrix2[1][1] = 4;
  TDynamicMatrix<int> result = matrix1 + matrix2;
  EXPECT_EQ(3, result[0][0]);
  EXPECT_EQ(7, result[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> matrix1(2), matrix2(3);
  ASSERT_ANY_THROW(matrix1 + matrix2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> matrix1(2), matrix2(2);
  matrix1[0][0] = 5; matrix2[0][0] = 2;
  matrix1[1][1] = 10; matrix2[1][1] = 4;
  TDynamicMatrix<int> result = matrix1 - matrix2;
  EXPECT_EQ(3, result[0][0]);
  EXPECT_EQ(6, result[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> matrix1(2), matrix2(3);
  ASSERT_ANY_THROW(matrix1 - matrix2);
}