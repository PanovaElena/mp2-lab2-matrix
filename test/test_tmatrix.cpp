#include "tmatrix.h"

#include <gtest.h>
#include <chrono>
#include <iostream>

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
	TDynamicMatrix<int> m(3);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			m[i][j] = i * 3 + j;
	TDynamicMatrix<int> mc(m);
	EXPECT_EQ(3, mc.size());
	EXPECT_TRUE(m == mc);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2; m[1][0] = 2; m[1][1] = 3;
	TDynamicMatrix<int> mc(m);
	mc[0][0] = 10;
	EXPECT_EQ(1, m[0][0]);
	EXPECT_EQ(10, mc[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(4);
	EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	m[1][2] = 37;
	EXPECT_EQ(37, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);
	ASSERT_ANY_THROW(m.at(3));
	ASSERT_ANY_THROW(m.at(100));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
	TDynamicMatrix<int> original(m);
	m = m;
	EXPECT_TRUE(m == original);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
	b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;
	a = b;
	EXPECT_TRUE(a == b);
	EXPECT_EQ(5, a[0][0]);
	EXPECT_EQ(8, a[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> a(2), b(4);
	a = b;
	EXPECT_EQ(4, a.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> a(2), b(3);
	a[0][0] = 1;
	b[0][0] = 10; b[2][2] = 30;
	a = b;
	EXPECT_EQ(3, a.size());
	EXPECT_EQ(10, a[0][0]);
	EXPECT_EQ(30, a[2][2]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
	b[0][0] = 1; b[0][1] = 2; b[1][0] = 3; b[1][1] = 4;
	EXPECT_TRUE(a == b);
	EXPECT_FALSE(a != b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> a(2), b(3);
	EXPECT_FALSE(a == b);
	EXPECT_TRUE(a != b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
	b[0][0] = 10; b[0][1] = 20; b[1][0] = 30; b[1][1] = 40;
	TDynamicMatrix<int> res = a + b;
	EXPECT_EQ(11, res[0][0]);
	EXPECT_EQ(22, res[0][1]);
	EXPECT_EQ(33, res[1][0]);
	EXPECT_EQ(44, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> a(2), b(3);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 10; a[0][1] = 20; a[1][0] = 30; a[1][1] = 40;
	b[0][0] = 1;  b[0][1] = 2;  b[1][0] = 3;  b[1][1] = 4;
	TDynamicMatrix<int> res = a - b;
	EXPECT_EQ(9, res[0][0]);
	EXPECT_EQ(18, res[0][1]);
	EXPECT_EQ(27, res[1][0]);
	EXPECT_EQ(36, res[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> a(2), b(3);
	ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;
	TDynamicVector<int> v(2);
	v[0] = 5; v[1] = 6;
	auto res = m * v;
	EXPECT_EQ(17, res[0]);
	EXPECT_EQ(39, res[1]);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_wrong_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicVector<int> v(3);
	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices)
{
	TDynamicMatrix<int> a(2), b(2);
	a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
	b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;
	auto res = a * b;
	EXPECT_EQ(19, res[0][0]);
	EXPECT_EQ(22, res[0][1]);
	EXPECT_EQ(43, res[1][0]);
	EXPECT_EQ(50, res[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_wrong_size)
{
	TDynamicMatrix<int> a(2), b(3);
	ASSERT_ANY_THROW(a * b);
}

TEST(TDynamicMatrix, all_multiplication_versions_give_same_result)
{
	const size_t n = 32;
	TDynamicMatrix<int> a(n), b(n);
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j) {
			a[i][j] = (int)(i + j + 1);
			b[i][j] = (int)(i * 2 + j + 1);
		}

	TDynamicMatrix<int> r = a.multipy_slow(b);
	EXPECT_TRUE(r == a.multipy_fast(b));
	EXPECT_TRUE(r == a.multipy_blocked(b));
	EXPECT_TRUE(r == a.multipy_omp(b));
}

// clock врёт для OpenMP, поэтому использую std::chrono, а не clock как в лабе на сортировки
namespace {
	template<typename F>
	double bench_ms(F&& f)
	{
		auto t0 = std::chrono::high_resolution_clock::now();
		f();
		auto t1 = std::chrono::high_resolution_clock::now();
		return std::chrono::duration<double, std::milli>(t1 - t0).count();
	}
} // namespace

TEST(TDynamicMatrix, benchmark_int)
{
	std::cout << "\n=== Benchmark: int ===\n";
	std::cout << "n\tslow(ms)\tfast(ms)\tblocked(ms)\tomp(ms)\n";

	for (size_t n : {100, 200, 400}) {
		TDynamicMatrix<int> a(n), b(n);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j) {
				a[i][j] = (int)(i + j + 1);
				b[i][j] = (int)(i * 2 + j + 1);
			}

		std::cout << n
			<< "\t" << bench_ms([&] { a.multipy_slow(b);   })
			<< "\t\t" << bench_ms([&] { a.multipy_fast(b);    })
			<< "\t\t" << bench_ms([&] { a.multipy_blocked(b); })
			<< "\t\t" << bench_ms([&] { a.multipy_omp(b);     })
			<< "\n";
	}
}

TEST(TDynamicMatrix, benchmark_double)
{
	std::cout << "\n=== Benchmark: double ===\n";
	std::cout << "n\tslow(ms)\tfast(ms)\tblocked(ms)\tomp(ms)\n";

	for (size_t n : {100, 200, 400}) {
		TDynamicMatrix<double> a(n), b(n);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j) {
				a[i][j] = (double)(i + j + 1) * 0.5;
				b[i][j] = (double)(i * 2 + j + 1) * 0.5;
			}

		std::cout << n
			<< "\t" << bench_ms([&] { a.multipy_slow(b);   })
			<< "\t\t" << bench_ms([&] { a.multipy_fast(b);    })
			<< "\t\t" << bench_ms([&] { a.multipy_blocked(b); })
			<< "\t\t" << bench_ms([&] { a.multipy_omp(b);     })
			<< "\n";
	}
}
