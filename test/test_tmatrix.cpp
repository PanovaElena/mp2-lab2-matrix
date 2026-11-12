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
  TDynamicMatrix<int> m1(5);
  TDynamicMatrix<int> m2(m1);
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(m1);
	TDynamicVector<int> v1(3);
	m1[0] = v1;
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(3);
	EXPECT_EQ(3, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m1(5);
  m1[0][0] = 3;
  EXPECT_EQ(m1[0][0], 3);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(-3).at(1) = 61);
  ASSERT_ANY_THROW(m.at(2).at(-1) = 36);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(5);
  ASSERT_ANY_THROW(m.at(6).at(1) = 61);
  ASSERT_ANY_THROW(m.at(2).at(10) = 36);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(6);
  ASSERT_NO_THROW(TDynamicMatrix<int> m(m));
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(3);
  TDynamicMatrix<int> m2(3);
  for (int i = 0; i < m1.size(); i++) {
	  for (int j = 0; j < m1[i].size(); j++) {
		  m1[i][j] = (i + 1) + (j + 1);
		  //std::cout << m1[i][j] << " ";
	  }
	  //std::cout << "\n";
  }
  /* | 2 3 4 |
	 | 3 4 5 |
	 | 4 5 6 | */
  m2 = m1;
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(4);
  TDynamicMatrix<int> m2(7);
  m2 = m1;
  EXPECT_EQ(4, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(4);
  TDynamicMatrix<int> m2(6);
  for (int i = 0; i < m1.size(); i++) {
      for (int j = 0; j < m1[i].size(); j++) {
		  m1[i][j] = (i + 1) + (j + 1);
	  }
  }
  m2 = m1;
  EXPECT_EQ(m2, m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(6);
  TDynamicMatrix<int> m2(6);
  for (int i = 0; i < m1.size(); i++) {
	  for (int j = 0; j < m1[i].size(); j++) {
		  m1[i][j] = (i + 1) + (j + 1);
		  m2[i][j] = (i + 1) + (j + 1);
	  }
  }
  EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m1(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			m1[i][j] = (i + 1) + (j + 1);
		}
	}
	EXPECT_EQ(m1, m1);
}
 
TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(6);
	TDynamicMatrix<int> m2(7);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			m1[i][j] = (i + 1) + (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2[i].size(); j++) {
			m2[i][j] = (i + 1) + (j + 1);
		}
	}
	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(6);
	TDynamicMatrix<int> m2(6);
	TDynamicMatrix<int> expect(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			m1[i][j] = (i + 1) + (j + 1);
			m2[i][j] = 2*(i + 1) + 2*(j + 1);
			expect[i][j] = 3 * (i + 1) + 3 * (j + 1);
		}
	}
	EXPECT_EQ(m1 + m2, expect);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(6);
	TDynamicMatrix<int> m2(8);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			m1[i][j] = (i + 1) + (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2[i].size(); j++) {
			m2[i][j] = 2*(i + 1) + 2*(j + 1);
		}
	}
	ASSERT_ANY_THROW(m1+m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(6);
	TDynamicMatrix<int> m2(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			m1[i][j] = (i + 1) + (j + 1);
			m2[i][j] = 2 * (i + 1) + 2 * (j + 1);
		}
	}
	EXPECT_EQ(m2-m1, m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(6);
	TDynamicMatrix<int> m2(8);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			m1[i][j] = (i + 1) + (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2[i].size(); j++) {
			m2[i][j] = 2 * (i + 1) + 2 * (j + 1);
		}
	}
	ASSERT_ANY_THROW(m1 - m2);
}

/*TEST(TDynamicMatrix, can_read_matrix)
{
  ADD_FAILURE();
}

TEST(TDynamicMatrix, can_write_matrix)
{
  TDynamicMatrix<int> m(2);
  for (int i = 0; i < m.size(); i++) {
  	  for (int j = 0; j < m[i].size(); j++) {
	  	  m[i][j] = (i + 1) + (j + 1);
	  }
  }
  std::cout << m;
  ADD_FAILURE();
}*/
