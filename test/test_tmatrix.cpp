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
	TMatrix<int> m1(4);
	TMatrix<int> m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m1;
	TMatrix<int> m2;
	EXPECT_NE(&m1, &m2);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(4);

	EXPECT_EQ(4, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(2);
	TVector<int> v(2);
	v[0] = 1; v[1] = 2;
	m[0][1] = 4;
	m[1] = v;
	EXPECT_EQ(4, m[0][1]);
	EXPECT_EQ(v, m[1]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m;
	ASSERT_ANY_THROW(m[-3]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
	//ASSERT_ANY_THROW(m[MAX_MATRIX_SIZE + 1]);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m;
	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 3;
	TMatrix<int> m1(size), m2(size);
	m2[0][2] = 4;
	m2[1][1] = 3;
	ASSERT_NO_THROW(m2 = m1);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	const int size_m1 = 2, size_m2 = 5;
	TVector<TVector<int> > v1(size_m1), v2(size_m2);
	for (size_t i = 0; i < size_m1; i++) {
		v1[i][i] = i;
	}
	for (size_t i = 0; i < size_m2; i++) {
		v2[i][i] = i + 5;
	}
	TMatrix<int> m1(v1);
	TMatrix<int> m2(v2);
	m2 = m1;
	EXPECT_EQ(2, m2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	const int size_m1 = 2, size_m2 = 5;
	TVector<TVector<int> > v1(size_m1), v2(size_m2);
	for (size_t i = 0; i < size_m1; i++) {
		v1[i][i] = i;
	}
	for (size_t i = 0; i < size_m2; i++) {
		v2[i][i] = i + 5;
	}
	TMatrix<int> m1(v1);
	TMatrix<int> m2(v2);
	ASSERT_NO_THROW(m2 = m1);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	const int size_m1 = 4, size_m2 = 4;
	TVector<TVector<int> > v1(size_m1), v2(size_m2);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i][i] = 3;
	v2 = v1;
	TMatrix<int> m1(v1), m2(v2);
	EXPECT_EQ(true, m2 == m1);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	const int size_m = 4;
	TVector<TVector<int> > v1(size_m);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i][i] = 3;
	TMatrix<int> m1(v1);
	EXPECT_EQ(true, m1 == m1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	const int size_m1 = 3, size_m2 = 4;
	TVector<TVector<int> > v1(size_m1), v2(size_m2);
	TMatrix<int> m1(v1), m2(v2);
	EXPECT_EQ(true, m2 != m1);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	const int size_m1 = 3, size_m2 = 3;
	TVector<TVector<int> > v1(size_m1), v2(size_m2);
	TMatrix<int> m1(v1), m2(v2);
	ASSERT_NO_THROW(m2 + m1);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	const int size_m1 = 3, size_m2 = 4;
	TVector<TVector<int> > v1(size_m1), v2(size_m2);
	TMatrix<int> m1(v1), m2(v2);
	ASSERT_ANY_THROW(m2 + m1);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	const int size_m1 = 3, size_m2 = 3;
	TVector<TVector<int> > v1(size_m1), v2(size_m2);
	TMatrix<int> m1(v1), m2(v2);
	ASSERT_NO_THROW(m2 - m1);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	const int size_m1 = 3, size_m2 = 4;
	TVector<TVector<int> > v1(size_m1), v2(size_m2);
	TMatrix<int> m1(v1), m2(v2);
	ASSERT_ANY_THROW(m2 - m1);
}

