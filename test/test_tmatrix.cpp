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
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[1][1] = 2; m[2][2] = 3;

	TDynamicMatrix<int> m1(m);

	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(3);
	m[0][0] =1;

	TDynamicMatrix<int>m1(m);
	m1[0][0] = 100;

	EXPECT_EQ(1,m[0][0]);
	EXPECT_EQ(100,m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(4);
	EXPECT_EQ(4, m.size());
}
TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	m[1][2] = 42;
	EXPECT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);
		ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m.at(MAX_MATRIX_SIZE + 1));
}
TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 7;

	m=m;
	EXPECT_EQ(7, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(3),m1(3);
	m[0][0] = 1;
	m1=m;

	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(3), m1(5);
	m[0][0] = 1;
	m1 = m;

	EXPECT_EQ(3, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(3),m1(5);
	m[0][0] = 1;

	m1=m;
	EXPECT_EQ(m,m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(3), m1(3);
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(3), m1(5);
	EXPECT_TRUE(m != m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 1; a[1][1] = 2;
	b[0][0] = 3; b[1][1] = 4;

	TDynamicMatrix<int> c = a + b;

	EXPECT_EQ(4,c[0][0]);
	EXPECT_EQ(6,c[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> a(2), b(3);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 5; a[1][1] = 6;
	b[0][0] = 1; b[1][1] = 2;

	TDynamicMatrix<int> c = a - b;

	EXPECT_EQ(4, c[0][0]);
	EXPECT_EQ(4, c[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> a(2), b(3);
		ASSERT_ANY_THROW(a-b);
}

TEST(TDynamicMatrix, can_read_matrix)
{
	TDynamicMatrix<int> m(2), expected(2);
	expected[0][0] = 1; expected[0][1] = 2;
	expected[1][0] = 3; expected[1][1] = 4;

	std::stringstream sstr;
	sstr << "1 2 3 4\n";
	sstr >> m;

	EXPECT_EQ(expected, m);
}

TEST(TDynamicMatrix, can_write_matrix)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1]= 2;
	m[1][0] = 3; m[1][1]= 4;

	std::stringstream sstr;
	sstr << m;

	std::string expected = "1 2 \n3 4 \n";
	EXPECT_EQ(expected, sstr.str());
};