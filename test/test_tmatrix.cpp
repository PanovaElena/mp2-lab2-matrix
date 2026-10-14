#include "tmatrix.h"
#include <chrono>
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
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);
	(m[4])[4] = 1;
	EXPECT_EQ((m1[4])[4], 0);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	(m[0])[0] = 1;
	EXPECT_EQ((m[0])[0], 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	EXPECT_ANY_THROW((m.at(-1)).at(-1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	EXPECT_ANY_THROW((m.at(MAX_MATRIX_SIZE + 1)).at(MAX_MATRIX_SIZE + 1) = 1);
}
TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	m = m;
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1=m;
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(4);
	m1 = m;
	EXPECT_EQ(m1.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> v(10);
	TDynamicMatrix<int> v1(8);
	v1 = v;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(10);
	bool b = (m == m1);
	EXPECT_EQ(b, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(10);
	bool b = (m == m);
	EXPECT_EQ(b, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(9);
	bool b = (m == m1);
	EXPECT_EQ(b, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int>m(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			(m[i])[j] = 2;
		}
	}
	TDynamicMatrix<int>m1(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			(m1[i])[j] = 1;
		}
	}
	TDynamicMatrix<int>m2(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			(m2[i])[j] = 3;
		}
	}
	EXPECT_EQ(m + m1, m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int>m(3);
	TDynamicMatrix<int>m1(2);
	EXPECT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int>m(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			(m[i])[j] = 2;
		}
	}
	TDynamicMatrix<int>m1(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			(m1[i])[j] = 1;
		}
	}
	TDynamicMatrix<int>m2(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			(m2[i])[j] = 1;
		}
	}
	EXPECT_EQ(m - m1, m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int>m(3);
	TDynamicMatrix<int>m1(2);
	EXPECT_ANY_THROW(m - m1);
}
TEST(TDynamicMatrix, can_multiple_matrixes_with_equal_size) {
	TDynamicMatrix<int>m(2);
	(m[0])[0] = 2;
	(m[1])[1] = 2;
	TDynamicMatrix<int>m1(2);
	(m1[0])[0] = 3;
	(m1[1])[1] = 3;
	TDynamicMatrix<int>m2(2);
	(m2[0])[0] = 6;
	(m2[1])[1] = 6;
	EXPECT_EQ(m * m1, m2);
}
TEST(TDynamicMatrix, cannot_multiple_matrixes_with_different_size) {
	TDynamicMatrix<int>m(2);
	TDynamicMatrix<int>m1(3);
	EXPECT_ANY_THROW(m * m1);
}
TEST(TDynamicMatrix, can_multiple_matrixes_with_equal_size_by_second_way) {
	TDynamicMatrix<int>m(2);
	(m[0])[0] = 2;
	(m[1])[1] = 2;
	TDynamicMatrix<int>m1(2);
	(m1[0])[0] = 3;
	(m1[1])[1] = 3;
	TDynamicMatrix<int>m2(2);
	(m2[0])[0] = 6;
	(m2[1])[1] = 6;
	EXPECT_EQ(m.mult2(m1), m2);
}
TEST(TDynamicMatrix, cannot_multiple_matrixes_with_different_size_even_by_second_way) {
	TDynamicMatrix<int>m(2);
	TDynamicMatrix<int>m1(3);
	EXPECT_ANY_THROW(m.mult2(m1));
}
/*TEST(TDynamicMatrix, cycles_replacing_make_multiple_faster) {
	TDynamicMatrix<double>m(1000);
	for (size_t i = 0; i < 1000; i++) {
		for (size_t j = 0; j < 1000; j++) {
			(m[i])[j] = (i + j) % 10 + 1;
		}
	}
	TDynamicMatrix<double>m1(1000);
	for (size_t i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			(m1[i])[j] = (i + j) % 10 + 1;
		}
	}
	TDynamicMatrix<double>m2(1000);
	std::chrono::duration<double, std::milli> res{ 0 };
	for (size_t k = 0; k < 5; k++) {
		auto start = std::chrono::steady_clock::now();
		m2 = m * m1;
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end-start;
		res = res + elapsed;
	}
	res = res / 5;
	std::chrono::duration<double, std::milli> res2{ 0 };
	for (size_t k = 0; k < 5; k++) {
		auto start = std::chrono::steady_clock::now();
		m2 = m.mult2(m1);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		res2 = res2 + elapsed;
	}
	res2 = res2 / 5;
	std::cout << "Standart multiple: " << res.count() << "\n" << "Time by cycles replacing: " << res2.count() << "\n";
	double diff = res / res2;
	EXPECT_GE(diff, 1.5);
}*/

