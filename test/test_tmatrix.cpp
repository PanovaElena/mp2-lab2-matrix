#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    
    TDynamicMatrix<int> m(5);

    
    EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    EXPECT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    EXPECT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    
    TDynamicMatrix<int> m(3);
    m[0][0] = 1;

    
    EXPECT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    
    TDynamicMatrix<int> m(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = i + j;

    
    TDynamicMatrix<int> m_copy(m);

    
    EXPECT_EQ(m, m_copy);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    
    TDynamicMatrix<int> m(2);
    m[0][0] = 10;

    
    TDynamicMatrix<int> m_copy(m);
    m_copy[0][0] = 100;

    
    EXPECT_NE(m[0][0], m_copy[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    
    TDynamicMatrix<int> m(4);

    
    EXPECT_EQ(m.size(), 4);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    
    TDynamicMatrix<int> m(2);

    
    m[1][0] = 42;

    
    EXPECT_EQ(m[1][0], 42);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    
    TDynamicMatrix<int> m(3);

    
    EXPECT_ANY_THROW(m.at(-1)[0] = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    
    TDynamicMatrix<int> m(3);

    
    EXPECT_ANY_THROW(m.at(3)[0] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    
    TDynamicMatrix<int> m(3);
    m[0][0] = 5;

    
    m = m;

    
    EXPECT_EQ(m[0][0], 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    
    TDynamicMatrix<int> m1(3), m2(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m2[i][j] = i + j;

    
    m1 = m2;

    
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    
    TDynamicMatrix<int> m1(2), m2(4);

    
    m1 = m2;

    
    EXPECT_EQ(m1.size(), 4);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    
    TDynamicMatrix<int> m1(2), m2(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m2[i][j] = i + j;

    
    m1 = m2;

    
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    
    TDynamicMatrix<int> m1(3), m2(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m1[i][j] = m2[i][j] = i + j;

    
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    
    TDynamicMatrix<int> m(3);

    
    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    
    TDynamicMatrix<int> m1(3), m2(4);

    
    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3; m1[1][1] = 4;
    m2[0][0] = 10; m2[0][1] = 20; m2[1][0] = 30; m2[1][1] = 40;

    
    TDynamicMatrix<int> result = m1 + m2;

    
    EXPECT_EQ(result[0][0], 11);
    EXPECT_EQ(result[1][1], 44);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    
    TDynamicMatrix<int> m1(2), m2(3);

    
    EXPECT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 10; m1[0][1] = 20; m1[1][0] = 30; m1[1][1] = 40;
    m2[0][0] = 1;  m2[0][1] = 2;  m2[1][0] = 3;  m2[1][1] = 4;

    
    TDynamicMatrix<int> result = m1 - m2;

    
    EXPECT_EQ(result[0][0], 9);
    EXPECT_EQ(result[1][1], 36);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
    
    TDynamicMatrix<int> m1(2), m2(3);

    
    EXPECT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;
    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;

    
    TDynamicMatrix<int> result = m1 * m2;

    
    EXPECT_EQ(result[0][0], 19); // 1*5 + 2*7
    EXPECT_EQ(result[1][1], 50); // 3*6 + 4*8
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
    
    TDynamicMatrix<int> m1(2), m2(3);

    
    EXPECT_ANY_THROW(m1 * m2);
}
