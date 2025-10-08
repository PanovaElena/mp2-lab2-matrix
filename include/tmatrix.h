// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz = 0;
  T* pMem = nullptr;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if(sz > MAX_VECTOR_SIZE) throw out_of_range("Error");

    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if(sz > MAX_VECTOR_SIZE) throw out_of_range("Error");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
    pMem = new T[sz];
    std::copy(v.pMem,v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
    v.sz = 0;
    v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this != &v) {
      if (sz != v.sz) {
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
    if (this != &v) {
      delete[] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
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
    if(ind >= 0 && ind < sz) return pMem[ind];
    else throw out_of_range("Error");
  }
  const T& at(size_t ind) const
  {
    if(ind >= 0 && ind < sz) return pMem[ind];
    else throw out_of_range("Error");
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    return sz == v.sz && std::equal(pMem, pMem + sz, v.pMem);
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
      res[i] = pMem[i] + val;
    return res;
  }
  TDynamicVector operator-(T val)//?
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] - val;
    return res;
  }
  TDynamicVector operator*(T val)//?
  {
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] * val;
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if(sz != v.sz) throw invalid_argument("Error");

    TDynamicVector res(sz);
    for(size_t i = 0; i < sz; i++)
      res[i] = pMem[i] + v.pMem[i];
    
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if(sz != v.sz) throw invalid_argument("Error");

     TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] - v.pMem[i];

    return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    if(sz != v.sz) throw invalid_argument("Error");

    T res = T();
    for (size_t i = 0; i < sz; i++)
      res += pMem[i] * v.pMem[i];
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
    if(s > MAX_MATRIX_SIZE) throw out_of_range("Error");

    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  size_t size() const noexcept { return sz; } //?

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
     if (sz != m.sz) return false;
    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != m.pMem[i]) return false;
    }
    return true;
  }

   bool operator!=(const TDynamicMatrix& m) const noexcept
  {
    return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) 
    {
        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] * val;
        return res;
    }

  //operator+ and operator- not needed?

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if(sz != v.size()) throw invalid_argument("Error");

    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] * v;
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.sz) throw invalid_argument("Error");
    
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] + m[i];
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.sz) throw invalid_argument("Error");
    
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      res[i] = pMem[i] - m[i];
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
     if (sz != m.size()) throw invalid_argument("Error");
    
    TDynamicMatrix res(sz);
    
    for (size_t row = 0; row < sz; row++) {          
        for (size_t col = 0; col < sz; col++) {      
            T skal = T();                       
            
            for (size_t k = 0; k < sz; k++) { 
                skal += (*this)[row][k] * m[k][col];
            }
            
            res[row][col] = skal;
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
    for (size_t i = 0; i < v.sz; i++) {
      for (size_t j = 0; j < v.sz; j++)
        ostr << v.pMem[i][j] << ' ';
      ostr << '\n';
    }
    return ostr;
  }
  
};

#endif
