
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cassert>
using namespace std;

const size_t MAX_VECTOR_SIZE = 100000000;
const size_t MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size is out of allowed range");
    pMem = new T[sz]();
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if (sz == 0 || sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size is out of allowed range");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
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
    pMem = nullptr;
    sz = 0;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v) return *this;
    TDynamicVector tmp(v);
    swap(*this, tmp);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this == &v) {
      return *this;
    }
    delete[] pMem;
    sz = v.sz;
    pMem = v.pMem;
    v.sz = 0;
    v.pMem = nullptr;
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
    if (ind >= sz) {
      throw out_of_range("Vector index out of range");
    }
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz) {
      throw out_of_range("Vector index out of range");
    }
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz) { return false;}
    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != v.pMem[i]) {return false;}
    }
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val) {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] + val;
    }
    return res;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] - val;
    }
    return res;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] * val;
    }
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz) {
      throw logic_error("Different vector lengths");
    }
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] + v.pMem[i];
    }
    return res;
  }
  TDynamicVector operator-(const TDynamicVector& v) {
    if (sz != v.sz) {
      throw logic_error("Different vector lengths");
    }
    TDynamicVector res(sz);
    for (size_t i = 0 ; i < sz; i++) {
      res.pMem[i] = pMem[i] - v.pMem[i];
    }
    return res;
  }

  T operator*(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw logic_error("Different vector lengths");
    T res{};
    for (size_t i = 0; i < sz; ++i)
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
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s == 0 || s > MAX_MATRIX_SIZE)
      throw out_of_range("Matrix size is out of allowed range");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept {
    if (sz != m.sz) { return false;}
    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != m.pMem[i]){ return false;}
    }
    return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) const
  {
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; ++i)
      for (size_t j = 0; j < sz; ++j)
        res[i][j] = (*this)[i][j] * val;
    return res;
  }
  // матрично-векторные операции
  //v столбец
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (sz != v.size()){ throw "Size matrix != size vector";}
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      res[i] = pMem[i] * v;
    }
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.sz) {throw "matrix size different!";}
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] + m.pMem[i];
    }
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.sz) { throw "matrix size different!";}
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++) {
      res.pMem[i] = pMem[i] - m.pMem[i];
    }
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz) throw ("Matrix size different");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++) {
        res[i][j] = T{};
        for (size_t k = 0; k < sz; k++)
          res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
      }
    return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      for (size_t j = 0; j < v.sz; j++)
        istr >> v[i][j];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
    {
      for (size_t j = 0; j < v.sz; j++)
        ostr << v[i][j] << ' ';
      ostr << '\n';
    }
    return ostr;
  }
};

#endif
