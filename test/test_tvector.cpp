#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	int size = 10;
	TDynamicVector<int> v(size);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int size = 10;
	TDynamicVector<int> v(size);
	for (size_t i = 0; i < size; i++)
	{
		v[i] = i;
	}
	TDynamicVector<int> v1(v);

	bool flag = true;
	if (v.size() != v1.size())
	{
		flag = false;
	}
	for (int i = 0; i < v.size(); i++)
	{
		if(v[i] != v1[i])
			flag = false;
	}
	EXPECT_TRUE(flag);
	//ADD_FAILURE();
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int size = 10;
	TDynamicVector<int> v(size);
	for (size_t i = 0; i < size; i++)
	{
		v[i] = i;
	}
	TDynamicVector<int> v1(v);

	EXPECT_TRUE(&v != &v1);
	EXPECT_EQ(v.size(), v1.size());
	EXPECT_EQ(size, v1.size());
	for (int i = 0; i < size; ++i)
	{
		EXPECT_EQ(v[i], v1[i]);
	}
	int OrgVal = v[0];
	v[0] = 999;
	EXPECT_TRUE(OrgVal != v[0]);
	EXPECT_TRUE(OrgVal == v1[0]);
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_get_size)
{
	int size = 4;
	TDynamicVector<int> v(size);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	int size = 4;
	TDynamicVector<int> v(size);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	int size = 4;
	TDynamicVector<int> v(size);

	ASSERT_ANY_THROW(v.at(-1) = 4);
	//ADD_FAILURE();
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	int size = 4;
	TDynamicVector<int> v(size);

	ASSERT_ANY_THROW(v.at(4) = 4);
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int size = 5;
	TDynamicVector<int> v(size);
	for (int i = 0; i < v.size(); i++)
	{
		v[i] = i * 5;
	}

	v = v;
	EXPECT_EQ(v.size(), 5);
	for (int i = 0; i < v.size(); i++)
	{
		EXPECT_EQ(v[i], i * 5);
	}
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int size = 5;
	TDynamicVector<int> v(size);
	TDynamicVector<int> v1(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = i * 5;
	}
	for (int i = 0; i < size; i++)
	{
		v1[i] = i * 10;
	}

	v = v1;
	EXPECT_EQ(v.size(), size);
	for (int i = 0; i < v.size(); i++)
	{
		EXPECT_EQ(v[i], i * 10);
	}
	//ADD_FAILURE();
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	int size1 = 5;
	int size2 = 10;
	TDynamicVector<int> v(size1);
	TDynamicVector<int> v1(size2);
	for (int i = 0; i < size1; i++)
	{
		v[i] = i * 5;
	}
	for (int i = 0; i < size2; i++)
	{
		v1[i] = i * 10;
	}

	v = v1;
	EXPECT_EQ(v.size(), size2);
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int size1 = 5;
	int size2 = 10;
	TDynamicVector<int> v(size1);
	TDynamicVector<int> v1(size2);
	for (int i = 0; i < size1; i++)
	{
		v[i] = i * 5;
	}
	for (int i = 0; i < size2; i++)
	{
		v1[i] = i * 10;
	}

	v = v1;
	for (int i = 0; i < v.size(); i++)
	{
		EXPECT_EQ(v[i], i * 10);
	}
	//ADD_FAILURE();
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int size = 5;
	TDynamicVector<int> v(size);
	v[1] = 2;
	v[2] = 3;
	TDynamicVector<int> v1(size);
	v1[1] = 2;
	v1[2] = 3;

	EXPECT_TRUE(v == v1);
	//ADD_FAILURE();
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int size = 5;
	TDynamicVector<int> v(size);
	v[1] = 2;
	v[2] = 3;

	EXPECT_TRUE(v == v);
	//ADD_FAILURE();
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	int size1 = 5;
	int size2 = 4;
	TDynamicVector<int> v(size1);
	v[1] = 2;
	v[2] = 3;
	TDynamicVector<int> v1(size2);
	v1[1] = 2;
	v1[2] = 3;

	EXPECT_TRUE(v != v1); //Normal test because != starts ==
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int size = 5;
	TDynamicVector<int> v(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = i * 5;
	}
	TDynamicVector<int> res = v + 5;

	EXPECT_EQ(res.size(), size);
	for (int i = 0; i < size; i++)
	{
		EXPECT_EQ(res[i], i * 5 + 5);
	}
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int size = 5;
	TDynamicVector<int> v(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = i * 5;
	}
	TDynamicVector<int> res = v - 5;

	EXPECT_EQ(res.size(), size);
	for (int i = 0; i < size; i++)
	{
		EXPECT_EQ(res[i], i * 5 - 5);
	}
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int size = 5;
	TDynamicVector<int> v(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = i * 5;
	}
	TDynamicVector<int> res = v * 5;

	EXPECT_EQ(res.size(), size);
	for (int i = 0; i < size; i++)
	{
		EXPECT_EQ(res[i], i * 5 * 5);
	}
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int size = 5;
	TDynamicVector<int> v(size);
	TDynamicVector<int> v1(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = i * 2;
	}
	for (int i = 0; i < size; i++)
	{
		v1[i] = i * 3;
	}
	TDynamicVector<int> res = v + v1;

	EXPECT_EQ(res.size(), size);
	for (int i = 0; i < size; i++)
	{
		EXPECT_EQ(res[i], 5 * i);
	}
	//ADD_FAILURE();
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	int size1 = 5;
	int size2 = 4;
	TDynamicVector<int> v(size1);
	TDynamicVector<int> v1(size2);
	for (int i = 0; i < size1; i++)
	{
		v[i] = i * 2;
	}
	for (int i = 0; i < size2; i++)
	{
		v1[i] = i * 3;
	}
	ASSERT_ANY_THROW(TDynamicVector<int> res = v + v1);
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int size = 5;
	TDynamicVector<int> v(size);
	TDynamicVector<int> v1(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = i * 2;
	}
	for (int i = 0; i < size; i++)
	{
		v1[i] = i * 3;
	}
	TDynamicVector<int> res = v - v1;

	EXPECT_EQ(res.size(), size);
	for (int i = 0; i < size; i++)
	{
		EXPECT_EQ(res[i], (-1)* i);
	}
	//ADD_FAILURE();
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	int size1 = 5;
	int size2 = 4;
	TDynamicVector<int> v(size1);
	TDynamicVector<int> v1(size2);
	for (int i = 0; i < size1; i++)
	{
		v[i] = i * 2;
	}
	for (int i = 0; i < size2; i++)
	{
		v1[i] = i * 3;
	}
	ASSERT_ANY_THROW(TDynamicVector<int> res = v - v1);
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int size = 5;
	TDynamicVector<int> v(size);
	TDynamicVector<int> v1(size);
	for (int i = 0; i < size; i++)
	{
		v[i] = i * 2;
	}
	for (int i = 0; i < size; i++)
	{
		v1[i] = i * 3;
	}
	int res = v * v1;

	EXPECT_EQ(res, 0*0 + 2*3 + 4*6 + 6*9 + 8*12);
	//ADD_FAILURE();
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	int size1 = 5;
	int size2 = 4;
	TDynamicVector<int> v(size1);
	TDynamicVector<int> v1(size2);
	for (int i = 0; i < size1; i++)
	{
		v[i] = i * 2;
	}
	for (int i = 0; i < size2; i++)
	{
		v1[i] = i * 3;
	}
	ASSERT_ANY_THROW(int res = v * v1);
	//ADD_FAILURE();
}

