// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "../include/tmatrix.h"
#include <chrono>
//---------------------------------------------------------------------------

int main()
{

#ifdef _OPENMP
  cout << "OpenMP активен, потоков доступно: " << omp_get_max_threads() << endl;
#else
  cout << "OpenMP НЕ активен" << endl;
#endif

  /*
  TDynamicMatrix<int> a(5), b(5), c(5);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl; */

  const size_t N = 10000;
  TDynamicMatrix<int> M1(N), M2(N);
  for (size_t i = 0; i < N; i++)
    for (size_t j = 0; j < N; j++) {
      M1[i][j] = (i + j) % 7;
      M2[i][j] = (i * j + 1) % 5;
    }

  auto start1 = std::chrono::high_resolution_clock::now();
  TDynamicMatrix<int> res1 = M1 * M2;
  auto end1 = std::chrono::high_resolution_clock::now();

  auto start2 = std::chrono::high_resolution_clock::now();
  TDynamicMatrix<int> res2 = M1.blockMultiply(M2);
  auto end2 = std::chrono::high_resolution_clock::now();

  auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
  auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

  auto start3 = std::chrono::high_resolution_clock::now();
  TDynamicMatrix<int> res3 = M1.slowMultiply(M2);
  auto end3 = std::chrono::high_resolution_clock::now();
  auto time3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3).count();

  cout << "Наивное (i,j,k) умножение: " << time3 << " мс" << endl;

  cout << "Размер матрицы: " << N << endl;
  cout << "Медленное умножение: " << time3 << " мс" << endl;
  cout << "Обычное умножение: " << time1 << " мс" << endl;
  //cout << "Блочное без OpenMP:  " << time2 << " мс" << endl;
  cout << "Блочное + OpenMP:  " << time2 << " мс" << endl;
  cout << "Ускорение: " << (double)time1 / time2 << "x" << endl;

}
//---------------------------------------------------------------------------
