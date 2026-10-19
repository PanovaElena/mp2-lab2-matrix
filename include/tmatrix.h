// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <algorithm>

//using namespace std;

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
      throw std::out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw std::length_error("The vector exceeds the maximum size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v): sz(v.sz)
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
      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (&v == this) return *this;
      delete[] pMem;
      sz = v.sz;
      pMem = new T[v.sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (&v == this) return *this;
      delete[] pMem;
      pMem = v.pMem;
      sz = v.sz;
      v.pMem = nullptr;
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
      if (ind >= sz || ind < 0) {
          throw std::out_of_range("index out of range");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0) {
          throw std::out_of_range("index out of range");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (v.sz != sz) return false;
      for (size_t i = 0; i < sz; i++) {
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
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] - val;
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * val;
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (v.sz != sz) throw std::invalid_argument("The vector sizes do not match");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (v.sz != sz) throw std::invalid_argument("The vector sizes do not match");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - v.pMem[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v) const
  {
      if (v.sz != sz) throw std::invalid_argument("The vector sizes do not match");
      T res{};
      for (size_t i = 0; i < sz; i++) res += pMem[i] * v.pMem[i];
      return res;
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
  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& v): TDynamicVector<TDynamicVector<T>>(v) {}//для сложения в 1 строку
  static size_t cheksz(size_t s) { //бросит искл до выделения памяти
      if (s > MAX_MATRIX_SIZE)
          throw std::length_error("The matrix exceeds the maximum size");
      return s;
  }
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(cheksz(s))
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i]) return false;
      }
      return true;
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept //либо забыли, либо не нужен был,но дописал
  {
      return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) const
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] * val;
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
      if(sz != v.size()) throw std::invalid_argument("The vector and matrix sizes do not match");
      TDynamicVector<T> res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = pMem[i] * v;
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {// нужен приватный конструктор(Vector<Vector> -> Matrix)
      return TDynamicMatrix(TDynamicVector<TDynamicVector<T>>::operator+(m));
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      return TDynamicMatrix(TDynamicVector<TDynamicVector<T>>::operator-(m));
  }

  // для сравнения скорости напишем 4 версии умножения*:
  TDynamicMatrix multipy_slow(const TDynamicMatrix& m) const// прыжки по памяти
  {
      if (sz != m.sz)
          throw std::invalid_argument("matrix sizes do not match");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              for (size_t k = 0; k < sz; k++)
                  res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
          }
      }
      return res;
  }
  TDynamicMatrix multipy_fast(const TDynamicMatrix& m) const//последовательно по строке
  {
      if (sz != m.sz)
          throw std::invalid_argument("matrix sizes do not match");
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < sz; k++) {
              T a = pMem[i][k]; //каждый раз лезет в память из-за чего убивает всю скорость-оптимизацию кэша
              for (size_t j = 0; j < sz; j++)
                  res.pMem[i][j] += a * m.pMem[k][j];
          }
      }
      return res;
  }
  TDynamicMatrix multipy_blocked(const TDynamicMatrix& m, size_t block = 64) const//умножать блоками
  {
      if (sz != m.sz)
          throw std::invalid_argument("matrix sizes do not match");
      TDynamicMatrix res(sz);
      for (size_t i2 = 0; i2 < sz; i2 += block)//цикл по блокам строк
          for (size_t k2 = 0; k2 < sz; k2 += block)//цикл по блокам столбцов A/строк B
              for (size_t j2 = 0; j2 < sz; j2 += block)//цикл по блокам столбцов результата
                  for (size_t i = i2; i < std::min(i2 + block, sz); i++)
                      for (size_t j = j2; j < std::min(j2 + block, sz); j++) {
                          T sum = T{}; // накапливаем сумму в регистре
                          for (size_t k = k2; k < std::min(k2 + block, sz); k++)
                              sum += pMem[i][k] * m.pMem[k][j];
                          res.pMem[i][j] += sum;
                      }
      //ускорение, так как прыжки по столбцу происходят внутри быстрой памяти, засчёт ограничения размером блока
      return res;
  }//в итоге данные разбиения помещаются в быструю память, в следствии чего реже обращаемся к медленной
  TDynamicMatrix multipy_omp(const TDynamicMatrix& m) const
  {
      if (sz != m.sz)
          throw std::invalid_argument("matrix sizes do not match");
      TDynamicMatrix res(sz);
      #pragma omp parallel for
      for (long long i2 = 0; i2 < (long long)sz; i2++) {//OpenMP требует знаковый счётчик
          size_t i = (size_t)i2; // убрали повторение
          for (size_t k = 0; k < sz; k++) {
              T a = pMem[i][k];
              for (size_t j = 0; j < sz; j++)
                  res.pMem[i][j] += a * m.pMem[k][j];
          }
      }
      return res;
  }


  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
      return multipy_fast(m);//безопасное и быстрое 
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              istr >> v.pMem[i][j];
      return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++)
              ostr << v.pMem[i][j] << ' ';
          ostr << '\n';
      }
      return ostr;
  }
};

#endif
