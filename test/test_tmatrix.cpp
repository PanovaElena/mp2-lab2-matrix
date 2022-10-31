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
    TDynamicMatrix<int>m1(8);
    m1[0][1] = 5;
    m1[5][5] = -18;
    TDynamicMatrix<int>m2(m1);
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int>m1(5);
    m1[2][4] = 3;
    m1[4][3] = -1;
    TDynamicMatrix<int>m2(m1);
    m2[2][4] = -8;
    EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int>m1(5);
    int size = m1.size();
    EXPECT_EQ(5, size);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int>m1(8);
    m1[6][3] = -9;
    m1[6][3] = m1[6][3] + 5;
    EXPECT_EQ(m1[6][3], -4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int>m1(5);
    EXPECT_ANY_THROW(m1[-1][3]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int>m1(5);
    EXPECT_ANY_THROW(m1[6][2]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int>m1(4);
    EXPECT_NO_THROW(m1 = m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int>m1(7);
    TDynamicMatrix<int>m2(7);
    EXPECT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int>m1(6);
    TDynamicMatrix<int>m2(3);
    m1 = m2;
    EXPECT_EQ(m1.size(), 3);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int>m1(5);
    TDynamicMatrix<int>m2(2);
    EXPECT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int>m1(5);
    TDynamicMatrix<int>m2(m1);
    EXPECT_EQ(m1 == m2,true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int>m1(4);
    EXPECT_EQ(m1 == m1, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int>m1(4);
    TDynamicMatrix<int>m2(6);
    EXPECT_EQ(m1 == m2, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int>m1(5);
    TDynamicMatrix<int>m2(5);
    m1[4][2] = 5;
    m2[4][2] = 3;
    TDynamicMatrix<int>tmp1(5);
    tmp1 = m1 + m2;
    TDynamicMatrix<int>tmp2(5);
    tmp2[4][2] = 8;
    EXPECT_EQ(tmp1, tmp2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int>m1(7);
    TDynamicMatrix<int>m2(4);
    EXPECT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int>m1(4);
    TDynamicMatrix<int>m2(4);
    m1[3][2] = 10;
    m2[3][2] = -2;
    TDynamicMatrix<int>tmp1(4);
    tmp1 = m1 - m2;
    TDynamicMatrix<int>tmp2(4);
    tmp2[3][2] = 12;
    EXPECT_EQ(tmp1, tmp2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int>m1(7);
    TDynamicMatrix<int>m2(10);
    EXPECT_ANY_THROW(m1 - m2);
}
