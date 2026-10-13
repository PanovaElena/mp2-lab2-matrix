// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
#include <algorithm>

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
      throw length_error("Vector size is too large");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
    pMem = new T[sz];
    std::copy(v.pMem,v.pMem + sz,pMem);
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
    if (this == &v) return *this;
    if(sz!=v.sz) {
      T* p = new T[v.sz];
      delete[] pMem;
      sz = v.sz;
      pMem = p;
    }
    std::copy(v.pMem,v.pMem + sz, pMem);
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this == &v) return *this;
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
    if (ind >= sz) throw out_of_range("Index out of range");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz) throw out_of_range("Index out of range");
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
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
    TDynamicVector temp(sz);
    for (size_t i =0; i < sz; i++) temp.pMem[i] = pMem[i] + val;
    return temp;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector temp(sz);
    for (size_t i =0; i < sz; i++) temp.pMem[i] = pMem[i] - val;
    return temp;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector temp(sz);
    for (size_t i =0; i < sz; i++) temp.pMem[i] = pMem[i] * val;
    return temp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz) throw invalid_argument("Vectors must be the same size");
    TDynamicVector temp(sz);
    for (size_t i =0; i < sz; i++) temp.pMem[i] = pMem[i] + v.pMem[i];
    return temp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz) throw invalid_argument("Vectors must be the same size");
    TDynamicVector temp(sz);
    for (size_t i =0; i < sz; i++) temp.pMem[i] = pMem[i] - v.pMem[i];
    return temp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    if (sz != v.sz) throw invalid_argument("Vectors must be the same size");
    T res = T();
    for (size_t i =0; i < sz; i++) res += pMem[i] * v.pMem[i];
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
    if (sz > MAX_MATRIX_SIZE)
      throw out_of_range("Matrix size is too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[]; // использование m[i][j], где и - строка, джи элемент
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
    return !(*this == m);
  }


  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(const T& val)
  {
    TDynamicMatrix<T> temp(sz);
    for (size_t i = 0; i < sz ; i++) {
      temp.pMem[i] = pMem[i] * val;
    }
    return temp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (sz != v.size()) throw invalid_argument("Matrix and vector sizes not same");
    TDynamicVector<T> temp(sz);
    for (size_t i = 0; i < sz ; i++) {
      temp[i] = pMem[i] * v;
    }
    return temp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.size()) throw invalid_argument("Matrices must be the same size");
    TDynamicMatrix<T> temp(sz);
    for (size_t i = 0; i < sz ; i++) {
      temp.pMem[i] = pMem[i] + m.pMem[i];
    }
    return temp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.size()) throw invalid_argument("Matrices must be the same size");
    TDynamicMatrix<T> temp(sz);
    for (size_t i = 0; i < sz ; i++) {
      temp.pMem[i] = pMem[i] - m.pMem[i];
    }
    return temp;
  }
  // TDynamicMatrix operator*(const TDynamicMatrix& m)
  // {
  //   if (sz != m.size()) throw invalid_argument("Matrices must be the same size");
  //   TDynamicMatrix<T> temp(sz);
  //   for (size_t i = 0; i < sz ; i++) {
  //     for (size_t j = 0; j < sz; j++) {
  //       temp.pMem[i][j] = T();
  //       for (size_t k = 0; k < sz; k++) {
  //               temp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
  //           }
  //     }
  //   }
  //   return temp;
  // }

  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz) throw invalid_argument("Matrices must be the same size");
    TDynamicMatrix temp(sz); 
    
    int n = static_cast<int>(sz);
    //int b = 64; // Размер блока

    int b = static_cast<int>(std::sqrt(16384 / sizeof(T)));
    if (b == 0) b = 8;

    #pragma omp parallel for
    for (int i = 0; i < n; i += b) {
      for (int j = 0; j < n; j += b) {
        for (int k = 0; k < n; k += b) {
          
          // Вычисляем границы внутренних блоков, чтобы не выйти за пределы матрицы
          int i_max = std::min(i + b, n);
          int j_max = std::min(j + b, n);
          int k_max = std::min(k + b, n);

          for (int ii = i; ii < i_max; ++ii) {
            for (int jj = j; jj < j_max; ++jj) {
              T sum = T();
              
              for (int kk = k; kk < k_max; ++kk) {
                sum += pMem[ii][kk] * m.pMem[kk][jj];
              }
              temp.pMem[ii][jj] += sum;
            }
          }

        }
      }
    }
    return temp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz ; i++) {
      istr >> v.pMem[i];
    }
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz ; i++) {
      ostr << v.pMem[i] << endl;
    }
    return ostr;
  }
};

#include <vector>

template<typename T>
class SparseMatrix {
private:
    std::vector<T> data; // все числа матрицы != 0
    std::vector<size_t> cols; // столбцы каждого числа из дата
    std::vector<size_t> rows; // с какого эл-та начинается в дата новая строка
    size_t n_size;

public:
    SparseMatrix(const TDynamicMatrix<T>& plotMatrix) {
        n_size = plotMatrix.size();
        
        rows.push_back(0); 

        for (size_t i = 0; i < n_size; i++) {
            int non_zero_count = 0;
            for (size_t j = 0; j < n_size; j++) {
                if (plotMatrix[i][j] != T()) { 
                    data.push_back(plotMatrix[i][j]);
                    cols.push_back(j);
                    non_zero_count++;
                }
            }
            rows.push_back(rows.back() + non_zero_count);
        }
    }

    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (n_size != v.size()) {
            throw std::invalid_argument("Matrix and vector sizes are not same");
        }

        TDynamicVector<T> result(n_size);

        #pragma omp parallel for
        for (int i = 0; i < static_cast<int>(n_size); i++) {
            T sum = T();
            
            for (size_t j = rows[i]; j < rows[i+1]; j++) {
                sum += data[j] * v[cols[j]];
            }
            result[i] = sum;
        }
        return result;
    }
    
    const std::vector<T>& getData() const { return data; }
    const std::vector<size_t>& getCols() const { return cols; }
    const std::vector<size_t>& getRows() const { return rows; }
};

#endif
