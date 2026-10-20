// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

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

      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind > sz) //по идее убрать
          throw out_of_range("Index out of range");

      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind > sz)//и это тоже убрать
          throw out_of_range("Index out of range");

      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind > sz)
          throw out_of_range("Index out of range");

      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind > sz)
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
      if (sz != v.sz)
          return true;

      for (size_t i = 0; i < sz; i++)
      {
          if (pMem[i] != v.pMem[i])
              return true
      }
      return false;
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
          res = pMem[i] * v.pMem[i];

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
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
