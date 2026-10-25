#include <sstream>
#include "gtest.h"
#include "tmatrix.h"
#include <utility>

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
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	TDynamicVector<int> expected(v);

	TDynamicVector<int> moved(std::move(v));

	EXPECT_EQ(expected, moved);
	EXPECT_EQ(0, v.size());
}

TEST(TDynamicVector, can_move_vector_using_move_operator)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	TDynamicVector<int> expected(v);

	TDynamicVector<int> target(5);
	target[0] = 4; target[1] = 5; target[2] = 6; target[3] = 7; target[4] = 8;

	target = std::move(v);

	EXPECT_EQ(expected, target);
} 

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	TDynamicVector<int> copy(v);

	EXPECT_EQ(v, copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	TDynamicVector<int> copy(v);

	copy[0] = 100;

	EXPECT_EQ(1, v[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4u, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v.at(0));
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(3);

  ASSERT_ANY_THROW(v.at(-1) = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(3);

  ASSERT_ANY_THROW(v.at(3) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  TDynamicVector<int> expected(v);
  TDynamicVector<int>& same = v;

  ASSERT_NO_THROW(v = same);

  EXPECT_EQ(expected, v);
}
TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> a(3);
  a[0] = 1; a[1] = 2; a[2] = 3;
  TDynamicVector<int> b(3);
  b[0] = 4; b[1] = 5; b[2] = 6;

  ASSERT_NO_THROW(a = b);

  EXPECT_EQ(a, b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> a(2);
  a[0] = 1; a[1] = 2;
  TDynamicVector<int> b(3);
  b[0] = 4; b[1] = 5; b[2] = 6;

  ASSERT_NO_THROW(a = b);

  EXPECT_EQ(3u, a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> a(2);
  a[0] = 1; a[1] = 2;
  TDynamicVector<int> b(3);
  b[0] = 4; b[1] = 5; b[2] = 6;
  TDynamicVector<int> a1(2);
  a1[0] = 1; a1[1] = 2;
  TDynamicVector<int> b1(3);
  b1[0] = 4; b1[1] = 5; b1[2] = 6;

  ASSERT_NO_THROW(a = b);
  ASSERT_NO_THROW(b1 = a1);

  EXPECT_EQ(a, b);
  EXPECT_EQ(a1, b1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> a(2);
  a[0] = 1; a[1] = 2;
  TDynamicVector<int> b(2);
  b[0] = 1; b[1] = 2;

  EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> a(2);
  a[0] = 1; a[1] = 2;

  EXPECT_TRUE(a == a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> a(2);
	a[0] = 1; a[1] = 2;
	TDynamicVector<int> b(3);
	b[0] = 1; b[1] = 2; b[2] = 3;

	EXPECT_TRUE(a != b);
	EXPECT_FALSE(a == b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3), expected(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  expected[0] = 6; expected[1] = 7; expected[2] = 8;

  EXPECT_EQ(expected, v + 5);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3), expected(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  expected[0] = 0; expected[1] = 1; expected[2] = 2;

  EXPECT_EQ(expected, v - 1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(3), expected(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  expected[0] = 2; expected[1] = 4; expected[2] = 6;

  EXPECT_EQ(expected, v * 2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> a(3), b(3), expected(3);
	a[0] = 1; a[1] = 2; a[2] = 3;
	b[0] = 4; b[1] = 5; b[2] = 6;
	expected[0] = 5; expected[1] = 7; expected[2] = 9;

	EXPECT_EQ(expected, a + b);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(3), b(4);

	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3), expected(3);
  a[0] = 4; a[1] = 5; a[2] = 6;
  b[0] = 1; b[1] = 2; b[2] = 3;
  expected[0] = 3; expected[1] = 3; expected[2] = 3;

  EXPECT_EQ(expected, a - b);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(3), b(4);

  ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3);
  a[0] = 1; a[1] = 2; a[2] = 3;
  b[0] = 4; b[1] = 5; b[2] = 6;

  EXPECT_EQ(32, a * b);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(3), b(4);

  ASSERT_ANY_THROW(a * b);
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
