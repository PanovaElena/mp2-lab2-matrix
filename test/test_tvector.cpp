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
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < v.size(); ++i)
        v[i] = static_cast<int>(i * 10);

    TDynamicVector<int> v1(v);

    EXPECT_TRUE(v1 == v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TDynamicVector<int> v1(v);
    v[1] = 999;

    EXPECT_NE(v[1], v1[1]);
    EXPECT_EQ(2, v1[1]);
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);
    EXPECT_EQ(4u, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(4);
    EXPECT_THROW(v.at(static_cast<size_t>(-1)) = 1, std::out_of_range);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);
    EXPECT_THROW(v.at(v.size()) = 1, std::out_of_range);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(3);
    v[0] = 7; v[1] = 8; v[2] = 9;

    ASSERT_NO_THROW(v = v);
    EXPECT_EQ(3u, v.size());
    EXPECT_EQ(8, v[1]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 10; b[1] = 20; b[2] = 30;

    a = b;

    EXPECT_TRUE(a == b);
    EXPECT_EQ(20, a[1]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> a(2);
    TDynamicVector<int> b(5);
    for (size_t i = 0; i < b.size(); ++i)
        b[i] = static_cast<int>(100 + i);

    a = b;

    EXPECT_EQ(5u, a.size());
    EXPECT_TRUE(a == b);
    EXPECT_EQ(104, a[4]);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> a(4);
    TDynamicVector<int> b(1);
    b[0] = 777;

    ASSERT_NO_THROW(a = b);
    EXPECT_EQ(1u, a.size());
    EXPECT_EQ(777, a[0]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 1; b[1] = 2; b[2] = 3;

    EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> a(3);
    a[0] = 5; a[1] = 6; a[2] = 7;

    EXPECT_TRUE(a == a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> a(3), b(4);
    EXPECT_FALSE(a == b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TDynamicVector<int> r = v + 5;

    EXPECT_EQ(6, r[0]);
    EXPECT_EQ(7, r[1]);
    EXPECT_EQ(8, r[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 10; v[1] = 20; v[2] = 30;

    TDynamicVector<int> r = v - 3.0;

    EXPECT_EQ(7, r[0]);
    EXPECT_EQ(17, r[1]);
    EXPECT_EQ(27, r[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 2; v[1] = 3; v[2] = 4;

    TDynamicVector<int> r = v * 2.0;

    EXPECT_EQ(4, r[0]);
    EXPECT_EQ(6, r[1]);
    EXPECT_EQ(8, r[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 10; b[1] = 20; b[2] = 30;

    TDynamicVector<int> c = a + b;

    EXPECT_EQ(11, c[0]);
    EXPECT_EQ(22, c[1]);
    EXPECT_EQ(33, c[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(3), b(4);
    EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 10; a[1] = 20; a[2] = 30;
    b[0] = 1;  b[1] = 2;  b[2] = 3;

    TDynamicVector<int> c = a - b;

    EXPECT_EQ(9, c[0]);
    EXPECT_EQ(18, c[1]);
    EXPECT_EQ(27, c[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(3), b(4);
    EXPECT_THROW(a - b, std::invalid_argument);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 4; b[1] = 5; b[2] = 6;
    int dot = a * b;
    EXPECT_EQ(32, dot);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(3), b(4);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 4; b[1] = 5; b[2] = 6; b[3] = 7;
    EXPECT_NO_THROW({
      int dot = a * b;
      EXPECT_EQ(0, dot);
        });
}