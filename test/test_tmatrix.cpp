#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(7));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 5));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-7));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(6);
	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(3);
	m1[0][0] = 2; m1[0][1] = 3; m1[0][2] = 1;
	m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
	m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;

	TDynamicMatrix<int> m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 5; m1[0][1] = 6;
	m1[1][0] = 7; m1[1][1] = 8;

	TDynamicMatrix<int> m2(m1);
	m2[0][0] = 15;

	EXPECT_NE(m1[0][0], m2[0][0]);
	EXPECT_EQ(5, m1[0][0]);
	EXPECT_EQ(15, m2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 7;
	m[1][2] = 15;

	EXPECT_EQ(7, m[0][0]);
	EXPECT_EQ(15, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m.at(5));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 5; m[0][1] = 6;
	m[1][0] = 7; m[1][1] = 8;

	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(5, m[0][0]);
	EXPECT_EQ(6, m[0][1]);
	EXPECT_EQ(7, m[1][0]);
	EXPECT_EQ(8, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 2; m1[0][1] = 3;
	m1[1][0] = 4; m1[1][1] = 5;

	TDynamicMatrix<int> m2(2);
	m2 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(6);

	m2 = m1;

	EXPECT_EQ(2, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 3; m1[0][1] = 4;
	m1[1][0] = 5; m1[1][1] = 6;

	TDynamicMatrix<int> m2(5);
	m2 = m1;

	EXPECT_EQ(m1, m2);
	EXPECT_EQ(2, m2.size());
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 2; m1[0][1] = 3;
	m1[1][0] = 4; m1[1][1] = 5;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 2; m2[0][1] = 3;
	m2[1][0] = 4; m2[1][1] = 5;

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 3; m[0][1] = 4;
	m[1][0] = 5; m[1][1] = 6;

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(4);

	EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 2; m1[0][1] = 3;
	m1[1][0] = 4; m1[1][1] = 5;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 6; m2[0][1] = 7;
	m2[1][0] = 8; m2[1][1] = 9;

	TDynamicMatrix<int> m3 = m1 + m2;

	EXPECT_EQ(8, m3[0][0]);
	EXPECT_EQ(10, m3[0][1]);
	EXPECT_EQ(12, m3[1][0]);
	EXPECT_EQ(14, m3[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(4);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 8; m1[0][1] = 9;
	m1[1][0] = 10; m1[1][1] = 11;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 2; m2[0][1] = 3;
	m2[1][0] = 4; m2[1][1] = 5;

	TDynamicMatrix<int> m3 = m1 - m2;

	EXPECT_EQ(6, m3[0][0]);
	EXPECT_EQ(6, m3[0][1]);
	EXPECT_EQ(6, m3[1][0]);
	EXPECT_EQ(6, m3[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(5);

	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 2; m1[0][1] = 3;
	m1[1][0] = 4; m1[1][1] = 5;

	TDynamicMatrix<int> m2(2);
	m2[0][0] = 6; m2[0][1] = 7;
	m2[1][0] = 8; m2[1][1] = 9;

	TDynamicMatrix<int> m3 = m1 * m2;

	EXPECT_EQ(36, m3[0][0]);
	EXPECT_EQ(41, m3[0][1]);
	EXPECT_EQ(64, m3[1][0]);
	EXPECT_EQ(73, m3[1][1]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 2; m1[0][1] = 3;
	m1[1][0] = 4; m1[1][1] = 5;

	TDynamicMatrix<int> m2 = m1 * 4;

	EXPECT_EQ(8, m2[0][0]);
	EXPECT_EQ(12, m2[0][1]);
	EXPECT_EQ(16, m2[1][0]);
	EXPECT_EQ(20, m2[1][1]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 2; m[0][1] = 3;
	m[1][0] = 4; m[1][1] = 5;

	TDynamicVector<int> v(2);
	v[0] = 6; v[1] = 7;

	TDynamicVector<int> result = m * v;

	EXPECT_EQ(33, result[0]);
	EXPECT_EQ(59, result[1]);
}

