#include "tmatrix.h"

#include <gtest.h>
#include <sstream>

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

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; a[0][1] = 2;
  a[1][0] = 3; a[1][1] = 4;

  b[0][0] = 5; b[0][1] = 6;
  b[1][0] = 7; b[1][1] = 8;

  TDynamicMatrix<int> result = a * b;

  EXPECT_EQ(19, result[0][0]);
  EXPECT_EQ(22, result[0][1]);
  EXPECT_EQ(43, result[1][0]);
  EXPECT_EQ(50, result[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_different_size) {
  TDynamicMatrix<int> a(2), b(1);

  EXPECT_THROW(a*b, out_of_range);
}

//тесты на блочное

TEST(TDynamicMatrix, blocked_multiply_gives_same_result_as_usual) {
  const size_t n = 100;
  TDynamicMatrix<int> a(n), b(n);

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) {
      a[i][j] = (i + j) % 7;      // небольшие числа, чтобы избежать переполнения int
      b[i][j] = (i * j + 1) % 5;
    }

  TDynamicMatrix<int> usual = a * b; // сравниваем обычным умножением, т.к. оно уже корректно
  TDynamicMatrix<int> blocked = a.blockMultiply(b);

  EXPECT_EQ(usual, blocked);
}

TEST(TDynamicMatrix, blocked_multiply_cant_multiply_matrices_with_different_sizes) {
  int n = 50;
  int m = 60;
  TDynamicMatrix<int> a(n), b(m);

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) {
      a[i][j] = (i + j) % 7;      // небольшие числа, чтобы избежать переполнения int
      b[i][j] = (i * j + 1) % 5;
    }

  EXPECT_THROW(a.blockMultiply(b), out_of_range);
}

//тесты на медленное умножение

TEST(TDynamicMatrix, slow_multiply_gives_correct_result)
{
  TDynamicMatrix<int> a(3), b(3);
  a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
  a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
  a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

  b[0][0] = 1; b[0][1] = 0; b[0][2] = 2;
  b[1][0] = 0; b[1][1] = 1; b[1][2] = 0;
  b[2][0] = 3; b[2][1] = 0; b[2][2] = 1;

  TDynamicMatrix<int> result = a.slowMultiply(b);

  EXPECT_EQ(10, result[0][0]);
  EXPECT_EQ(2, result[0][1]);
  EXPECT_EQ(5, result[0][2]);
  EXPECT_EQ(22, result[1][0]);
  EXPECT_EQ(5, result[1][1]);
  EXPECT_EQ(14, result[1][2]);
  EXPECT_EQ(34, result[2][0]);
  EXPECT_EQ(8, result[2][1]);
  EXPECT_EQ(23, result[2][2]);
}

TEST(TDynamicMatrix, slow_multiply_by_identity_matrix_does_not_change_matrix)
{
  TDynamicMatrix<int> a(3), e(3);
  for (size_t i = 0; i < 3; i++) {
    e[i][i] = 1;
    for (size_t j = 0; j < 3; j++)
      a[i][j] = i * 3 + j;
  }

  EXPECT_EQ(a, a.slowMultiply(e));
  EXPECT_EQ(a, e.slowMultiply(a));
}

TEST(TDynamicMatrix, slow_multiply_by_zero_matrix_gives_zero_matrix)
{
  TDynamicMatrix<int> a(3), zero(3);
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      a[i][j] = i + j + 1;

  EXPECT_EQ(zero, a.slowMultiply(zero));
}

TEST(TDynamicMatrix, slow_multiply_does_not_change_source_matrices)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; a[0][1] = 2;
  a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 5; b[0][1] = 6;
  b[1][0] = 7; b[1][1] = 8;
  TDynamicMatrix<int> a1(a), b1(b);

  a.slowMultiply(b);

  EXPECT_EQ(a1, a);
  EXPECT_EQ(b1, b);
}

TEST(TDynamicMatrix, cant_slow_multiply_matrices_with_different_size)
{
  TDynamicMatrix<int> a(2), b(1);

  EXPECT_THROW(a.slowMultiply(b), out_of_range);
}

TEST(TDynamicMatrix, slow_multiply_gives_same_result_as_usual_and_blocked)
{
  const size_t n = 100;
  TDynamicMatrix<int> a(n), b(n);

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++) {
      a[i][j] = (i + j) % 7;      // небольшие числа, чтобы избежать переполнения int
      b[i][j] = (i * j + 1) % 5;
    }

  TDynamicMatrix<int> slow = a.slowMultiply(b);

  EXPECT_EQ(slow, a * b);
  EXPECT_EQ(slow, a.blockMultiply(b));
}

// тесты для crs

TEST(SparseMatrix, can_create_matrix_with_positive_size)
{
  ASSERT_NO_THROW(SparseMatrix<int> m(3, 5));
}

TEST(SparseMatrix, cant_create_matrix_with_wrong_size)
{
  ASSERT_ANY_THROW(SparseMatrix<int> m(0, 5));
  ASSERT_ANY_THROW(SparseMatrix<int> m(5, MAX_MATRIX_SIZE + 1));
  ASSERT_ANY_THROW(SparseMatrix<int> m(-5, 5));
}

TEST(SparseMatrix, can_create_from_dense_matrix)
{
  TDynamicMatrix<int> a(3);
  a[0][1] = 2;
  a[1][0] = 3;
  a[2][2] = 4;

  SparseMatrix<int> m(a);

  EXPECT_EQ(3, m.nonZeroCount());
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      EXPECT_EQ(a[i][j], m.at(i, j));
}

TEST(SparseMatrix, copied_matrix_is_equal_to_source_one)
{
  SparseMatrix<int> m1(3, 3);
  m1.set(1, 2, 5);
  SparseMatrix<int> m2(m1);

  EXPECT_EQ(m1, m2);
}

