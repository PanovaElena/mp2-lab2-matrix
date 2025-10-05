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
	int size = 5;
	TDynamicMatrix<int> m(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m[i][j] = i * size + j;
		}
	}
	TDynamicMatrix<int> m1(m);

	bool flag = true;
	if (m.size() != m1.size())
		flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (m[i][j] != m1[i][j])
				flag = false;
		}
	}
	EXPECT_TRUE(flag);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	int size = 10;
	TDynamicMatrix<int> m(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m[i][j] = i * size + j;
		}
	}
	TDynamicMatrix<int> m1(m);

	EXPECT_TRUE(&m != &m1);
	EXPECT_EQ(m.size(), m1.size());
	EXPECT_EQ(size, m1.size());
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			EXPECT_EQ(m[i][j], m1[i][j]);
		}
	}
	int OrgVal = m[0][0];
	m[0][0] = 999;
	EXPECT_TRUE(OrgVal != m[0][0]);
	EXPECT_TRUE(OrgVal == m1[0][0]);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, can_get_size) //IT WAS NOT IN .h FILE!!!
{
	int size = 4;
	TDynamicMatrix<int> m(size);

	EXPECT_EQ(4, m.size());
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	int size = 4;
	TDynamicMatrix<int> m(size);
	m[0][0] = 4;

	EXPECT_EQ(4, m[0][0]);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	int size = 4;
	TDynamicMatrix<int> m(size);

	ASSERT_ANY_THROW(m[0].at(-1) = 4);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	int size = 4;
	TDynamicMatrix<int> m(size);

	ASSERT_ANY_THROW(m[3].at(4) = 4);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	int size = 5;
	TDynamicMatrix<int> m(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m[i][j] = i * size + j;
		}
	}

	m = m;
	EXPECT_EQ(m.size(), 5);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			EXPECT_EQ(m[i][j], i * size + j);
		}
	}
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	int size = 5;
	TDynamicMatrix<int> m(size);
	TDynamicMatrix<int> m1(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m[i][j] = i * size + j;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m1[i][j] = i * size + j + 1;
		}
	}

	m = m1;
	EXPECT_EQ(m.size(), size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			EXPECT_EQ(m[i][j], i * size + j + 1);
		}
	}
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	int size1 = 5;
	int size2 = 10;
	TDynamicMatrix<int> m(size1);
	TDynamicMatrix<int> m1(size2);
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size1; j++)
		{
			m[i][j] = i * size1 + j;
		}
	}
	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			m1[i][j] = i * size2 + j + 1;
		}
	}

	m = m1;
	EXPECT_EQ(m.size(), size2);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	int size1 = 5;
	int size2 = 10;
	TDynamicMatrix<int> m(size1);
	TDynamicMatrix<int> m1(size2);
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size1; j++)
		{
			m[i][j] = i * size1 + j;
		}
	}
	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			m1[i][j] = i * size2 + j + 1;
		}
	}

	m = m1;
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			EXPECT_EQ(m[i][j], i * m.size() + j + 1);
		}
	}
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	int size = 5;
	TDynamicMatrix<int> m(size);
	m[0][1] = 2;
	m[1][2] = 3;
	TDynamicMatrix<int> m1(size);
	m1[0][1] = 2;
	m1[1][2] = 3;

	EXPECT_TRUE(m == m1);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	int size = 5;
	TDynamicMatrix<int> m(size);
	m[0][1] = 2;
	m[1][2] = 3;

	EXPECT_TRUE(m == m);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	int size1 = 5;
	int size2 = 4;
	TDynamicMatrix<int> m(size1);
	m[0][1] = 2;
	m[1][2] = 3;
	TDynamicMatrix<int> m1(size2);
	m1[0][1] = 2;
	m1[1][2] = 3;

	EXPECT_TRUE(m != m1);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	int size = 5;
	TDynamicMatrix<int> m(size);
	TDynamicMatrix<int> m1(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m[i][j] = i * size + j;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m1[i][j] = i * size + j + 1;
		}
	}
	TDynamicMatrix<int> res = m + m1;

	EXPECT_EQ(res.size(), size);
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			EXPECT_EQ(res[i][j], 2 * i * m.size() + 2 * j + 1);
		}
	}
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	int size1 = 5;
	int size2 = 4;
	TDynamicMatrix<int> m(size1);
	TDynamicMatrix<int> m1(size2);
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size1; j++)
		{
			m[i][j] = i * size1 + j;
		}
	}
	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			m1[i][j] = i * size2 + j + 1;
		}
	}
	ASSERT_ANY_THROW(TDynamicMatrix<int> res = m + m1);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	int size = 5;
	TDynamicMatrix<int> m(size);
	TDynamicMatrix<int> m1(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m[i][j] = i * size + j;
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			m1[i][j] = i * size + j + 1;
		}
	}
	TDynamicMatrix<int> res = m - m1;

	EXPECT_EQ(res.size(), size);
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m.size(); j++)
		{
			EXPECT_EQ(res[i][j], -1);
		}
	}
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	int size1 = 5;
	int size2 = 4;
	TDynamicMatrix<int> m(size1);
	TDynamicMatrix<int> m1(size2);
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size1; j++)
		{
			m[i][j] = i * size1 + j;
		}
	}
	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			m1[i][j] = i * size2 + j + 1;
		}
	}
	ASSERT_ANY_THROW(TDynamicMatrix<int> res = m - m1);
	//ADD_FAILURE();
}

