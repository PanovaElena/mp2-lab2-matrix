#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(2));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-2));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(2);
  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  TDynamicMatrix<int> m1(m);
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  TDynamicMatrix<int> m1(m);
  m[0][0] = 10;
  EXPECT_EQ(1, m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);
  EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(2);
  m[0][1] = 1;
  EXPECT_EQ(1, m[0][1]);
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
  ASSERT_ANY_THROW(m[0].at(2) = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[1][1] = 2;
  ASSERT_NO_THROW(m = m);
  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  m1 = m;
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(4)ж
  m = m1;
  EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(3);
  m1[0][0] = 9;
  m1[2][2] = 5;
  m = m1;
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  m[0][0] = 1;
  m[1][1] = 2;
  m1[0][0] = 1;
  m1[1][1] = 2;
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(3);
  EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  m1[0][0] = 5;
  m1[0][1] = 6;
  m1[1][0] = 7;
  m1[1][1] = 8;
  TDynamicMatrix<int> res = m + m1;
  EXPECT_EQ(6, res[0][0]);
  EXPECT_EQ(8, res[0][1]);
  EXPECT_EQ(10, res[1][0]);
  EXPECT_EQ(12, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(3);
  ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  m[0][0] = 2;
  m[0][1] = 4;
  m[1][0] = 6;
  m[1][1] = 8;
  m1[0][0] = 1;
  m1[0][1] = 3;
  m1[1][0] = 5;
  m1[1][1] = 7;
  TDynamicMatrix<int> res = m - m1;
  EXPECT_EQ(1, res[0][0]);
  EXPECT_EQ(1, res[0][1]);
  EXPECT_EQ(1, res[1][0]);
  EXPECT_EQ(1, res[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(3);
  ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> m(2);
  TDynamicVector<int> v(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  v[0] = 5;
  v[1] = 6;
  TDynamicVector<int> res = m * v;
  EXPECT_EQ(17, res[0]);
  EXPECT_EQ(39, res[1]);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicVector<int> v(3);
  ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  m1[0][0] = 5;
  m1[0][1] = 6;
  m1[1][0] = 7;
  m1[1][1] = 8;
  TDynamicMatrix<int> res = m * m1;
  EXPECT_EQ(19, res[0][0]);
  EXPECT_EQ(22, res[0][1]);
  EXPECT_EQ(43, res[1][0]);
  EXPECT_EQ(50, res[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicMatrix<int> m1(3);
  ASSERT_ANY_THROW(m * m1);
}
