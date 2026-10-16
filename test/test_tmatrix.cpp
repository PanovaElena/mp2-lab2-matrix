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
  TDynamicMatrix<int> m1(5);
  m1[1][1] = 10;
  TDynamicMatrix<int> m2(m1);
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m1(5);
  m1[1][1] = 10;
  TDynamicMatrix<int> m2(m1);
  m2[1][1] = 20;
  EXPECT_NE(m1[1][1], m2[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);
  EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(4);
  m[1][2] = 42;
  EXPECT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(-1).at(0) = 1);
  ASSERT_ANY_THROW(m.at(0).at(-1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(5).at(0) = 1);
  ASSERT_ANY_THROW(m.at(0).at(5) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(5);
  m[0][0] = 42;
  ASSERT_NO_THROW(m = m);
  EXPECT_EQ(42, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(5), m2(5);
  m1[0][0] = 10;
  m2 = m1;
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(2), m2(5);
  m1 = m2;
  EXPECT_EQ(5, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(2), m2(5);
  m2[4][4] = 99;
  m1 = m2;
  EXPECT_EQ(99, m1[4][4]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(3), m2(3);
  m1[0][0] = m2[0][0] = 1;
  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(3);
  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(3), m2(4);
  EXPECT_FALSE(m1 == m2);
  EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2), expected(2);
  m1[0][0] = 1; m1[1][1] = 2;
  m2[0][0] = 3; m2[1][1] = 4;
  expected[0][0] = 4; expected[1][1] = 6;
  
  EXPECT_EQ(m1 + m2, expected);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2), expected(2);
  m1[0][0] = 10; m1[1][1] = 20;
  m2[0][0] = 3; m2[1][1] = 4;
  expected[0][0] = 7; expected[1][1] = 16;
  
  EXPECT_EQ(m1 - m2, expected);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  TDynamicMatrix<int> m(2), expected(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;

  expected[0][0] = 5; expected[0][1] = 10;
  expected[1][0] = 15; expected[1][1] = 20;

  EXPECT_EQ(m * 5, expected);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;

  TDynamicVector<int> v(2), expected(2);
  v[0] = 2; v[1] = 3;

  expected[0] = 8; 
  expected[1] = 18;

  EXPECT_EQ(m * v, expected);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
  TDynamicMatrix<int> m(2);
  TDynamicVector<int> v(3);
  ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(2), expected(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;

  m2[0][0] = 2; m2[0][1] = 0;
  m2[1][0] = 1; m2[1][1] = 2;

  expected[0][0] = 4;  expected[0][1] = 4;
  expected[1][0] = 10; expected[1][1] = 8;

  EXPECT_EQ(m1 * m2, expected);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> m1(2), m2(3);
  ASSERT_ANY_THROW(m1 * m2);
}

TEST(TDynamicMatrix, can_multiply_large_matrices_efficiently)
{
  const int size = 256; 
  TDynamicMatrix<int> m1(size), m2(size);
  
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      m1[i][j] = 1;
      m2[i][j] = 1;
    }
  }
  
  TDynamicMatrix<int> res(size);
  ASSERT_NO_THROW(res = m1 * m2);
  
  EXPECT_EQ(size, res[0][0]);
  EXPECT_EQ(size, res[128][128]);
  EXPECT_EQ(size, res[255][255]);
}

TEST(SparseMatrix, can_convert_plotmatrix_to_crs)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 5;
  m[1][1] = 8; m[1][2] = 2;
  m[2][2] = 3;

  SparseMatrix<int> sm(m);

  std::vector<int> expected_data = {5, 8, 2, 3};
  EXPECT_EQ(sm.getData(), expected_data);

  std::vector<size_t> expected_cols = {0, 1, 2, 2};
  EXPECT_EQ(sm.getCols(), expected_cols);

  std::vector<size_t> expected_rows = {0, 1, 3, 4};
  EXPECT_EQ(sm.getRows(), expected_rows);
}

TEST(SparseMatrix, can_multiply_crs_matrix_by_vector)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 5;
  m[1][1] = 8; m[1][2] = 2;
  m[2][2] = 3;

  SparseMatrix<int> sm(m);

  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> expected(3);
  expected[0] = 5;
  expected[1] = 22;
  expected[2] = 9;

  EXPECT_EQ(sm * v, expected);
}

TEST(SparseMatrix, can_multiply_by_scalar)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 2; m[1][1] = 3;
  SparseMatrix<int> sm(m);
  
  SparseMatrix<int> res = sm * 5;
  std::vector<int> expected_data = {10, 15};
  EXPECT_EQ(res.getData(), expected_data);
}

TEST(SparseMatrix, can_add_matrices)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m2[0][1] = 3; m2[1][1] = 4;
  
  SparseMatrix<int> sm1(m1), sm2(m2);
  SparseMatrix<int> res = sm1 + sm2;
  
  std::vector<int> expected_data = {1, 5, 4}; // 1 на (0,0), 2+3=5 на (0,1), 4 на (1,1)
  std::vector<size_t> expected_cols = {0, 1, 1};
  std::vector<size_t> expected_rows = {0, 2, 3};
  
  EXPECT_EQ(res.getData(), expected_data);
  EXPECT_EQ(res.getCols(), expected_cols);
  EXPECT_EQ(res.getRows(), expected_rows);
}

TEST(SparseMatrix, can_subtract_matrices)
{
  TDynamicMatrix<int> m1(2), m2(2);
  m1[0][0] = 5; m1[0][1] = 2;
  m2[0][0] = 3; m2[1][1] = 4;
  
  SparseMatrix<int> sm1(m1), sm2(m2);
  SparseMatrix<int> res = sm1 - sm2;
  
  std::vector<int> expected_data = {2, 2, -4};
  EXPECT_EQ(res.getData(), expected_data);
}

TEST(SparseMatrix, can_multiply_matrices)
{
  TDynamicMatrix<int> m1(2), m2(2);

  m1[0][0] = 1; m1[0][1] = 2; m1[1][1] = 3;
  
  m2[0][0] = 2; 
  m2[1][0] = 1; m2[1][1] = 4;
  
  SparseMatrix<int> sm1(m1), sm2(m2);
  SparseMatrix<int> res = sm1 * sm2;
  
  std::vector<int> expected_data = {4, 8, 3, 12};
  std::vector<size_t> expected_cols = {0, 1, 0, 1};
  std::vector<size_t> expected_rows = {0, 2, 4};
  
  EXPECT_EQ(res.getData(), expected_data);
  EXPECT_EQ(res.getCols(), expected_cols);
  EXPECT_EQ(res.getRows(), expected_rows);
}