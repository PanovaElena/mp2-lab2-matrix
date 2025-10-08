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
    if(sz > MAX_VECTOR_SIZE) throw "The vector size is too large";
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
		pMem = new T[v.sz];
		for(int i = 0; i < v.sz; ++i) pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    pMem = v.pMem;
    v.pMem = nullptr;
    sz = v.sz;
    v.sz = 0;
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if(&v != this)
    {
      sz = v.sz;
      delete[] pMem;
      pMem = new T[sz];
		  for(int i = 0; i < sz; ++i) pMem[i] = v.pMem[i];
    }
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if(this == &v) return *this;

    delete[] pMem;
    pMem = v.pMem;
    v.pMem = nullptr;
    sz = v.sz;
	  v.sz = 0;
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
    if(ind >= sz || ind < 0) throw "Index out of bounds";
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if(ind >= sz || ind < 0) throw "Index out of bounds";
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector<double>& v) const noexcept
  {
    if(sz != v.sz) return 0;
    for(int i = 0; i < v.sz; ++i) 
      if(std::abs(pMem[i] - v.pMem[i]) > 1e-10) return 0;
    return 1;
  }
  bool operator==(const TDynamicVector<float>& v) const noexcept
  {
    if(sz != v.sz) return 0;
    for(int i = 0; i < v.sz; ++i) 
      if(std::abs(pMem[i] - v.pMem[i]) > (float)(1e-6)) return 0;
    return 1;
  }

  bool operator==(const TDynamicVector<int>& v) const noexcept
  {
    if(sz != v.sz) return 0;
    for(int i = 0; i < v.sz; ++i) 
      if(pMem[i] != v.pMem[i]) return 0;
    return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    for(int i = 0; i < sz; ++i) pMem[i] += val;
    return *this;
  }
  TDynamicVector operator-(double val)
  {
    for(int i = 0; i < sz; ++i) pMem[i] -= val;
    return *this;
  }
  TDynamicVector operator*(double val)
  {
    for(int i = 0; i < sz; ++i) pMem[i] *= val;
    return *this;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if(sz != v.sz) throw "Vectors must have equal sizes for addition";
    TDynamicVector res(sz);
    for(int i = 0; i < sz; ++i) res.pMem[i] = pMem[i] + v.pMem[i];
    return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if(sz != v.sz) throw "Vectors must have equal sizes for subtraction";
    TDynamicVector res(sz);
    for(int i = 0; i < sz; ++i) res.pMem[i] = pMem[i] - v.pMem[i];
    return res;
  }
  T operator*(const TDynamicVector& v)
  {
    if(sz != v.sz) throw "Vectors must have equal sizes for multiplication";
    T res = 0;
    for(int i = 0; i < sz; ++i) res += (pMem[i] * v.pMem[i]);
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
    if(sz > MAX_MATRIX_SIZE) throw "The matrix size is too large";
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  size_t size() const noexcept { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if(sz != m.sz) return 0;
    for(int i = 0; i < sz; ++i) if(pMem[i] != m.pMem[i]) return 0;
    return 1; 
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
    TDynamicMatrix res(sz);
    for(int i = 0; i < sz; ++i) res.pMem[i] = pMem[i] * val;
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    TDynamicVector res(v.sz);
    for(int i = 0; i < sz; ++i)
    {
      for(int j = 0; j < sz; ++j)
      {
        res[i] += pMem[j][i] * v[i];
      }
    }
    return res;
  }
  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    TDynamicMatrix res(sz);
    for(int i = 0; i < sz; ++i) res.pMem[i] = pMem[i] + m.pMem[i];
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    TDynamicMatrix res(sz);
    for(int i = 0; i < sz; ++i) res.pMem[i] = pMem[i] - m.pMem[i];
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if(sz != m.sz) throw "Matrices must have equal sizes for multiplication";
    TDynamicMatrix res(sz);
    for(int i = 0; i < sz; ++i)
      for(int k = 0; k < sz; ++k)
        for(int j = 0; j < sz; ++j)
          res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
    return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for(int i = 0; i < v.sz; ++i) istr >> v.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for(int i = 0; i < v.sz; ++i)
      for(int j = 0; j < v.sz; ++j)
        ostr << v.pMem[i][j] << ' ' << (j == (v.sz - 1) ? "\n" : "");
    return ostr;
  }
};

#endif
