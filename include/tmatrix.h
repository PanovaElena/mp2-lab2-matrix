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
    if (sz > MAX_VECTOR_SIZE) {
        throw "Error";
    }
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if (sz > MAX_VECTOR - SIZE) {
        throw "Error";
    }
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v): sz(v.sz)
  {
      if (v.pMem==nullptr) {
          pMem = nullptr;
          return;
      }
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + v.sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept: pMem(v.pMem), sz(v.sz)
  {
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
      if (this == &v) {
          return *this;
      }
      delete[] pMem;
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
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
      v.pMem = nullptr;
      v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  T* data() {
      return pMem;
  }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind>=0 && ind < sz) {
          return pMem[ind];
      }
      throw "Error: incorrect index";
  }
  const T& operator[](size_t ind) const
  {
      if (ind >= 0 && ind < sz) {
          return pMem[ind];
      }
      throw "Error: incorrect index";
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= 0 && ind < sz) {
          return pMem[ind];
      }
      throw "Error: incorrect index";
  }
  const T& at(size_t ind) const
  {
      if (ind >= 0 && ind < sz) {
          return pMem[ind];
      }
      throw "Error: incorrect index";
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
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
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] + val;
      }
      return result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] - val;
      }
      return result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] * val;
      }
      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz!=v.sz) {
          throw "Error";
      }
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] + v.pMem[i];
      }
      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw "Error";
      }
      TDynamicVector result(sz);
      for (size_t i = 0; i < sz; i++) {
          result[i] = pMem[i] - v.pMem[i];
      }
      return result;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          return T();
      }
      T result = T();
      for (size_t i = 0; i < sz; i++) {
          result += pMem[i] * v.pMem[i];
      }
      return result;
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
      if (s > MAX_MATRIX_SIZE) {
          throw "Error";
      }
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  TDynamicMatrix(const TDynamicMatrix& m):TDynamicVector<TDynamicVector<T>>(m.sz) {
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = m.pMem[i];
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) {
          return false;
      }
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              if (pMem[i][j] != m.pMem[i][j]) {
                  return false;
              }
          }
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
      TDynamicMatrix<T> result(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              result[i][j] *= val;
          }
      }
      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz) {
          throw "Error";
      }
      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i] += pMem[i][j] * v[j];
          }
      }
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw "Error";
      }
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i][j] = pMem[i][j] + m.pMem[i][j];
          }
      }
      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw "Error";
      }
      TDynamicMatrix result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              result[i][j] = pMem[i][j] - m.pMem[i][j];
          }
      }
      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw "Error";
      }
      TDynamicMatrix<T> result(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              for (size_t k = 0; k < sz; k++) {
                  result[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              istr >> v.pMem[i][j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              ostr << v.pMem[i][j] << ' ';
          }
      }
      return ostr;
  }
};

#endif
