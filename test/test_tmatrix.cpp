#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
	TMatrix<int> m(5);

	ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(5);
	for (int i = 0; i < m.GetSize(); i++)
		for (int j = 0; j < m[i].GetSize(); j++)
			m[i][j] = 2;
	TMatrix<int> a(m);
	bool res = a == m;
	EXPECT_EQ(true, res);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(5);
	TMatrix<int> m1(m);
	int res = &m[0] == &m1[0];
	EXPECT_NE(1, res);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);
	ASSERT_NO_THROW(m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(5);
	ASSERT_NO_THROW(m.GetSize());
	ASSERT_NO_THROW(m[2] = 2);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(5);
	ASSERT_ANY_THROW(m.Set(-1, 2));
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix <int> a(5);
	ASSERT_ANY_THROW(a[6][3] = 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix <int> a(5);
	ASSERT_NO_THROW(a = a);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix <int> a(5);
	TMatrix <int> b(5);
	ASSERT_NO_THROW(a = b);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix <int> a(5);
	TMatrix <int> b(4);
	int aSize = a.GetSize();
	a = b;
	EXPECT_NE(aSize, a.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix <int> a(5);
	TMatrix <int> b(4);
	ASSERT_NO_THROW(a = b);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix <int> a(5);
	TMatrix <int> b(5);
	EXPECT_EQ(true, a == b);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix <int> a(5);
	EXPECT_EQ(true, a == a);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix <int> a(5);
	TMatrix <int> b(4);
	EXPECT_EQ(true, a != b);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix <int> a(5);
	TMatrix <int> b(5);
	ASSERT_NO_THROW(a + b);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix <int> a(5);
	TMatrix <int> b(4);
	ASSERT_ANY_THROW(a + b);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix <int> a(5);
	TMatrix <int> b(5);
	ASSERT_NO_THROW(a - b);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix <int> a(5);
	TMatrix <int> b(4);
	ASSERT_ANY_THROW(a - b);
}
