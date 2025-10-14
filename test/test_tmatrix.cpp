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
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;
    
    TDynamicMatrix<int> m1(m);
    
    EXPECT_EQ(m.size(), m1.size());
    EXPECT_EQ(m[0][0], m1[0][0]);
    EXPECT_EQ(m[0][1], m1[0][1]);
    EXPECT_EQ(m[1][0], m1[1][0]);
    EXPECT_EQ(m[1][1], m1[1][1]);
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

TEST(TDynamicMatrix, throws_when_set_element_with_out_of_range_index) {
    TDynamicMatrix<int> m(3);
    EXPECT_ANY_THROW(m.at(5));  
    EXPECT_ANY_THROW(m.at(10)); 
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

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 2; m1[0][1] = 3;
    m1[1][0] = 4; m1[1][1] = 5;

    TDynamicMatrix<int> m2(2);
    m2[0][0] = 2; m2[0][1] = 3;
    m2[1][0] = 4; m2[1][1] = 5;

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 3; m[0][1] = 4;
    m[1][0] = 5; m[1][1] = 6;

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(4);

    EXPECT_TRUE(m1 != m2);
}

// Тесты арифметических операций
TEST(TDynamicMatrix, can_add_matrices_with_equal_size) {
    TDynamicMatrix<int> m(2), m1(2);
    m[0][0] = 1;
    m1[0][0] = 5;
    
    TDynamicMatrix<int> res = m + m1;
    
    EXPECT_EQ(6, res[0][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) {
    TDynamicMatrix<int> m(2);
    TDynamicMatrix<int> m1(4);

    EXPECT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) {
    TDynamicMatrix<int> m(2), m1(2);
    m[0][0] = 10;
    m1[0][0] = 3;
    
    TDynamicMatrix<int> res = m - m1;
    
    EXPECT_EQ(7, res[0][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size) {
    TDynamicMatrix<int> m(2);
    TDynamicMatrix<int> m1(4);

    EXPECT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_matrix) {
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    TDynamicMatrix<int> m2(2);
    m2[0][0] = 5; m2[0][1] = 6; /* 1*5+2*7 = 19 1*6+2*8 = 22 3*5+4*7 = 43 3*6+4*8 = 50 вроде бы?*/
    m2[1][0] = 7; m2[1][1] = 8;

    TDynamicMatrix<int> res = m1 * m2;

    EXPECT_EQ(19, res[0][0]);
    EXPECT_EQ(22, res[0][1]);
    EXPECT_EQ(43, res[1][0]);
    EXPECT_EQ(50, res[1][1]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    TDynamicMatrix<int> res = m * 5;

    EXPECT_EQ(5, res[0][0]);
    EXPECT_EQ(10, res[0][1]);
    EXPECT_EQ(15, res[1][0]);
    EXPECT_EQ(20, res[1][1]);
}

TEST(TDynamicMatrix, can_multiply_by_zero_scalar) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 5; m[0][1] = 6;
    m[1][0] = 7; m[1][1] = 8;
    
    TDynamicMatrix<int> res = m * 0;
    
    EXPECT_EQ(0, res[0][0]);
    EXPECT_EQ(0, res[0][1]);
    EXPECT_EQ(0, res[1][0]);
    EXPECT_EQ(0, res[1][1]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    TDynamicVector<int> v(2);
    v[0] = 5; v[1] = 6;

    TDynamicVector<int> res = m * v;

    EXPECT_EQ(17, res[0]);   /*1*5 + 2*6 = 5 + 12 = 17 3*5 + 4*6 = 15 + 24 = 39 вроде в это хочется поверить*/
    EXPECT_EQ(39, res[1]);   
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_different_size) {
    TDynamicMatrix<int> m(2);
    TDynamicVector<int> v(3);

    EXPECT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, multiply_by_edinich_matrix_gives_same_matrix) {
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    
    TDynamicMatrix<int> edinich(2);
    edinich[0][0] = 1; edinich[0][1] = 0;
    edinich[1][0] = 0; edinich[1][1] = 1;
    
    TDynamicMatrix<int> res = m * edinich;
    
    EXPECT_EQ(m, res);
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
//тест на ввод и вывод вроде
TEST(TDynamicMatrix, can_read_and_write_matrix_from_stream) {
    std::stringstream input;
    input << "1 2 3\n";
    input << "4 5 6\n";
    input << "7 8 9\n";
    
    TDynamicMatrix<int> m(3);
    input >> m;
    
    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[0][1]);
    EXPECT_EQ(3, m[0][2]);
    EXPECT_EQ(4, m[1][0]);
    EXPECT_EQ(5, m[1][1]);
    EXPECT_EQ(6, m[1][2]);
    EXPECT_EQ(7, m[2][0]);
    EXPECT_EQ(8, m[2][1]);
    EXPECT_EQ(9, m[2][2]);
    
    std::stringstream output;
    output << m;
    
    TDynamicMatrix<int> m2(3);
    output >> m2;
    
    EXPECT_EQ(m, m2);
}