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

static void FillMatrix(TDynamicMatrix<int>& m, int base = 0)
{
    
    for (size_t i = 0; i < m.size(); ++i)
        for (size_t j = 0; j < m.size(); ++j)
            m[i][j] = base + static_cast<int>(i * 100 + j);
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(4);
    FillMatrix(m, 10);

    TDynamicMatrix<int> m1(m);

    EXPECT_TRUE(m1 == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(3);
    FillMatrix(m, 0);

    TDynamicMatrix<int> m1(m);
    m[1][1] = 999;

    EXPECT_NE(m[1][1], m1[1][1]);
    EXPECT_TRUE(m1[0][0] == 0);   
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(7);
    EXPECT_EQ(7u, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(5);
    m[2][3] = 123;
    EXPECT_EQ(123, m[2][3]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(5);
    EXPECT_THROW(m.at(static_cast<size_t>(-1)), std::out_of_range);
    EXPECT_THROW(m[0].at(static_cast<size_t>(-1)) = 1, std::out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(5);
    EXPECT_THROW(m.at(m.size()), std::out_of_range);

    EXPECT_THROW(m[0].at(m.size()) = 1, std::out_of_range);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(3);
    FillMatrix(m, 5);

    ASSERT_NO_THROW(m = m);
    EXPECT_EQ(3u, m.size());
    EXPECT_EQ(5, m[0][0]);
    EXPECT_EQ(5 + 101, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> a(3), b(3);
    FillMatrix(a, 1);
    FillMatrix(b, 1000);

    a = b;

    EXPECT_TRUE(a == b);
    EXPECT_EQ(1000, a[0][0]);
    EXPECT_EQ(1000 + 202, a[2][2]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> a(2);
    TDynamicMatrix<int> b(4);
    FillMatrix(b, 7);

    a = b;

    EXPECT_EQ(4u, a.size());
    EXPECT_TRUE(a == b);
    EXPECT_EQ(7 + 303, a[3][3]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> small(2);
    TDynamicMatrix<int> big(5);
    FillMatrix(big, 42);

    ASSERT_NO_THROW(small = big);
    EXPECT_EQ(5u, small.size());
    EXPECT_TRUE(small == big);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> a(3), b(3);
    FillMatrix(a, 0);
    FillMatrix(b, 0);

    EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> a(3);
    FillMatrix(a, 11);

    EXPECT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> a(3);
    TDynamicMatrix<int> b(4);

    EXPECT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> a(3), b(3);
    FillMatrix(a, 0);
    FillMatrix(b, 100);

    TDynamicMatrix<int> c(3);
    ASSERT_NO_THROW(c = a + b);

    EXPECT_EQ(a.size(), c.size());
    EXPECT_EQ((0 + 0) + (100 + 0), c[0][0]);
    EXPECT_EQ((0 + 202) + (100 + 202), c[2][2]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> a(3), b(4);
    EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> a(3), b(3);
    FillMatrix(a, 500);
    FillMatrix(b, 100);

    TDynamicMatrix<int> c(3);
    ASSERT_NO_THROW(c = a - b);

    EXPECT_EQ(500 - 100, c[0][0]);
    EXPECT_EQ((500 + 202) - (100 + 202), c[2][2]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> a(3), b(4);
    EXPECT_THROW(a - b, std::invalid_argument);
}