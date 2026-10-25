// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор — шаблонный вектор на динамической памяти.
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
      throw std::out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw std::length_error("Vector size is too large");
    pMem = new T[sz]();
  }

  TDynamicVector(T* arr, size_t s) : sz(s), pMem(nullptr)
  {
    if (sz == 0)
      throw std::out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw std::length_error("Vector size is too large");
    if (arr == nullptr)
      throw std::invalid_argument("Source array must not be null");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
    if (sz != 0)
      std::copy(v.pMem, v.pMem + sz, pMem);
  }

  TDynamicVector(TDynamicVector&& v) noexcept
  {
    sz = v.sz;
    pMem = v.pMem;
    v.sz = 0;
    v.pMem = nullptr;
  }

  ~TDynamicVector()
  {
    delete[] pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this != &v)
    {
      TDynamicVector copy(v);
      swap(*this, copy);
    }
    return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this != &v)
    {
      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
    }
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // Индексация с проверкой границ.
  T& operator[](size_t ind)
  {
    if (ind >= sz)
      throw std::out_of_range("Vector index is out of range");
    return pMem[ind];
  }

  const T& operator[](size_t ind) const
  {
    if (ind >= sz)
      throw std::out_of_range("Vector index is out of range");
    return pMem[ind];
  }

  // Индексация с контролем границ.
  T& at(size_t ind)
  {
    if (ind >= sz)
      throw std::out_of_range("Vector index is out of range");
    return pMem[ind];
  }

  const T& at(size_t ind) const
  {
    if (ind >= sz)
      throw std::out_of_range("Vector index is out of range");
    return pMem[ind];
  }

  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return false;
    for (size_t i = 0; i < sz; ++i)
      if (pMem[i] != v.pMem[i])
        return false;
    return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  TDynamicVector operator+(T val) const
  {
    TDynamicVector result(sz);
    for (size_t i = 0; i < sz; ++i)
      result[i] = pMem[i] + val;
    return result;
  }

  TDynamicVector operator-(double val) const
  {
    TDynamicVector result(sz);
    for (size_t i = 0; i < sz; ++i)
      result[i] = pMem[i] - val;
    return result;
  }

  TDynamicVector operator*(double val) const
  {
    TDynamicVector result(sz);
    for (size_t i = 0; i < sz; ++i)
      result[i] = pMem[i] * val;
    return result;
  }

  TDynamicVector operator+(const TDynamicVector& v) const
  {
    checkSameSize(v);
    TDynamicVector result(sz);
    for (size_t i = 0; i < sz; ++i)
      result[i] = pMem[i] + v.pMem[i];
    return result;
  }

  TDynamicVector operator-(const TDynamicVector& v) const
  {
    checkSameSize(v);
    TDynamicVector result(sz);
    for (size_t i = 0; i < sz; ++i)
      result[i] = pMem[i] - v.pMem[i];
    return result;
  }

  T operator*(const TDynamicVector& v) const
  {
    checkSameSize(v);
    T result{};
    for (size_t i = 0; i < sz; ++i)
      result += pMem[i] * v.pMem[i];
    return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; ++i)
      istr >> v.pMem[i];
    return istr;
  }

  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; ++i)
      ostr << v.pMem[i] << ' ';
    return ostr;
  }

private:
  void checkSameSize(const TDynamicVector& v) const
  {
    if (sz != v.sz)
      throw std::invalid_argument("Vector sizes must match");
  }
};

// Квадратная матрица хранится как вектор строк.
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;

public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(checkedSize(s))
  {
    for (size_t i = 0; i < sz; ++i)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if (sz != m.sz)
      return false;
    for (size_t i = 0; i < sz; ++i)
      if (pMem[i] != m.pMem[i])
        return false;
    return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
    return !(*this == m);
  }

  TDynamicMatrix<T> operator*(const T& val) const
  {
    TDynamicMatrix<T> result(sz);
    for (size_t i = 0; i < sz; ++i)
      for (size_t j = 0; j < sz; ++j)
        result[i][j] = pMem[i][j] * val;
    return result;
  }

  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
    if (v.size() != sz)
      throw std::invalid_argument("Matrix and vector sizes must match");
    TDynamicVector<T> result(sz);
    for (size_t i = 0; i < sz; ++i)
      result[i] = pMem[i] * v;
    return result;
  }

  TDynamicMatrix operator+(const TDynamicMatrix& m) const
  {
    checkSameSize(m);
    TDynamicMatrix result(sz);
    for (size_t i = 0; i < sz; ++i)
      result[i] = pMem[i] + m.pMem[i];
    return result;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m) const
  {
    checkSameSize(m);
    TDynamicMatrix result(sz);
    for (size_t i = 0; i < sz; ++i)
      result[i] = pMem[i] - m.pMem[i];
    return result;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
    checkSameSize(m);
    TDynamicMatrix result(sz);
    for (size_t i = 0; i < sz; ++i)
    {
      for (size_t j = 0; j < sz; ++j)
      {
        T sum{};
        for (size_t k = 0; k < sz; ++k)
          sum += pMem[i][k] * m.pMem[k][j];
        result[i][j] = sum;
      }
    }
    return result;
  }

  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& m)
  {
    for (size_t i = 0; i < m.sz; ++i)
      istr >> m.pMem[i];
    return istr;
  }

  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& m)
  {
    for (size_t i = 0; i < m.sz; ++i)
      ostr << m.pMem[i] << '\n';
    return ostr;
  }

private:
  static size_t checkedSize(size_t size)
  {
    if (size == 0)
      throw std::out_of_range("Matrix size should be greater than zero");
    if (size > MAX_MATRIX_SIZE)
      throw std::length_error("Matrix size is too large");
    return size;
  }

  void checkSameSize(const TDynamicMatrix& m) const
  {
    if (sz != m.sz)
      throw std::invalid_argument("Matrix sizes must match");
  }
};

#endif
