#include <sstream>
#include "gtest.h"
#include "tmatrix.h"

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

TEST(TDynamicVector, can_move_vector_using_move_constructor)
{
  TDynamicVector<int> v1(4);
  for (int i = 0; i < v1.size(); i++)
	  v1[i] = 4 - i;
  ASSERT_NO_THROW(TDynamicVector<int> v(TDynamicVector<int> &&v1));
}

TEST(TDynamicVector, can_move_vector_using_move_operator)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> v1 = std::move(v);

	ASSERT_NO_THROW(TDynamicVector<int> v1);
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(5);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v1(5);
  for (int i = 0; i < v1.size(); i++) {
  	  v1[i] = i;
  }
  TDynamicVector<int> v2(v1);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i*2;
  }
  EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
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
  TDynamicVector<int> v(4);
  ASSERT_ANY_THROW(v.at(-5));
  //ADD_FAILURE();
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(4);
  ASSERT_ANY_THROW(v.at(10));
  //ADD_FAILURE();
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v(v)); 
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v1(5);
  TDynamicVector<int> v2(5);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i;
	  v2[i] = 5-i;
  }
  v1 = v2;
  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v1(6);
  TDynamicVector<int> v2(3);
  size_t sz1 = v1.size();
  v1 = v2;
  EXPECT_NE(sz1, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v1(5);
  TDynamicVector<int> v2(10);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i;
  }
  for (int j = 0; j < v2.size(); j++) {
	  v2[j] = j+1;
  }
  v1 = v2;
  ASSERT_NO_THROW(v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = i;
		v2[i] = i;
	}
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(5);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	EXPECT_EQ(v1, v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v1(4);
  TDynamicVector<int> v2(6);
  for (int i = 0; i<v1.size();i++)
  //ADD_FAILURE();
  EXPECT_NE(v1, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{  
  TDynamicVector<int> v1(5);
  TDynamicVector<int> v2(5);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i;
	  v2[i] = i + 1;
  }
  EXPECT_EQ(v1 + 1, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v1(5);
  TDynamicVector<int> v2(5);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i + 3;
	  v2[i] = i;
  }
  EXPECT_EQ(v1 - 3, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v1(5);
  TDynamicVector<int> v2(5);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i;
	  v2[i] = i*2;
  }
  EXPECT_EQ(v1*2, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	TDynamicVector<int> expect(5);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = i;
		v2[i] = i * 2;
		expect[i] = i * 3;
	}
	EXPECT_EQ(v1+v2, expect);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(5);
  TDynamicVector<int> v2(3);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i;
  }
  for (int j = 0; j < v2.size(); j++) {
	  v2[j] = j;
  }
  ASSERT_ANY_THROW(v1+v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  
  TDynamicVector<int> v1(10);
  TDynamicVector<int> v2(10);
  TDynamicVector<int> expect(10);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i;
	  v2[i] = i + 1;
	  expect[i] = 1;
  }
  EXPECT_EQ(v2-v1, expect);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(5);
  TDynamicVector<int> v2(3);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i;
  }
  for (int j = 0; j < v2.size(); j++) {
	  v2[j] = j;
  }
  ASSERT_ANY_THROW(v2-v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v1(7);
  TDynamicVector<int> v2(7);
  for (int i = 0; i < v1.size(); i++) {
	  v1[i] = i+1;
	  v2[i] = i+1;
  }
  int expect = v1 * v2;
  EXPECT_EQ(expect, 1 + 4 + 9 + 16 + 25 + 36 + 49);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(7);
  TDynamicVector<int> v2(8);
  for (int i = 0; i < v1.size(); i++) {
  	  v1[i] = i;
  }
  for (int j = 0; j < v2.size(); j++) {
	  v2[j] = j;
  }
  ASSERT_ANY_THROW(v2 * v1);
}

TEST(TDynamicVector, can_read_vector)
{
  TDynamicVector<int> v(5);
  TDynamicVector<int> expected(5);
  for (int i = 0; i < 5; i++) expected[i] = i+1;
  
  std::stringstream sstr;
  sstr << "1 2 3 4 5\n";
  sstr >> v;
  
  EXPECT_EQ(expected, v);
}

TEST(TDynamicVector, can_write_vector)
{
  TDynamicVector<int> v(5);
  for (int i = 0; i < 5; i++) v[i] = i+1;
  std::string expected = "1 2 3 4 5 ";
  
  std::stringstream sstr;
  sstr << v;
  
  EXPECT_EQ(expected, sstr.str());
}