#include "tmatrix.h"

#include <cstddef>
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
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  TDynamicMatrix<int> m1(m);
  
  EXPECT_EQ(m1, m);
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

  EXPECT_NE(&m[0][0], &m1[0][0]);
 }

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(2);
  
  int true_size = 2;

  EXPECT_EQ(m.size(), true_size);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;

  EXPECT_EQ(m[0][0], 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  int bad_index = -1;
  ASSERT_ANY_THROW(m.at(bad_index));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  int bad_index = 2;

  ASSERT_ANY_THROW(m.at(bad_index));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  m = m;

  ASSERT_NO_THROW(m.at(0));
  EXPECT_EQ(m.size(), 2);
  EXPECT_EQ(m[0][0], 1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  TDynamicMatrix<int> m1(2);

  m1 = m;

  EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  TDynamicMatrix<int> m1(3);

  m1 = m;

  EXPECT_EQ(m1.size(), 2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  TDynamicMatrix<int> m1(3);

  m1 = m;

  EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[1][0] = 3;
  m1[1][1] = 4;

  EXPECT_TRUE(m1 == m);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;

  TDynamicMatrix<int> m1(1);
  m1[0][0] = 1;

  EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 1;
  m1[0][1] = 2;
  m1[1][0] = 3;
  m1[1][1] = 4;
  TDynamicMatrix<int> m2(2);
  m2[0][0] = 10;
  m2[0][1] = 20;
  m2[1][0] = 30;
  m2[1][1] = 40;
  TDynamicMatrix<int> m3(2);
  m3[0][0] = 11;
  m3[0][1] = 22;
  m3[1][0] = 33;
  m3[1][1] = 44;

  EXPECT_EQ(m1 + m2, m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);

  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 10;
  m1[0][1] = 20;
  m1[1][0] = 30;
  m1[1][1] = 40;
  TDynamicMatrix<int> m2(2);
  m2[0][0] = 1;
  m2[0][1] = 2;
  m2[1][0] = 3;
  m2[1][1] = 4;
  TDynamicMatrix<int> m3(2);
  m3[0][0] = 9;
  m3[0][1] = 18;
  m3[1][0] = 27;
  m3[1][1] = 36;

  EXPECT_EQ(m1 - m2, m3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);

  ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_smaller_than_block_size)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 10;
  m1[0][1] = 20;
  m1[1][0] = 30;
  m1[1][1] = 40;
  TDynamicMatrix<int> m2(2);
  m2[0][0] = 1;
  m2[0][1] = 2;
  m2[1][0] = 3;
  m2[1][1] = 4;

  EXPECT_EQ(m1.blockMult(m2), m1 * m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_exact_block_size){
  TDynamicMatrix<int> m1(64), m2(64);

  for (size_t i = 0; i < 64; i++){
    for (size_t j = 0; j < 64; j++){
      m1[i][j] = i + 2 + j;
      m2[i][j] = i + 10 * j - 5;
    }
  }

  EXPECT_EQ(m1.blockMult(m2), m1 * m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_size_not_divisible_by_block_size){
  TDynamicMatrix<int> m1(70), m2(70);

  for (size_t i = 0; i < 70; i++){
    for (size_t j = 0; j < 70; j++){
      m1[i][j] = i + 2 + j;
      m2[i][j] = i + 10 * j - 5;
    }
  }

  EXPECT_EQ(m1.blockMult(m2), m1 * m2);
}