TEST(TDynamicVector, can_create_vector_with_move_semantics)
{
	int size = 5;
	TDynamicVector<int> v1(size);
	for (size_t i = 0; i < size; i++)
		v1[i] = i;
	TDynamicVector<int> v2(std::move(v1));

	EXPECT_EQ(v1.size(), 0);
	//EXPECT_EQ(v1[0], nullptr); +++++++++++++++++++++++++++++++++ Почему?
	EXPECT_EQ(v2.size(), size);
	for (size_t i = 0; i < v2.size(); i++)
		EXPECT_EQ(v2[i], i);
	//ADD_FAILURE();
}

TEST(TDynamicVector, move_assignment_operator_works_correctly)
{
	int size1 = 5;
	int size2 = 3;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);
	for (size_t i = 0; i < size1; i++)
		v1[i] = i;
	for (size_t i = 0; i < size2; i++)
		v2[i] = i + 10;
	v2 = std::move(v1);

	EXPECT_EQ(v1.size(), 0);
	EXPECT_EQ(v2.size(), size1);
	for (size_t i = 0; i < v2.size(); i++)
		EXPECT_EQ(v2[i], i);
	//ADD_FAILURE();
}

TEST(TDynamicVector, moved_from_vector_can_be_reused)
{
	int size = 5;
	TDynamicVector<int> v1(size);
	for (size_t i = 0; i < size; i++)
		v1[i] = i + 1;
	TDynamicVector<int> v2 = std::move(v1);
	v1 = TDynamicVector<int>(size);
	for (size_t i = 0; i < size; i++)
		v1[i] = i + 100;

	EXPECT_EQ(v1.size(), size);
	for (size_t i = 0; i < v1.size(); i++)
		EXPECT_EQ(v1[i], i + 100);
	//ADD_FAILURE();
}

TEST(TDynamicVector, self_move_assignment_does_not_crash)
{
	int size = 5;
	TDynamicVector<int> v(size);
	for (size_t i = 0; i < v.size(); i++)
		v[i] = i;
	v = std::move(v);

	EXPECT_EQ(v.size(), size);
	for (size_t i = 0; i < v.size(); i++)
		EXPECT_EQ(v[i], i);
	//ADD_FAILURE();
}

