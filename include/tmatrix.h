// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <type_traits>
#include <cmath>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
const int FLOAT_EPSILON = 1e-6;
const int DOUBLE_EPSILON = 1e-14;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz = 0;
  T* pMem = nullptr;
public:
  TDynamicVector(size_t s = 1) : sz(s)
  {
      if (sz == 0)
          throw out_of_range("Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE)
          throw out_of_range("Vector is too large");
      pMem = new T[sz]();
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      if (sz > MAX_VECTOR_SIZE)
          throw out_of_range("Vector is too large");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
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
          if (sz != v.sz)
          {
              delete[] pMem;
              sz = v.sz;
              pMem = new T[sz];
          }
          std::copy(v.pMem, v.pMem + sz, pMem);
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
      if(ind >= 0 && ind < sz)
          return pMem[ind];
      else
          throw out_of_range("Index out of range");
  }
  const T& at(size_t ind) const
  {
      if (ind >= 0 && ind < sz)
          return pMem[ind];
      else
          throw out_of_range("Index out of range");
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++)
      {
          if (std::is_integral<T>::value)
          {
              if (pMem[i] != v.pMem[i])
                  return false;
          }
          else if (std::is_same<T, float>::value)
          {
              if (std::abs(pMem[i] - v.pMem[i]) > static_cast<T>(FLOAT_EPSILON))
                  return false;
          }
          else if (std::is_same<T, double>::value)
          {
              if (std::abs(pMem[i] - v.pMem[i]) > static_cast<T>(DOUBLE_EPSILON))
                  return false;
          }
          else
          {
              if (pMem[i] != v.pMem[i]) return false;
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
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw invalid_argument("Vector sizes are not EQ");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw invalid_argument("Vector sizes are not EQ");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] - v.pMem[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw invalid_argument("Vector sizes are not EQ");
      T result = T();
      for (size_t i = 0; i < sz; i++)
      {
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
      istr >> v.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' ';
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
  TDynamicMatrix(size_t s = 1)
  {
      if (s <= 0)
          throw out_of_range("Matrix size should be greater than zero");
      if (s > MAX_MATRIX_SIZE)
          throw out_of_range("Matrix is too large");
      this->sz = s;
      this->pMem = new TDynamicVector<T>[s];
      for (size_t i = 0; i < sz; i++)
      {
          pMem[i] = TDynamicVector<T>(sz);
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  size_t size() const noexcept { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (size_t i = 0; i < sz; i++)
      {
          if (pMem[i] != m.pMem[i]) return false;
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
      TDynamicVector<T> res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] * val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size())
          throw invalid_argument("Matrix and vector must be equal");
      TDynamicVector<T> res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = T();
          for (size_t j = 0; j < sz; j++)
          {
              res[i] += pMem[i][j] * v[j];
          }
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] + m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] - m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.size())
          throw invalid_argument("Matrix1 and Matrix2 must be equal n1 and m2");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
      {
          for (size_t j = 0; j < sz; j++)
          {
              res[i][j] = T();
              for (size_t k = 0; k < sz; k++)
              {
                  res[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
      {
          for (size_t j = 0; j < m.sz; j++)
          {
              istr >> m.pMem[i][j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; i++)
      {
          for (size_t j = 0; j < m.sz; j++)
          {
              ostr << m.pMem[i][j] << ' ';
          }
          ostr << endl;
      }
      return ostr;
  }
};

#endif
