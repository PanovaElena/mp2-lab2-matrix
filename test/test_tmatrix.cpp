#include "tmatrix.h"

#include <gtest.h>

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
  TDynamicMatrix<int> m1(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1[i][j] = i * j;
    }
  }
  TDynamicMatrix<int> m2(m1);

  EXPECT_EQ(m1, m2);

}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) {
  TDynamicMatrix<int> m1(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1[i][j] = i * j;
    }
  }
  TDynamicMatrix<int> m2(m1);
  m2[0][0] = 999;

  EXPECT_NE(m1[0][0], m2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m1(3);
  ASSERT_NO_THROW(m1[0].size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m1(3);

  m1[0][0] = 999;

  EXPECT_EQ(m1[0][0], 999);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m1(3);

  EXPECT_THROW(m1.at(-1).at(-2), out_of_range);

}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m1(3);

  EXPECT_THROW(m1.at(MAX_MATRIX_SIZE+1).at(MAX_MATRIX_SIZE+1), out_of_range);

}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m1(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1[i][j] = i * j;
    }
  }
  m1 = m1;
  EXPECT_EQ(m1[0][0], 0);
  EXPECT_EQ(m1[2][2], 4);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1[i][j] = i * j;
    }
  }
  TDynamicMatrix<int> m2(3);
  m2 = m1;
  EXPECT_EQ(m2,m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(3);
  TDynamicMatrix<int> m2(4);

  m2 = m1;

  EXPECT_EQ(m1.size(), m2.size());

}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(3);
  TDynamicMatrix<int> m2(4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      m2[i][j] = i * j;
    }
  }

  m2 = m1;

  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1[i][j] = i * j;
    }
  }
  TDynamicMatrix<int> m2(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m2[i][j] = i * j;
    }
  }

  EXPECT_TRUE(m2 == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m1(3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1[i][j] = i * j;
    }
  }

  EXPECT_TRUE(m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(3);
  TDynamicMatrix<int> m2(4);

  EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++) {
      m1[i][j] = i + j;
      m2[i][j] = 1;
    }

  TDynamicMatrix<int> result = m1 + m2;

  EXPECT_EQ(1, result[0][0]);
  EXPECT_EQ(2, result[0][1]);
  EXPECT_EQ(2, result[1][0]);
  EXPECT_EQ(3, result[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(1);
  for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++) {
      m1[i][j] = i + j;
    }
  m2[0][0] = 1;

  EXPECT_THROW(m1 + m2, out_of_range);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2);
  for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++) {
      m1[i][j] = i + j;
      m2[i][j] = 1;
    }

  TDynamicMatrix<int> result = m1 - m2;

  EXPECT_EQ(-1, result[0][0]);
  EXPECT_EQ(0, result[0][1]);
  EXPECT_EQ(0, result[1][0]);
  EXPECT_EQ(1, result[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) {
  TDynamicMatrix<int> m1(2), m2(1);
  for (size_t i = 0; i < 2; i++)
    for (size_t j = 0; j < 2; j++) {
      m1[i][j] = i + j;
    }
  m2[0][0] = 1;

  EXPECT_THROW(m1 - m2, out_of_range);
}

