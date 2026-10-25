#include <sstream>
#include <utility>
#include "gtest.h"
#include "tmatrix.h"

TEST(TDynamicVector, create)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, zero_size)
{
  ASSERT_THROW(TDynamicVector<int> v(0), std::out_of_range);
}

TEST(TDynamicVector, large_size)
{
  ASSERT_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1), std::length_error);
}

TEST(TDynamicVector, negative_size)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, from_array)
{
  int values[] = {2, 4, 6};
  TDynamicVector<int> v(values, 3);
  EXPECT_EQ(2, v[0]);
  EXPECT_EQ(4, v[1]);
  EXPECT_EQ(6, v[2]);
  values[0] = 99;
  EXPECT_EQ(2, v[0]);
}

TEST(TDynamicVector, copy_constructor)
{
  TDynamicVector<int> a(2);
  a[0] = 3;
  a[1] = 7;
  TDynamicVector<int> b(a);
  EXPECT_TRUE(b == a);
  b[0] = 10;
  EXPECT_EQ(3, a[0]);
}

TEST(TDynamicVector, move_constructor)
{
  TDynamicVector<int> a(2);
  a[0] = 8;
  TDynamicVector<int> b(std::move(a));
  EXPECT_EQ(8, b[0]);
  EXPECT_EQ(0u, a.size());
}

TEST(TDynamicVector, move_assignment)
{
  TDynamicVector<int> a(2);
  a[0] = 9;
  TDynamicVector<int> b(4);
  b = std::move(a);
  EXPECT_EQ(2u, b.size());
  EXPECT_EQ(9, b[0]);
  EXPECT_EQ(0u, a.size());
}

TEST(TDynamicVector, size)
{
  TDynamicVector<int> v(4);
  EXPECT_EQ(4u, v.size());
}

TEST(TDynamicVector, index)
{
  TDynamicVector<int> v(2);
  v[0] = 4;
  v.at(1) = 5;
  EXPECT_EQ(4, v[0]);
  EXPECT_EQ(5, v.at(1));
}

TEST(TDynamicVector, negative_index)
{
  TDynamicVector<int> v(2);
  EXPECT_ANY_THROW(v[-1] = 4);
}

TEST(TDynamicVector, large_index)
{
  TDynamicVector<int> v(2);
  EXPECT_THROW(v[2] = 4, std::out_of_range);
  EXPECT_THROW(v.at(2), std::out_of_range);
}

TEST(TDynamicVector, self_copy_assignment)
{
  TDynamicVector<int> v(2);
  v[0] = 11;
  v = v;
  EXPECT_EQ(11, v[0]);
}

TEST(TDynamicVector, copy_assignment)
{
  TDynamicVector<int> a(2);
  a[0] = 12;
  TDynamicVector<int> b(2);
  b = a;
  EXPECT_EQ(2u, b.size());
  EXPECT_EQ(12, b[0]);
  b[0] = 0;
  EXPECT_EQ(12, a[0]);
}

TEST(TDynamicVector, copy_assignment_changes_size)
{
  TDynamicVector<int> a(4);
  TDynamicVector<int> b(2);
  b = a;
  EXPECT_EQ(4u, b.size());
}

TEST(TDynamicVector, equal)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(2);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
}

TEST(TDynamicVector, not_equal)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(2);
  TDynamicVector<int> c(3);
  b[1] = 1;
  EXPECT_FALSE(a == b);
  EXPECT_TRUE(a != b);
  EXPECT_FALSE(a == c);
}

TEST(TDynamicVector, add_number)
{
  TDynamicVector<int> v(2);
  v[0] = 2;
  EXPECT_EQ(5, (v + 3)[0]);
}

TEST(TDynamicVector, subtract_number)
{
  TDynamicVector<double> v(2);
  v[0] = 5.0;
  EXPECT_DOUBLE_EQ(2.5, (v - 2.5)[0]);
}

TEST(TDynamicVector, multiply_number)
{
  TDynamicVector<int> v(2);
  v[0] = 5;
  EXPECT_EQ(15, (v * 3)[0]);
}

TEST(TDynamicVector, add)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(2);
  a[0] = 2;
  b[0] = 4;
  EXPECT_EQ(6, (a + b)[0]);
}

TEST(TDynamicVector, add_different_sizes)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(3);
  EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(TDynamicVector, subtract)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(2);
  a[0] = 7;
  b[0] = 4;
  EXPECT_EQ(3, (a - b)[0]);
}

TEST(TDynamicVector, subtract_different_sizes)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(3);
  EXPECT_THROW(a - b, std::invalid_argument);
}

TEST(TDynamicVector, dot_product)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(2);
  a[0] = 1;
  a[1] = 2;
  b[0] = 3;
  b[1] = 4;
  EXPECT_EQ(11, a * b);
}

TEST(TDynamicVector, multiply_different_sizes)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(3);
  EXPECT_THROW(a * b, std::invalid_argument);
}

TEST(TDynamicVector, read)
{
  TDynamicVector<int> v(3);
  std::stringstream input("1 2 3");
  input >> v;
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, write)
{
  TDynamicVector<int> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  std::stringstream output;
  output << v;
  EXPECT_EQ("1 2 3 ", output.str());
}

TEST(TDynamicVector, null_array)
{
  EXPECT_THROW(TDynamicVector<int> v(nullptr, 2), std::invalid_argument);
}

TEST(TDynamicVector, empty_array)
{
  int value = 1;
  EXPECT_THROW(TDynamicVector<int> v(&value, 0), std::out_of_range);
}

TEST(TDynamicVector, const_index)
{
  TDynamicVector<int> a(2);
  a[0] = 13;
  const TDynamicVector<int>& v = a;
  EXPECT_EQ(13, v[0]);
  EXPECT_EQ(13, v.at(0));
}

TEST(TDynamicVector, at_negative_index)
{
  TDynamicVector<int> v(2);
  EXPECT_THROW(v.at(-1), std::out_of_range);
}

TEST(TDynamicVector, copy_empty_vector)
{
  TDynamicVector<int> a(2);
  TDynamicVector<int> b(std::move(a));
  TDynamicVector<int> copy(a);
  EXPECT_EQ(0u, copy.size());
}

TEST(TDynamicVector, self_move)
{
  TDynamicVector<int> v(2);
  v[0] = 14;
  v = std::move(v);
  EXPECT_EQ(2u, v.size());
  EXPECT_EQ(14, v[0]);
}

TEST(TDynamicVector, bad_input)
{
  TDynamicVector<int> v(2);
  std::stringstream input("5");
  input >> v;
  EXPECT_TRUE(input.fail());
}

TEST(TDynamicVector, add_all_elements)
{
  TDynamicVector<int> a(3);
  TDynamicVector<int> b(3);
  a[0] = 1; a[1] = 2; a[2] = 3;
  b[0] = 4; b[1] = 5; b[2] = 6;
  TDynamicVector<int> result = a + b;
  EXPECT_EQ(5, result[0]);
  EXPECT_EQ(7, result[1]);
  EXPECT_EQ(9, result[2]);
}
