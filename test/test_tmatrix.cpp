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
	TDynamicMatrix<int> source(3);
	for (size_t i = 0; i < source.size(); i++) {
		for (size_t j = 0; j < source.size(); j++) {
			source[i][j] = i+j;
		}
	}
	TDynamicMatrix<int> copy(source);
	EXPECT_EQ(source.size(), copy.size());
	for (size_t i = 0; i < source.size(); i++) {
		for (size_t j = 0; j < source.size(); j++) {
			EXPECT_EQ(source[i][j], copy[i][j]);
		}
	}

}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> source(3);
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			source[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> copy(source);
	EXPECT_NE(&source[0][0], &copy[0][0]);
	source[0][0] = 111;
	EXPECT_NE(source[0][0], copy[0][0]);
	copy[1][1] = 222;
	EXPECT_NE(source[1][1], copy[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> v(3);
	EXPECT_EQ(v.size(), 3);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	int a;
	TDynamicMatrix<int> v(4);
	v[0][0] = 4;
	a = v[0][0];
	EXPECT_EQ(4, v[0][0]);
	EXPECT_EQ(a, 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> v(4);
	ASSERT_ANY_THROW(v[-1][-1] = 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> v(4);
	ASSERT_ANY_THROW(v[4][4] = 4);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> v(4);
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v.size(); j++){
			v[i][j] = i+j;
		}
	}
	v = v;
	EXPECT_EQ(v.size(), 4);
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v.size(); j++) {
			EXPECT_EQ(v[i][j], i + j);
		}
	}
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(4);
	v2 = v1;
	EXPECT_EQ(v1.size(), v2.size());
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			EXPECT_EQ(v1[i][j], v2[i][j]);
		}
	}
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(4);
	v2 = v1;
	EXPECT_EQ(v1.size(), v2.size());
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			EXPECT_EQ(v1[i][j], v2[i][j]);
		}
	}
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(2);
	v2 = v1;
	EXPECT_EQ(v1.size(), v2.size());
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			EXPECT_EQ(v1[i][j], v2[i][j]);
		}
	}
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(v1);
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(2);
	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(v1);
	TDynamicMatrix<int> v3(v1.size());
	v3 = v1 + v2;
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			EXPECT_EQ(v3[i][j], (i + j) * 2);
		}
	}

}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(2);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(v1);
	TDynamicMatrix<int> v3(v1.size());
	v3 = v1 - v2;
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			EXPECT_EQ(v3[i][j], 0);
		}
	}
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(2);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicMatrix, io) {
	TDynamicMatrix<int> v1(4);
	for (size_t i = 0; i < v1.size(); i++) {
		for (size_t j = 0; j < v1.size(); j++) {
			v1[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> v2(4);
	std::stringstream s;
	s << v1;
	s >> v2;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicMatrix, multiply_matrix_const) {
	TDynamicMatrix<int> m(2);
	m[0][0] = 0; m[0][1] = 1; m[1][0] = 2; m[1][1] = 3;
	m * 2;
	TDynamicMatrix<int> x(m);
}