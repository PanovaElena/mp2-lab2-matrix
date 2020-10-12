#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
    TMatrix<int> v(10);
    v[2][1] = 1;
    TMatrix<int> v1(v);

    EXPECT_EQ(v, v1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
    TMatrix<int> v(10);
    TMatrix<int> v1(v);
    v1[2][1] = 0;
    v[2][1] = 1;

    EXPECT_EQ(v1[2][1], 0);
}

TEST(TMatrix, can_get_size)
{
    TMatrix<int> v(4);

    EXPECT_EQ(4, v.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
    TMatrix<int> v(4);
    v[0][0] = 4;

    EXPECT_EQ(4, v[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
    TMatrix<int> v(10);

    ASSERT_ANY_THROW(v[-1][0] = 1);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
    TMatrix<int> v(10);

    ASSERT_ANY_THROW(v[20][0] = 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
    TMatrix<int> v(10);
    v[2][1] = 1;
    v = v;
    EXPECT_EQ(v[2][1], 1);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
    TMatrix<int> v(10), v1(10);
    v[2][1] = 1;
    v1 = v;
    EXPECT_EQ(v1, v);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
    TMatrix<int> v(10), v1(5);
    v1 = v;
    EXPECT_EQ(v1.GetSize(), 10);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
    TMatrix<int> v(10), v1(5);
    v[2][1] = 1;
    v1 = v;
    EXPECT_EQ(v1, v);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
    TMatrix<int> v(10);
    TMatrix<int> v1(v);
    EXPECT_EQ(v, v1);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
    TMatrix<int> v(10);
    EXPECT_EQ(v, v);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
    TMatrix<int> v(10);
    TMatrix<int> v1(5);
    for (int i = 0; i < v.GetSize(); i++)
        for(int j = 0; j < v[i].GetSize(); j++)
            v[i][j] = 0;
    for (int i = 0; i < v1.GetSize(); i++)
        for (int j = 0; j < v1[i].GetSize(); j++)
            v1[i][j] = 0;
    EXPECT_NE(v, v1);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
    TMatrix<int> v(10), v1(10);
    TMatrix<int> exp(10);
    for (int i = 0; i < v.GetSize(); i++)
        for (int j = 0; j < v[i].GetSize(); j++)
            v[i][j] = 0;
    for (int i = 0; i < v1.GetSize(); i++)
        for (int j = 0; j < v1[i].GetSize(); j++)
            v1[i][j] = 0;
    for (int i = 0; i < exp.GetSize(); i++)
        for (int j = 0; j < exp[i].GetSize(); j++)
            exp[i][j] = 0;

    EXPECT_EQ(exp, v + v1);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
    TMatrix<int> v(10), v1(5);
    ASSERT_ANY_THROW(v + v1);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
    TMatrix<int> v(10), v1(10);
    TMatrix<int> exp(10);
    for (int i = 0; i < v.GetSize(); i++)
        for (int j = 0; j < v[i].GetSize(); j++)
            v[i][j] = 0;
    for (int i = 0; i < v1.GetSize(); i++)
        for (int j = 0; j < v1[i].GetSize(); j++)
            v1[i][j] = 3;
    for (int i = 0; i < exp.GetSize(); i++)
        for (int j = 0; j < exp[i].GetSize(); j++)
            exp[i][j] = -3;

    EXPECT_EQ(exp, v - v1);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TMatrix<int> v(10), v1(5);
    ASSERT_ANY_THROW(v - v1);
}

