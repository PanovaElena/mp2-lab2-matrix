#include "tmatrix.h"
#include <gtest.h>

// Базовые тесты создания матрицы
TEST(TDynamicMatrix, can_create_matrix_with_positive_length) {
    ASSERT_NO_THROW(TDynamicMatrix<int> m(3));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix) {
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) {
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-3));
}

// Тесты копирования
TEST(TDynamicMatrix, can_create_copied_matrix) {
    TDynamicMatrix<int> m(3);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 1;
    
    TDynamicMatrix<int> m1(m);
    
    EXPECT_EQ(m.size(), m1.size());
    EXPECT_EQ(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 1;
    
    TDynamicMatrix<int> m1(m);
    m[0][0] = 999;
    
    EXPECT_EQ(1, m1[0][0]);
}

// Тесты доступа к элементам
TEST(TDynamicMatrix, can_get_size) {
    TDynamicMatrix<int> m(4);
    EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element) {
    TDynamicMatrix<int> m(2);
    m[1][1] = 42;
    EXPECT_EQ(42, m[1][1]);
}

// Тесты оператора присваивания
TEST(TDynamicMatrix, can_assign_matrix_to_itself) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 1;
    
    m = m;
    
    EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) {
    TDynamicMatrix<int> m(2), m1(2);
    m1[0][0] = 10;
    
    m = m1;
    
    EXPECT_EQ(10, m[0][0]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size) {
    TDynamicMatrix<int> m(2), m1(3);
    
    m = m1;
    
    EXPECT_EQ(3, m.size());
}

// Тесты арифметических операций
TEST(TDynamicMatrix, can_add_matrices_with_equal_size) {
    TDynamicMatrix<int> m(2), m1(2);
    m[0][0] = 1;
    m1[0][0] = 5;
    
    TDynamicMatrix<int> res = m + m1;
    
    EXPECT_EQ(6, res[0][0]);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) {
    TDynamicMatrix<int> m(2), m1(2);
    m[0][0] = 10;
    m1[0][0] = 3;
    
    TDynamicMatrix<int> res = m - m1;
    
    EXPECT_EQ(7, res[0][0]);
}

// Тесты move-семантики
TEST(TDynamicMatrix, can_create_matrix_with_move_semantics) {
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1;
    
    TDynamicMatrix<int> m2(std::move(m1));
    
    EXPECT_EQ(1, m2[0][0]);
}

TEST(TDynamicMatrix, move_assignment_operator_works_correctly) {
    TDynamicMatrix<int> m1(2), m2(1);
    m1[0][0] = 1;
    
    m2 = std::move(m1);
    
    EXPECT_EQ(1, m2[0][0]);
}