#include "tmatrix.h"

#include <gtest.h>
#include <sstream>

// --- Конструкторы ---

TEST(SparseMatrixCoo, can_create_sparse_matrix_with_positive_dimensions)
{
	ASSERT_NO_THROW(SparseMatrixCoo<int> sm(5, 5));
}

TEST(SparseMatrixCoo, throws_when_create_sparse_matrix_with_negative_rows)
{
	ASSERT_ANY_THROW(SparseMatrixCoo<int> sm(-1, 5));
}

TEST(SparseMatrixCoo, throws_when_create_sparse_matrix_with_negative_cols)
{
	ASSERT_ANY_THROW(SparseMatrixCoo<int> sm(5, -1));
}

TEST(SparseMatrixCoo, can_create_from_dense_matrix)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 3;
	m[1][0] = 0; m[1][1] = 5; m[1][2] = 0;
	m[2][0] = 7; m[2][1] = 0; m[2][2] = 9;

	SparseMatrixCoo<int> sm(m);
	EXPECT_EQ(static_cast<size_t>(3), sm.rows());
	EXPECT_EQ(static_cast<size_t>(3), sm.cols());
	EXPECT_EQ(static_cast<size_t>(5), sm.values()); // 5 ненулевых элементов
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			EXPECT_EQ(m[i][j], sm(i, j));
}

TEST(SparseMatrixCoo, from_dense_matrix_skips_zeros)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 0;
	m[1][0] = 0; m[1][1] = 0;

	SparseMatrixCoo<int> sm(m);
	sm.set_element(0, 0, 1);
	EXPECT_EQ(static_cast<size_t>(1), sm.values());
}

// --- Доступ к элементам ---

TEST(SparseMatrixCoo, can_get_nonzero_element)
{
	SparseMatrixCoo<int> sm(3, 3);
	sm.set_element(1, 2, 2);
	EXPECT_EQ(2, sm(1, 2));
}

TEST(SparseMatrixCoo, returns_zero_for_missing_element)
{
	SparseMatrixCoo<int> sm(3, 3);
	sm.set_element(0, 0, 1);
	EXPECT_EQ(0, sm(1, 2));
}

TEST(SparseMatrixCoo, can_get_element_via_at)
{
	SparseMatrixCoo<int> sm(3, 3);
	sm.set_element(2, 2, 5);
	EXPECT_EQ(5, sm.at(2, 2));
}

TEST(SparseMatrixCoo, throws_at_out_of_range)
{
	SparseMatrixCoo<int> sm(3, 3);
	ASSERT_ANY_THROW(sm.at(3, 0));
	ASSERT_ANY_THROW(sm.at(0, 3));
}

// --- Добавление элементов ---

TEST(SparseMatrixCoo, can_set_element)
{
	SparseMatrixCoo<int> sm(3, 3);
	sm.set_element(1, 1, 5);
	EXPECT_EQ(5, sm(1, 1));
	EXPECT_EQ(static_cast<size_t>(1), sm.values());
}

TEST(SparseMatrixCoo, can_update_existing_element)
{
  SparseMatrixCoo<int> sm(3, 3);
  sm.set_element(1, 1, 5);
  sm.set_element(1, 1, 10);
  EXPECT_EQ(10, sm(1, 1));
  EXPECT_EQ(static_cast<size_t>(1), sm.values()); // не дублируется
}

TEST(SparseMatrixCoo, throws_set_element_out_of_range)
{
  SparseMatrixCoo<int> sm(3, 3);
  ASSERT_ANY_THROW(sm.set_element(3, 0, 1));
  ASSERT_ANY_THROW(sm.set_element(0, 3, 1));
}

TEST(SparseMatrixCoo, can_add_multiple_elements)
{
  SparseMatrixCoo<int> sm(3, 3);
  sm.set_element(0, 0, 1);
  sm.set_element(1, 1, 2);
  sm.set_element(2, 2, 3);
  EXPECT_EQ(static_cast<size_t>(3), sm.values());
  EXPECT_EQ(1, sm(0, 0));
  EXPECT_EQ(2, sm(1, 1));
  EXPECT_EQ(3, sm(2, 2));
}

// --- Операции ---

