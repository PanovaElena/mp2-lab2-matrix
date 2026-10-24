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
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;

	TDynamicMatrix<int> m2(m1);

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 1;

	TDynamicMatrix<int> m2(m1);
	m2[0][0] = 2; 

	EXPECT_EQ(1, m1[0][0]);  
	EXPECT_EQ(2, m2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(24);
	EXPECT_EQ(24, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);
	m[1][1] = 42;

	EXPECT_EQ(42, m[1][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(1);
	ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(1);
	ASSERT_ANY_THROW(m.at(1));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[1][1] = 2;

	ASSERT_NO_THROW(m = m);

	EXPECT_EQ(1, m[0][0]);
	EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1; m1[1][1] = 2;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 3; m2[1][1] = 4;

	m2 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(5);

	m2 = m1;

	EXPECT_EQ(2, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1; m1[1][1] = 2;

	TDynamicMatrix<int> m2(5);
	m2 = m1;

	EXPECT_EQ(2, m2.size());
	EXPECT_EQ(1, m2[0][0]);
	EXPECT_EQ(2, m2[1][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1; m1[1][1] = 2;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 1; m2[1][1] = 2;

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1;

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);

	EXPECT_FALSE(m1 == m2);
	EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 5; m2[0][1] = 6;
	m2[1][0] = 7; m2[1][1] = 8;

	TDynamicMatrix<int> res = m1 + m2;

	EXPECT_EQ(6, res[0][0]);
	EXPECT_EQ(8, res[0][1]);
	EXPECT_EQ(10, res[1][0]);
	EXPECT_EQ(12, res[1][1]);
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
	m1[0][0] = 5; m1[0][1] = 6;
	m1[1][0] = 7; m1[1][1] = 8;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][0] = 3; m2[1][1] = 4;

	TDynamicMatrix<int> res = m1 - m2;

	EXPECT_EQ(4, res[0][0]);
	EXPECT_EQ(4, res[0][1]);
	EXPECT_EQ(4, res[1][0]);
	EXPECT_EQ(4, res[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, correct_simple_multiply)
{
	TDynamicMatrix<int> A(2);
	A[0][0] = 1; A[0][1] = 2;
	A[1][0] = 3; A[1][1] = 4;

	TDynamicMatrix<int> B(2);
	B[0][0] = 5; B[0][1] = 6;
	B[1][0] = 7; B[1][1] = 8;

	TDynamicMatrix<int> C = A.SimpleMultiply(B);

	EXPECT_EQ(19, C[0][0]);
	EXPECT_EQ(22, C[0][1]);
	EXPECT_EQ(43, C[1][0]);
	EXPECT_EQ(50, C[1][1]);
}

TEST(TDynamicMatrix, correct_permutation_multiply)
{
	TDynamicMatrix<int> A(2);
	A[0][0] = 1; A[0][1] = 2;
	A[1][0] = 3; A[1][1] = 4;

	TDynamicMatrix<int> B(2);
	B[0][0] = 5; B[0][1] = 6;
	B[1][0] = 7; B[1][1] = 8;

	TDynamicMatrix<int> C = A.PermutationMultiply(B);

	EXPECT_EQ(19, C[0][0]);
	EXPECT_EQ(22, C[0][1]);
	EXPECT_EQ(43, C[1][0]);
	EXPECT_EQ(50, C[1][1]);
}

TEST(TDynamicMatrix, correct_blocked_multiply)
{
	TDynamicMatrix<int> A(2);
	A[0][0] = 1; A[0][1] = 2;
	A[1][0] = 3; A[1][1] = 4;

	TDynamicMatrix<int> B(2);
	B[0][0] = 5; B[0][1] = 6;
	B[1][0] = 7; B[1][1] = 8;

	TDynamicMatrix<int> C = A.BlockedMultiply(B, 1);

	EXPECT_EQ(19, C[0][0]);
	EXPECT_EQ(22, C[0][1]);
	EXPECT_EQ(43, C[1][0]);
	EXPECT_EQ(50, C[1][1]);
}