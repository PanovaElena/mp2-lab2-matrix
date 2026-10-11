// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <cassert>

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
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s) //создается TDynamicVector из массива С
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg"); // Макрос для поиска багов: если arr равен nullptr, программа упадет и выведет этот текст в консоль
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept // noexcept - чтобы во время перемещения при ошибкене было такого, что старая память уже удалилась, а новая не смогла переместиться из-за исключения
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
    if (this == &v) {
      return *this;
    }
    sz = v.sz;
    delete[] pMem;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this == &v) {
      return *this;
    }
    sz = v.sz;
    delete[] pMem;
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
  T& at(size_t ind) {
    if (ind >= sz) {
      throw out_of_range("Vector index out of bounds");
    }
    return pMem[ind];
  }

  const T& at(size_t ind) const
  {
    if (ind >= sz) {
      throw out_of_range("Vector index out of bounds");
    }
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept // noexcept — для оптимизации при использовании в циклах и тп
  {
    if (sz != v.sz) return false;
    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != v.pMem[i]) return false;
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
    TDynamicVector v(sz);
    for (size_t i = 0; i < sz; i++) {
      v[i] = pMem[i] + val;
    }
    return v;
  }
  TDynamicVector operator-(double val)
  {
    TDynamicVector v(sz);
    for (size_t i = 0; i < sz; i++) {
      v[i] = pMem[i] - val;
    }
    return v;
  }
  TDynamicVector operator*(double val)
  {
    TDynamicVector v(sz);
    for (size_t i = 0; i < sz; i++) {
      v[i] = pMem[i] * val;
    }
    return v;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz) {
      throw out_of_range("Vector size mismatch");
    }
    TDynamicVector tmp{sz};
    for (size_t i = 0; i < sz; i++) {
      tmp[i] = pMem[i] + v.pMem[i];
    }
    return tmp;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz) {
      throw out_of_range("Vector size mismatch");
    }
    TDynamicVector tmp{sz};
    for (size_t i = 0; i < sz; i++) {
      tmp[i] = pMem[i] - v.pMem[i];
    }
    return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T())) //operator* является noexcept тогда и только тогда, когда конструктор по умолчанию типа T сам является noexcept. т.е внутренний noexcept это проверка на noexecept'ность конструктора Т
  {
    T res = T();
    for (size_t i = 0; i < sz; i++) {
      res += pMem[i] * v.pMem[i];
    }
    return res;
  } // но тут же надо бросать исключение в случае несовпадения размеров

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
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> //наследование от конкретизации шаблона
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
