#include <sstream>
#include <utility>
#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicMatrix, create)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, zero_size)
{
  ASSERT_THROW(TDynamicMatrix<int> m(0), std::out_of_range);
}

TEST(TDynamicMatrix, large_size)
{
  ASSERT_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1), std::length_error);
}

TEST(TDynamicMatrix, negative_size)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, copy_constructor)
{
  TDynamicMatrix<int> a(2);
  a[0][1] = 4;
  TDynamicMatrix<int> b(a);
  EXPECT_TRUE(b == a);
  b[0][1] = 9;
  EXPECT_EQ(4, a[0][1]);
}

TEST(TDynamicMatrix, size)
{
  TDynamicMatrix<int> m(3);
  EXPECT_EQ(3u, m.size());
}

TEST(TDynamicMatrix, index)
{
  TDynamicMatrix<int> m(2);
  m[1][0] = 6;
  EXPECT_EQ(6, m[1][0]);
}

TEST(TDynamicMatrix, negative_row)
{
  TDynamicMatrix<int> m(2);
  EXPECT_ANY_THROW(m[-1][0] = 1);
}

TEST(TDynamicMatrix, large_row)
{
  TDynamicMatrix<int> m(2);
  EXPECT_THROW(m[2][0] = 1, std::out_of_range);
}

TEST(TDynamicMatrix, self_copy_assignment)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 7;
  m = m;
  EXPECT_EQ(7, m[0][0]);
}

TEST(TDynamicMatrix, copy_assignment)
{
  TDynamicMatrix<int> a(3);
  a[2][1] = 8;
  TDynamicMatrix<int> b(2);
  b = a;
  EXPECT_EQ(3u, b.size());
  EXPECT_EQ(8, b[2][1]);
  b[2][1] = 1;
  EXPECT_EQ(8, a[2][1]);
}

TEST(TDynamicMatrix, equal)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(2);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(TDynamicMatrix, not_equal)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(2);
  TDynamicMatrix<int> c(3);
  b[1][0] = 1;
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a == c);
}

TEST(TDynamicMatrix, add_and_subtract)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(2);
  a[0][0] = 7;
  b[0][0] = 2;
  EXPECT_EQ(9, (a + b)[0][0]);
  EXPECT_EQ(5, (a - b)[0][0]);
}

TEST(TDynamicMatrix, different_sizes)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(3);
  EXPECT_THROW(a + b, std::invalid_argument);
  EXPECT_THROW(a - b, std::invalid_argument);
}

TEST(TDynamicMatrix, multiply_number)
{
  TDynamicMatrix<int> a(2);
  a[0][1] = 4;
  EXPECT_EQ(12, (a * 3)[0][1]);
}

TEST(TDynamicMatrix, multiply_vector)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1;
  a[0][1] = 2;
  a[1][0] = 3;
  a[1][1] = 4;
  TDynamicVector<int> v(2);
  v[0] = 2;
  v[1] = 1;
  TDynamicVector<int> result = a * v;
  EXPECT_EQ(4, result[0]);
  EXPECT_EQ(10, result[1]);
}

TEST(TDynamicMatrix, multiply_vector_different_sizes)
{
  TDynamicMatrix<int> a(2);
  TDynamicVector<int> v(3);
  EXPECT_THROW(a * v, std::invalid_argument);
}

TEST(TDynamicMatrix, multiply)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(2);
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

TEST(TDynamicMatrix, read)
{
  TDynamicMatrix<int> m(2);
  std::stringstream input("1 2 3 4");
  input >> m;
  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(2, m[0][1]);
  EXPECT_EQ(3, m[1][0]);
  EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, write)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2;
  m[1][0] = 3; m[1][1] = 4;
  std::stringstream output;
  output << m;
  EXPECT_EQ("1 2 \n3 4 \n", output.str());
}

TEST(TDynamicMatrix, const_index)
{
  TDynamicMatrix<int> a(2);
  a[1][0] = 15;
  const TDynamicMatrix<int>& m = a;
  EXPECT_EQ(15, m[1][0]);
}

TEST(TDynamicMatrix, large_column)
{
  TDynamicMatrix<int> m(2);
  EXPECT_THROW(m[0][2] = 1, std::out_of_range);
}

TEST(TDynamicMatrix, copy_assignment_same_size)
{
  TDynamicMatrix<int> a(2);
  a[0][1] = 16;
  TDynamicMatrix<int> b(2);
  b = a;
  EXPECT_EQ(16, b[0][1]);
  b[0][1] = 0;
  EXPECT_EQ(16, a[0][1]);
}

TEST(TDynamicMatrix, move_constructor)
{
  TDynamicMatrix<int> a(2);
  a[1][1] = 17;
  TDynamicMatrix<int> b(std::move(a));
  EXPECT_EQ(17, b[1][1]);
  EXPECT_EQ(0u, a.size());
}

TEST(TDynamicMatrix, move_assignment)
{
  TDynamicMatrix<int> a(2);
  a[0][1] = 18;
  TDynamicMatrix<int> b(3);
  b = std::move(a);
  EXPECT_EQ(2u, b.size());
  EXPECT_EQ(18, b[0][1]);
  EXPECT_EQ(0u, a.size());
}

TEST(TDynamicMatrix, self_move)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 19;
  m = std::move(m);
  EXPECT_EQ(2u, m.size());
  EXPECT_EQ(19, m[0][0]);
}

TEST(TDynamicMatrix, multiply_different_sizes)
{
  TDynamicMatrix<int> a(2);
  TDynamicMatrix<int> b(3);
  EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(TDynamicMatrix, bad_input)
{
  TDynamicMatrix<int> m(2);
  std::stringstream input("1 2 3");
  input >> m;
  EXPECT_TRUE(input.fail());
}

TEST(TDynamicMatrix, multiply_all_cells)
{
  TDynamicMatrix<int> a(3);
  TDynamicMatrix<int> identity(3);
  for (size_t i = 0; i < 3; ++i)
    identity[i][i] = 1;
  a[0][0] = 2; a[0][1] = 3; a[0][2] = 4;
  a[1][0] = 5; a[1][1] = 6; a[1][2] = 7;
  a[2][0] = 8; a[2][1] = 9; a[2][2] = 10;
  TDynamicMatrix<int> result = a * identity;
  EXPECT_TRUE(result == a);
}