TEST(SparseMatrix, copied_matrix_has_its_own_memory)
{
  SparseMatrix<int> m1(3, 3);
  m1.set(1, 2, 5);
  SparseMatrix<int> m2(m1);

  m2.set(1, 2, 999);

  EXPECT_EQ(5, m1.at(1, 2));
}

TEST(SparseMatrix, can_assign_matrices_of_different_size)
{
  SparseMatrix<int> m1(3, 3), m2(4, 6);
  m1.set(1, 1, 7);

  m2 = m1;

  EXPECT_EQ(m1, m2);
}

TEST(SparseMatrix, can_set_and_get_element)
{
  SparseMatrix<int> m(3, 3);

  m.set(1, 2, 999);

  EXPECT_EQ(999, m.at(1, 2));
  EXPECT_EQ(0, m.at(2, 1));
}

TEST(SparseMatrix, set_zero_removes_element)
{
  SparseMatrix<int> m(3, 3);
  m.set(1, 2, 5);

  m.set(1, 2, 0);

  EXPECT_EQ(0, m.at(1, 2));
  EXPECT_EQ(0, m.nonZeroCount());
}

TEST(SparseMatrix, throws_when_index_is_out_of_bounds)
{
  SparseMatrix<int> m(3, 4);

  EXPECT_THROW(m.at(3, 0), out_of_range);
  EXPECT_THROW(m.at(0, 4), out_of_range);
  EXPECT_THROW(m.set(3, 0, 1), out_of_range);
}

TEST(SparseMatrix, compare_equal_matrices_return_true)
{
  SparseMatrix<int> m1(3, 3), m2(3, 3);
  m1.set(0, 1, 5);
  m2.set(0, 1, 5);

  EXPECT_TRUE(m1 == m2);
}

TEST(SparseMatrix, matrices_with_different_size_are_not_equal)
{
  SparseMatrix<int> m1(3, 3), m2(3, 4);

  EXPECT_FALSE(m1 == m2);
}

TEST(SparseMatrix, matrices_with_different_elements_are_not_equal)
{
  SparseMatrix<int> m1(3, 3), m2(3, 3);
  m1.set(0, 1, 5);
  m2.set(1, 0, 5);

  EXPECT_TRUE(m1 != m2);
}

TEST(SparseMatrix, can_multiply_matrix_by_scalar)
{
  SparseMatrix<int> m(3, 3);
  m.set(0, 2, 1);
  m.set(1, 0, 3);

  SparseMatrix<int> result = m * 3;

  EXPECT_EQ(3, result.at(0, 2));
  EXPECT_EQ(9, result.at(1, 0));
  EXPECT_EQ(2, result.nonZeroCount());
}

TEST(SparseMatrix, can_add_matrices_with_equal_size)
{
  SparseMatrix<int> m1(3, 3), m2(3, 3);
  m1.set(0, 0, 1); m1.set(1, 1, 2);
  m2.set(1, 1, 3); m2.set(2, 2, 4);

  SparseMatrix<int> result = m1 + m2;

  EXPECT_EQ(1, result.at(0, 0));
  EXPECT_EQ(5, result.at(1, 1));
  EXPECT_EQ(4, result.at(2, 2));
  EXPECT_EQ(3, result.nonZeroCount());
}

TEST(SparseMatrix, sum_with_opposite_matrix_is_empty)
{
  SparseMatrix<int> m(3, 3);
  m.set(0, 0, 1);
  m.set(1, 2, 2);

  SparseMatrix<int> result = m + m * (-1);

  EXPECT_EQ(SparseMatrix<int>(3, 3), result);
}

TEST(SparseMatrix, cant_add_matrices_with_not_equal_size)
{
  SparseMatrix<int> m1(3, 3), m2(3, 4);

  EXPECT_THROW(m1 + m2, out_of_range);
}

TEST(SparseMatrix, can_subtract_matrices_with_equal_size)
{
  SparseMatrix<int> m1(3, 3), m2(3, 3);
  m1.set(0, 0, 1); m1.set(1, 1, 2);
  m2.set(1, 1, 3); m2.set(2, 2, 4);

  SparseMatrix<int> result = m1 - m2;

  EXPECT_EQ(1, result.at(0, 0));
  EXPECT_EQ(-1, result.at(1, 1));
  EXPECT_EQ(-4, result.at(2, 2));
}

TEST(SparseMatrix, cant_subtract_matrices_with_not_equal_size)
{
  SparseMatrix<int> m1(3, 3), m2(3, 4);

  EXPECT_THROW(m1 - m2, out_of_range);
}

TEST(SparseMatrix, can_multiply_matrix_by_vector)
{
  SparseMatrix<int> m(3, 3);
  m.set(0, 0, 1); m.set(0, 2, 2);
  m.set(1, 1, 3);
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> result = m * v;

  EXPECT_EQ(7, result[0]);
  EXPECT_EQ(6, result[1]);
  EXPECT_EQ(0, result[2]);
}

TEST(SparseMatrix, cant_multiply_matrix_by_vector_with_different_size)
{
  SparseMatrix<int> m(3, 4);
  TDynamicVector<int> v(3);

  EXPECT_THROW(m * v, out_of_range);
}

TEST(SparseMatrix, can_output_matrix)
{
  SparseMatrix<int> m(2, 2);
  m.set(0, 0, 1);
  m.set(1, 1, 2);
  ostringstream out; //поток вывода, по сути буфер в памяти, который не выводит в консоль, можем сравнить

  out << m;

  EXPECT_EQ("1 0 \n0 2 \n", out.str());
}