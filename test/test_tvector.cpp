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
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(6);
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int>v1(6);
	TDynamicVector<int>v2(v1);
	v2[4] = 9;
	EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(8);

	EXPECT_EQ(8, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int>v(10);
	EXPECT_ANY_THROW(v[-1] = 8);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> v(10);
	EXPECT_ANY_THROW(v[13] = 13);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(15);
	EXPECT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(26);
	TDynamicVector<int> v2(26);
	EXPECT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(15);
	TDynamicVector<int> v2(5);
	v1 = v2;
	EXPECT_EQ(5, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(20);
	TDynamicVector<int> v2(15);
	EXPECT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(true, v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(200);
	EXPECT_EQ(true, v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(14);
	TDynamicVector<int> v2(17);
	EXPECT_NE(true, v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(7);
	TDynamicVector<int> tmp(7);
	tmp[0] = 10;
	tmp[1] = 10;
	tmp[2] = 10;
	tmp[3] = 10;
	tmp[4] = 10;
	tmp[5] = 10;
	tmp[6] = 10;
	int scalar = 10;
	TDynamicVector<int> drugoy = v + scalar;
	EXPECT_EQ(drugoy, tmp);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> tmp(3);
	tmp[0] = -10;
	tmp[1] = -10;
	tmp[2] = -10;
	int scalar = 10;
	TDynamicVector<int> drugoy = v - scalar;
	EXPECT_EQ(drugoy, tmp);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	TDynamicVector<int> tmp(3);
	v[0] = 0;
	v[1] = 4;
	v[2] = 10;
	tmp[0] = 0;
	tmp[1] = 28;
	tmp[2] = 70;
	int scalar = 7;
	TDynamicVector<int> drugoy = v * scalar;
	EXPECT_EQ(drugoy, tmp);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	TDynamicVector<int> tmp(3);
	TDynamicVector<int> drugoy(3);
	v1[1] = 10;
	v2[1] = -3;
	v2[2] = 17;
	tmp[1] = 7;
	tmp[2] = 17;
	drugoy = v1 + v2;
	EXPECT_EQ(drugoy, tmp);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(17);
	EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	TDynamicVector<int> tmp(3);
	TDynamicVector<int> drugoy(3);
	v1[1] = 9;
	v2[1] = 7;
	v2[2] = 20;
	tmp[1] = 2;
	tmp[2] = -20;
	drugoy = v1 - v2;
	bool f = false;
	if (drugoy == tmp)
	{
		f = true;
	}
	EXPECT_EQ(f, true);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(15);
	EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	v1[0] = 2;
	v1[1] = 3;
	v2[0] = 5;
	v2[1] = 1;
	EXPECT_EQ(v1 * v2, 13);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(7);
	EXPECT_ANY_THROW(v1 * v2);
}
