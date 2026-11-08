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
  TDynamicMatrix<int> m(5);
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      m[i][j] = i * 5 + j;

  TDynamicMatrix<int> m1(m);
  EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(5);
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      m[i][j] = i * 5 + j;

  TDynamicMatrix<int> m1(m);
  m[0][0] = 999;
  EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(7);
  EXPECT_EQ(static_cast<size_t>(7), m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(5);
  m[2][3] = 42;
  EXPECT_EQ(42, m[2][3]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(100));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(5);
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      m[i][j] = i * 5 + j;

  m = m;
  ASSERT_NO_THROW(
    for (size_t i = 0; i < m.size(); i++)
      for (size_t j = 0; j < m.size(); j++) {
        if (m[i][j] != i * 5 + j)
          ADD_FAILURE();
      }
  );
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(5), m2(5);
  for (size_t i = 0; i < m1.size(); i++)
    for (size_t j = 0; j < m1.size(); j++) {
      m1[i][j] = i + j;
      m2[i][j] = i * j;
    }

  m1 = m2;
  for (size_t i = 0; i < m1.size(); i++)
    for (size_t j = 0; j < m1.size(); j++)
      EXPECT_EQ(i * j, m1[i][j]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(3), m2(5);
  m1 = m2;
  EXPECT_EQ(static_cast<size_t>(5), m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(3), m2(5);
  for (size_t i = 0; i < m2.size(); i++)
    for (size_t j = 0; j < m2.size(); j++)
      m2[i][j] = i * 10 + j;

  m1 = m2;
  EXPECT_EQ(static_cast<size_t>(5), m1.size());
  for (size_t i = 0; i < m1.size(); i++)
    for (size_t j = 0; j < m1.size(); j++)
      EXPECT_EQ(i * 10 + j, m1[i][j]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(4), m2(4);
  for (size_t i = 0; i < m1.size(); i++)
    for (size_t j = 0; j < m1.size(); j++) {
      m1[i][j] = i * 4 + j;
      m2[i][j] = i * 4 + j;
    }
  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m(5);
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      m[i][j] = i + j;
  EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(3), m2(5);
  EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(3), b(3), expected(3);
  for (size_t i = 0; i < a.size(); i++)
    for (size_t j = 0; j < a.size(); j++) {
      a[i][j] = i * 3 + j;
      b[i][j] = (i * 3 + j) * 10;
      expected[i][j] = (i * 3 + j) * 11;
    }

  TDynamicMatrix<int> res = a + b;
  EXPECT_EQ(expected, res);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(3), b(5);
  ASSERT_ANY_THROW(TDynamicMatrix<int> res = a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(3), b(3), expected(3);
  for (size_t i = 0; i < a.size(); i++)
    for (size_t j = 0; j < a.size(); j++) {
      a[i][j] = (i * 3 + j) + 100;
      b[i][j] = i * 3 + j;
      expected[i][j] = 100;
    }

  TDynamicMatrix<int> res = a - b;
  EXPECT_EQ(expected, res);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(3), b(5);
  ASSERT_ANY_THROW(TDynamicMatrix<int> res = a - b);
}

TEST(TDynamicMatrix, can_read_matrix)
{
  TDynamicMatrix<int> m(3);
  TDynamicMatrix<int> expected(3);
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      expected[i][j] = i * 3 + j + 1;

  std::stringstream sstr;
  sstr << "1 2 3 4 5 6 7 8 9\n";
  sstr >> m;

  EXPECT_EQ(expected, m);
}

TEST(TDynamicMatrix, can_write_matrix)
{
  TDynamicMatrix<int> m(3);
  int cnt = 1;
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      m[i][j] = cnt++;
  std::string expected = "1 2 3 4 5 6 7 8 9 ";

  std::stringstream sstr;
  sstr << m;

  std::string result = sstr.str();
  EXPECT_EQ(expected, result);
}

// --- Дополнительные тесты: умножение ---

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
  TDynamicMatrix<int> m(3);
  int cnt = 0;
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      m[i][j] = cnt++;
  cnt = 0;
  TDynamicMatrix<int> res = m * 10;
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      EXPECT_EQ((cnt++) * 10, res[i][j]);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; a[0][1] = 2;
  a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 5; b[0][1] = 6;
  b[1][0] = 7; b[1][1] = 8;

  TDynamicMatrix<int> res = a * b;
  EXPECT_EQ(19, res[0][0]); // 1*5 + 2*7
  EXPECT_EQ(22, res[0][1]); // 1*6 + 2*8
  EXPECT_EQ(43, res[1][0]); // 3*5 + 4*7
  EXPECT_EQ(50, res[1][1]); // 3*6 + 4*8
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(3), b(5);
  ASSERT_ANY_THROW(a * b);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
  TDynamicMatrix<int> m(3);
  m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
  m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;
  m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;

  TDynamicVector<int> res = m * v;
  EXPECT_EQ(14, res[0]); // 1*1 + 2*2 + 3*3
  EXPECT_EQ(32, res[1]); // 4*1 + 5*2 + 6*3
  EXPECT_EQ(50, res[2]); // 7*1 + 8*2 + 9*3
}

TEST(TDynamicMatrix, can_add_assign_matrices)
{
  TDynamicMatrix<int> a(3), b(3);
  for (size_t i = 0; i < a.size(); i++)
    for (size_t j = 0; j < a.size(); j++) {
      a[i][j] = i * 3 + j;
      b[i][j] = 10;
    }
  a += b;
  for (size_t i = 0; i < a.size(); i++)
    for (size_t j = 0; j < a.size(); j++)
      EXPECT_EQ(i * 3 + j + 10, a[i][j]);
}

TEST(TDynamicMatrix, can_subtract_assign_matrices)
{
  TDynamicMatrix<int> a(3), b(3);
  for (size_t i = 0; i < a.size(); i++)
    for (size_t j = 0; j < a.size(); j++) {
      a[i][j] = (i + 1) * 3 + j + 10;
      b[i][j] = i * 3 + j + 10;
    }
  a -= b;
  for (size_t i = 0; i < a.size(); i++)
    for (size_t j = 0; j < a.size(); j++)
      EXPECT_EQ(3, a[i][j]);
}

TEST(TDynamicMatrix, can_multiply_assign_by_scalar)
{
  TDynamicMatrix<int> m(3);
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      m[i][j] = i * 3 + j + 1;

  m *= 10;
  for (size_t i = 0; i < m.size(); i++)
    for (size_t j = 0; j < m.size(); j++)
      EXPECT_EQ((i * 3 + j + 1) * 10, m[i][j]);
}
