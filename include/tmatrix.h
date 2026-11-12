// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

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
    if (sz <= 0)
      throw "Vector size should be greater than zero";
    if (sz > MAX_VECTOR_SIZE)
        throw "Vector size is too large";
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
      this->sz = v.sz;
      this->pMem = new T[sz]();
      for (int i = 0; i < v.sz; i++) {
          this->pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->sz = v.sz;
      this->pMem = new T[sz]();
      for (int i = 0; i < v.sz; i++) {
          this->pMem[i] = v.pMem[i];
      }
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
        return *this;
    this->sz = v.sz;
    this->pMem = new T[sz]();
    for (int i = 0; i < v.sz; i++) {
        this->pMem[i] = v.pMem[i];
    }
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this == &v)
        return *this;
    this->sz = v.sz;
    this->pMem = new T[sz]();
    for (int i = 0; i < v.sz; i++) {
        this->pMem[i] = v.pMem[i];
    }
    v.sz = 0;
    v.pMem = nullptr;
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return this->pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return this->pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0)
          throw "Error: index must be greater than 0";
      if (ind >= this->sz)
          throw "Error: index mustn't be greater than vector's max size";
      return this->pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0)
          throw "Error: index must be greater than 0";
      if (ind >= this->sz)
          throw "Error: index mustn't be greater than vector's max size";
      return this->pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (this->sz!=v.sz)
        return false;
    else {
        bool flag = true;
        for (int i = 0; i < v.sz; i++) {
            if (this->pMem[i] != v.pMem[i]) {
                flag = false;
                break;
            }
        }
        return flag;
    }
  }
  bool operator!=(const TDynamicVector& v) const noexcept {
      return !(*this == v);
  }
  // скалярные операции
  TDynamicVector operator+(double val)
  {
    TDynamicVector newVector(this->sz);
    for (int i = 0; i < this->sz; i++)
        newVector.pMem[i] = this->pMem[i] + val;
    return newVector;
  }
  TDynamicVector operator-(double val)
  {
      TDynamicVector newVector(this->sz);
      for (int i = 0; i < this->sz; i++)
          newVector.pMem[i] = this->pMem[i] - val;
      return newVector;
  }
  TDynamicVector operator*(double val)
  {
      TDynamicVector newVector(this->sz);
      for (int i = 0; i < this->sz; i++)
          newVector.pMem[i] = this->pMem[i] * val;
      return newVector;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (this->sz != v.size())
        throw "Error: sizes of vectors to be summarized are not equal";
    TDynamicVector newVector(this->sz);
    for (int i = 0; i < this->sz; i++)
        newVector.pMem[i] = this->pMem[i] + v.pMem[i];
    return newVector;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (this->sz != v.size())
          throw "Error: sizes of vectors to be substracted are not equal";
      TDynamicVector newVector(this->sz);
      for (int i = 0; i < this->sz; i++)
          newVector.pMem[i] = this->pMem[i] - v.pMem[i];
      return newVector;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
    if (this->sz != v.sz)
        throw "Error: sizes of vectors to be multipied are not equal";
    T product = 0;
    for (int i = 0; i < this->sz; i++) {
        product+=this->pMem[i]*v.pMem[i];
    }
    return product;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
        istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
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
    if (sz <= 0)
        throw std::out_of_range("Matrix size should be greater than zero");
    if (sz > MAX_MATRIX_SIZE)
        throw std::out_of_range("Matrix size is too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if (this->sz!=m.sz)
        return false;
    else {
        bool flag = true;
        for (int i = 0; i < this->sz; i++) {
            if (this->pMem[i] != m.pMem[i]) {
                flag = false;
                break;
            }
        }
        return flag;
    }
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
      TDynamicMatrix<T> NewMatrix(this->sz);
      for (int i = 0; i < this->sz; i++) {
          NewMatrix.pMem[i] = this->pMem[i] * val;
      }
      return NewMatrix;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (this->sz != v.sz)
        throw std::invalid_argument("Error: Matrix and vector sizes are not equal");
    TDynamicVector<T> NewMatrix(sz);
    for (size_t i = 0; i < sz; i++) {
        NewMatrix[i] = this->pMem[i] * v;
    }
    return NewMatrix;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    // можно ли написать реализацию, используя operator+ вектора?
      if (this->sz != m.sz)
          throw std::invalid_argument("Error: Matrix sizes are not equal");
      TDynamicMatrix<T> NewMatrix(sz);
      for (size_t i = 0; i < sz; i++) {
          NewMatrix[i] = this->pMem[i] + m.pMem[i];
      }
      return NewMatrix;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (this->sz != m.sz)
          throw std::invalid_argument("Error: Matrix sizes are not equal");
      TDynamicMatrix<T> NewMatrix(sz);
      for (size_t i = 0; i < sz; i++) {
          NewMatrix[i] = this->pMem[i] - m.pMem[i];
      }
      return NewMatrix;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (this->pMem[0].sz!=m.sz)
        throw std::invalid_argument("Error: First matrix length does not equal second matrix height");
    TDynamicMatrix<T> NewMatrix(this->sz);
    return TDynamicMatrix<T>{};
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++) {
        istr >> v.pMem[i];
    }
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
        ostr << v.pMem[i] << std::endl; // требуется оператор<< для типа T
    return ostr; 
  }
};

#endif