TEST(SparseMatrixCoo, can_add_sparse_matrices)
{
  SparseMatrixCoo<int> sm1(3, 3);
  sm1.set_element(0, 0, 1);
  sm1.set_element(1, 1, 2);

  SparseMatrixCoo<int> sm2(3, 3);
  sm2.set_element(0, 0, 10);
  sm2.set_element(2, 2, 30);

  SparseMatrixCoo<int> res = sm1 + sm2;
  EXPECT_EQ(11, res(0, 0));
  EXPECT_EQ(2, res(1, 1));
  EXPECT_EQ(30, res(2, 2));
}
TEST(SparseMatrixCoo, comparison) {
	SparseMatrixCoo<int> sm1(3, 3);
	sm1.set_element(0, 0, 1);
	sm1.set_element(1, 1, 2);
	SparseMatrixCoo<int> sm2(3, 3);
	sm2.set_element(0, 0, 1);
	sm2.set_element(1, 1, 2);
	SparseMatrixCoo<int> sm3 = sm1 + sm2;
	EXPECT_EQ(sm1, sm2);
	EXPECT_NE(sm1, sm3);
	EXPECT_NE(sm2, sm3);
}

// --- Ввод/вывод ---

TEST(SparseMatrixCoo, can_write_sparse_matrix)
{
  SparseMatrixCoo<int> sm(3, 3);
  sm.set_element(0, 0, 1);
  sm.set_element(1, 1, 2);
  sm.set_element(2, 2, 3);

  std::stringstream sstr;
  sstr << sm;
  std::string result = sstr.str();

  EXPECT_NE(result.find("1"), std::string::npos);
  EXPECT_NE(result.find("2"), std::string::npos);
  EXPECT_NE(result.find("3"), std::string::npos);
}

TEST(SparseMatrixCoo, can_read_sparse_matrix)
{
	SparseMatrixCoo<int> sm(3, 3);

	std::stringstream sstr;
	sstr << "1 0 3 0 5 0 7 0 9";
	sstr >> sm;

	EXPECT_EQ(static_cast<size_t>(5), sm.values());
	EXPECT_EQ(1, sm(0, 0));
	EXPECT_EQ(5, sm(1, 1));
	EXPECT_EQ(9, sm(2, 2));
}

TEST(SparseMatrixCoo, reads_zeros_correctly)
{
  SparseMatrixCoo<int> sm(2, 2);

  std::stringstream sstr;
  sstr << "0 0 0 0";
  sstr >> sm;

  EXPECT_EQ(static_cast<size_t>(0), sm.values());
}

// --- Граничные случаи ---

TEST(SparseMatrixCoo, empty_sparse_matrix_returns_zero)
{
  SparseMatrixCoo<int> sm(5, 5);
  EXPECT_EQ(0, sm(0, 0));
  EXPECT_EQ(0, sm(4, 4));
}

TEST(SparseMatrixCoo, single_element_matrix)
{
  SparseMatrixCoo<int> sm(1, 1);
  sm.set_element(0, 0, 1);
  EXPECT_EQ(1, sm(0, 0));
  EXPECT_EQ(static_cast<size_t>(1), sm.values());
}

TEST(SparseMatrixCoo, rows_and_cols_return_correct_values)
{
  SparseMatrixCoo<int> sm(10, 20);
  EXPECT_EQ(static_cast<size_t>(10), sm.rows());
  EXPECT_EQ(static_cast<size_t>(20), sm.cols());
}

// ---Запись/Чтение
TEST(SparseMatrixCoo, can_write_matrix) {
	SparseMatrixCoo<int> sm(5, 6);
	sm.set_element(3, 4, 1);
	sm.set_element(4, 5, 2);
	std::string expected =
		"0 0 0 0 0 0 \n0 0 0 0 0 0 \n0 0 0 0 0 0 \n0 0 0 0 1 0 \n0 0 0 0 0 2 \n";

	std::stringstream sstr;
	sstr << sm;
	EXPECT_EQ(expected, sstr.str());

}

TEST(SparseMatrixCoo, can_read_matrix) {
	SparseMatrixCoo<int> sm(7, 3);
	SparseMatrixCoo<int> expected(7, 3);
	expected.set_element(0, 0, 1);
	expected.set_element(3, 2, 2);

	std::stringstream sstr;
	std::string str =
		"1 0 0 \n0 0 0 \n0 0 0 \n0 0 2 \n0 0 0 \n0 0 0 \n0 0 0 \n";
	sstr << str;
	sstr >> sm;

	EXPECT_EQ(expected, sm);
}
