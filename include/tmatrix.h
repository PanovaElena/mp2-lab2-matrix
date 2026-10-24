// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size is too big");

    pMem = new T[sz]();
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    if (arr == nullptr)
        throw invalid_argument("arr must not be nullptr");
    if (sz == 0)
        throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size is too big");

    pMem = new T[sz];

    for (size_t i = 0; i < sz; i++)
        pMem[i] = arr[i];
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];

      for (size_t i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v)
      {
          T* Mem = new T[v.sz];

              for (size_t i = 0; i < v.sz; i++) 
                Mem[i] = v.pMem[i];
              
          delete[] pMem;

          pMem = Mem;
          sz = v.sz;
      }

      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) 
      {
          delete[] pMem;

          pMem = v.pMem;
          sz = v.sz;

          v.pMem = nullptr;
          v.sz = 0;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");

      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");

      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return false;

      for (size_t i = 0; i < sz; i++) 
      {
          if (pMem[i] != v.pMem[i])
              return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);

      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + val;

      return res;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector res(sz);

      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - val;

      return res;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector res(sz);

      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * val;

      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw ("Vectors must be of the same size");

      TDynamicVector res(sz);

      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + v.pMem[i];

      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw ("Vectors must be of the same size");

      TDynamicVector res(sz);

      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - v.pMem[i];

      return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw ("Vectors must be of the same size");

      T res = T();

      for (size_t i = 0; i < sz; i++)
          res = res + pMem[i] * v.pMem[i];

      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

  
public:
    //запоминает лучший размер блока для данного типа T
    static size_t bestBlockSize;

    //метод для замера времени
    template<typename Func>
    static double MeasureTime(Func func, int iterations = 2)
    {
        double totalMs = 0.0;
        for (int i = 0; i < iterations; i++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            func();
            auto end = std::chrono::high_resolution_clock::now();
            totalMs += std::chrono::duration<double, std::milli>(end - start).count();
        }
        return totalMs / iterations;
    }

    //автоматический подбор блока
    static size_t FindOptimalBlockSize()
    {
        //если размер матрицы маленький, блок не нужен
        const size_t TEST_SIZE = 128;

        TDynamicMatrix<T> A(TEST_SIZE), B(TEST_SIZE);

        //заполняем тестовые матрицы случайными числами
        for (size_t i = 0; i < TEST_SIZE; i++) {
            for (size_t j = 0; j < TEST_SIZE; j++) {
                A[i][j] = static_cast<T>(rand() % 100);
                B[i][j] = static_cast<T>(rand() % 100);
            }
        }
        //выполняем умножение 3 раза, чтобы процессор вышел на рабочую частоту
        //а данные загрузились в кэш
        for (int w = 0; w < 3; w++) {
            TDynamicMatrix<T> WarmUp = A.BlockedMultiply(B, 32);
            (void)WarmUp;
        }

        //кандидаты на лучший размер блока
        size_t candidates[] = { 16, 32, 48, 64, 96, 128, 192, 256 };
        size_t bestSize = 32;
        double bestTime = 1e18;

        for (size_t bs : candidates)
        {
            if (bs > TEST_SIZE) continue;

            double time = MeasureTime([&]() {
                TDynamicMatrix<T> C = A.BlockedMultiply(B, bs);
                (void)C; // чтобы компилятор не выкинул вычисления
                });

            if (time < bestTime) {
                bestTime = time;
                bestSize = bs;
            }
        }
        return bestSize;
    }

  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (sz > MAX_MATRIX_SIZE)
          throw out_of_range("Matrix size is too big");

      for (size_t i = 0; i < sz; i++)
        pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
          return false;

      for (size_t i = 0; i < sz; i++) 
      {
          if (pMem[i] != m.pMem[i])
              return false;
      }
      return true;
          
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      TDynamicMatrix<T> res(sz);

      for (size_t i = 0; i < sz; i++)
          res[i] = pMem[i] * val;

      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size())
          throw out_of_range("Size mismatch");

      TDynamicVector<T> res(sz);

      for (size_t i = 0; i < sz; i++)
          res[i] = pMem[i] * v;

      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Size mismatch");

      TDynamicMatrix res(sz);

      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + m.pMem[i];

      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Size mismatch");

      TDynamicMatrix res(sz);

      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - m.pMem[i];

      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      return SimpleMultiply(m);
  }
  //Самая очевидная реализация, медленно, много прыжков по памяти
  TDynamicMatrix SimpleMultiply(const TDynamicMatrix& m) const
  {
      if (sz != m.sz)
          throw out_of_range("Size mismatch");

      TDynamicMatrix res(sz);

      for (size_t i = 0; i < sz; i++)
      {
          for (size_t j = 0; j < sz; j++)
          {
              T sum = T();
              for (size_t k = 0; k < sz; k++)
                  sum = sum + pMem[i][k] * m.pMem[k][j];

              res.pMem[i][j] = sum;
          }
      }
      return res;
  }

  //Немного оптимизировали перестановкой циклов
  //меньше прыжков по памяти, но все еще медленно
  TDynamicMatrix PermutationMultiply(const TDynamicMatrix& m) const
  {
      if (sz != m.sz)
          throw out_of_range("Size mismatch");

      TDynamicMatrix res(sz);

      for (size_t i = 0; i < sz; i++)
      {
          TDynamicVector<T>& resRow = res.pMem[i];

          for (size_t k = 0; k < sz; k++)
          {
              T a = pMem[i][k];

              const TDynamicVector<T>& bRow = m.pMem[k];

              for (size_t j = 0; j < sz; j++)
                  resRow[j] = resRow[j] + a * bRow[j];
          }
      }
      return res;
  }

  TDynamicMatrix BlockedMultiply(const TDynamicMatrix& m, size_t blockSize = 0) const
  {
      if (sz != m.sz)
          throw out_of_range("Size mismatch");

      if (blockSize == 0)
          blockSize = bestBlockSize;

      if (blockSize == 0)
          throw out_of_range("Block size must be > 0");

      TDynamicMatrix res(sz);

      for (size_t bi = 0; bi < sz; bi += blockSize)
      {
          size_t iMax = (bi + blockSize < sz) ? (bi + blockSize) : sz;

          for (size_t bj = 0; bj < sz; bj += blockSize)
          {
              size_t jMax = (bj + blockSize < sz) ? (bj + blockSize) : sz;

              for (size_t bk = 0; bk < sz; bk += blockSize)
              {
                  size_t kMax = (bk + blockSize < sz) ? (bk + blockSize) : sz;

                  for (size_t i = bi; i < iMax; i++)
                  {
                      //берем ссылку на строку результата 
                      TDynamicVector<T>& resRow = res.pMem[i];

                      for (size_t k = bk; k < kMax; k++)
                      {
                          T a = pMem[i][k];

                          //берем ссылку на строку B, так работает намного быстрее
                          const TDynamicVector<T>& bRow = m.pMem[k];

                          for (size_t j = bj; j < jMax; j++)
                          {
                              resRow[j] = resRow[j] + a * bRow[j];
                          }
                      }
                  }
              }
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];

      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << '\n';

      return ostr;
  }

};

template<typename T>
size_t TDynamicMatrix<T>::bestBlockSize = 0;

#endif
