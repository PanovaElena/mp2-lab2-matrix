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
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;

	TDynamicMatrix<int> copy(m);

	EXPECT_EQ(m, copy);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
	TDynamicMatrix<int> copy(m);

	copy[0][0] = 100;

	EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(2);
  
  EXPECT_EQ(2u, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 4;

  EXPECT_EQ(4, m.at(0).at(0));
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(2);

  ASSERT_ANY_THROW(m.at(-1).at(0) = 1);
  ASSERT_ANY_THROW(m.at(0).at(-1) = 1);
  ASSERT_ANY_THROW(m.at(-1).at(-1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(2);

  ASSERT_ANY_THROW(m.at(2).at(0) = 1);
  ASSERT_ANY_THROW(m.at(0).at(2) = 1);
  ASSERT_ANY_THROW(m.at(2).at(2) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
  TDynamicMatrix<int> expected(m);
  TDynamicMatrix<int>& same = m;

  ASSERT_NO_THROW(m = same);

  EXPECT_EQ(expected, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  TDynamicMatrix<int> b(2);
  b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;

  ASSERT_NO_THROW(a = b);

  EXPECT_EQ(a, b);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  TDynamicMatrix<int> b(3);
  b[0][0] = 5; b[0][1] = 6; b[0][2] = 7; b[1][0] = 8; b[1][1] = 9; b[1][2] = 10; b[2][0] = 11; b[2][1] = 12; b[2][2] = 13;

  ASSERT_NO_THROW(a = b);

  EXPECT_EQ(3u, a.size());


}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  TDynamicMatrix<int> b(3);
  b[0][0] = 5; b[0][1] = 6; b[0][2] = 7; b[1][0] = 8; b[1][1] = 9; b[1][2] = 10; b[2][0] = 11; b[2][1] = 12; b[2][2] = 13;
  TDynamicMatrix<int> a1(2);
  a1[0][0] = 1; a1[0][1] = 2; a1[1][0] = 3; a1[1][1] = 4;
  TDynamicMatrix<int> b1(3);
  b1[0][0] = 5; b1[0][1] = 6; b1[0][2] = 7; b1[1][0] = 8; b1[1][1] = 9; b1[1][2] = 10; b1[2][0] = 11; b1[2][1] = 12; b1[2][2] = 13;

  ASSERT_NO_THROW(a = b);
  ASSERT_NO_THROW(b1 = a1);

  EXPECT_EQ(a, b);
  EXPECT_EQ(a1, b1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  TDynamicMatrix<int> b(2);
  b[0][0] = 1; b[0][1] = 2; b[1][0] = 3; b[1][1] = 4;

  EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;

  EXPECT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> a(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  TDynamicMatrix<int> b(3);
  b[0][0] = 5; b[0][1] = 6; b[0][2] = 7; b[1][0] = 8; b[1][1] = 9; b[1][2] = 10; b[2][0] = 11; b[2][1] = 12; b[2][2] = 13;

  EXPECT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2), expected(2);
  a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;
  expected[0][0] = 6; expected[0][1] = 8; expected[1][0] = 10; expected[1][1] = 12;

  EXPECT_EQ(expected, a + b);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);

  ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2), expected(2);
  a[0][0] = 5; a[0][1] = 6; a[1][0] = 7; a[1][1] = 8;
  b[0][0] = 1; b[0][1] = 2; b[1][0] = 3; b[1][1] = 4;
  expected[0][0] = 4; expected[0][1] = 4; expected[1][0] = 4; expected[1][1] = 4;

  EXPECT_EQ(expected, a - b);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);

  ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicMatrix, can_read_matrix)
{
  TDynamicMatrix<int> m(2), expected(2);
  expected[0][0] = 1; expected[0][1] = 2; expected[1][0] = 3; expected[1][1] = 4;

  std::stringstream sstr;
  sstr << "1 2\n3 4\n";
  sstr >> m;

  EXPECT_EQ(expected, m);
}

TEST(TDynamicMatrix, can_write_matrix)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
  std::string expected = "1 2 \n3 4 \n";

  std::stringstream sstr;
  sstr << m;

  EXPECT_EQ(expected, sstr.str());
}





TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
	TDynamicMatrix<int> m(2), expected(2);
	m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
	expected[0][0] = 2; expected[0][1] = 4; expected[1][0] = 6; expected[1][1] = 8;

	EXPECT_EQ(expected, m * 2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
	TDynamicVector<int> v(2), expected(2);
	v[0] = 5; v[1] = 6;
	expected[0] = 17; expected[1] = 39;

	EXPECT_EQ(expected, m * v);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_of_different_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(3);

	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(2), b(2), expected(2);
	a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
	b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;
	expected[0][0] = 19; expected[0][1] = 22; expected[1][0] = 43; expected[1][1] = 50;

	EXPECT_EQ(expected, a * b);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> a(2), b(3);

	ASSERT_ANY_THROW(a * b);
}