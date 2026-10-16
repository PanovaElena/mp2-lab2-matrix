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
      throw std::length_error("Vector size is too large");
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
    if (ind >= sz) throw std::out_of_range("Index out of range");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz) throw std::out_of_range("Index out of range");
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
    if (sz != v.sz) throw std::invalid_argument("Vectors must be the same size");
    TDynamicVector temp(sz);
    for (size_t i =0; i < sz; i++) temp.pMem[i] = pMem[i] + v.pMem[i];
    return temp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz) throw std::invalid_argument("Vectors must be the same size");
    TDynamicVector temp(sz);
    for (size_t i =0; i < sz; i++) temp.pMem[i] = pMem[i] - v.pMem[i];
    return temp;
  }
  T operator*(const TDynamicVector& v) 
  {
    if (sz != v.sz) throw std::invalid_argument("Vectors must be the same size");
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
    if (sz > MAX_MATRIX_SIZE)
      throw std::out_of_range("Matrix size is too large");
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
    if (sz != v.size()) throw std::invalid_argument("Matrix and vector sizes not same");
    TDynamicVector<T> temp(sz);
    for (size_t i = 0; i < sz ; i++) {
      temp[i] = pMem[i] * v;
    }
    return temp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.size()) throw std::invalid_argument("Matrices must be the same size");
    TDynamicMatrix<T> temp(sz);
    for (size_t i = 0; i < sz ; i++) {
      temp.pMem[i] = pMem[i] + m.pMem[i];
    }
    return temp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.size()) throw std::invalid_argument("Matrices must be the same size");
    TDynamicMatrix<T> temp(sz);
    for (size_t i = 0; i < sz ; i++) {
      temp.pMem[i] = pMem[i] - m.pMem[i];
    }
    return temp;
  }
  // TDynamicMatrix operator*(const TDynamicMatrix& m)
  // {
  //   if (sz != m.size()) throw std::invalid_argument("Matrices must be the same size");
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
    if (sz != m.sz) throw std::invalid_argument("Matrices must be the same size");
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
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz ; i++) {
      istr >> v.pMem[i];
    }
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz ; i++) {
      ostr << v.pMem[i] << std::endl;
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
    SparseMatrix(size_t size = 1) : n_size(size) {
        rows.assign(n_size + 1, 0); 
    }
    SparseMatrix(const TDynamicMatrix<T>& plotMatrix) {
        n_size = plotMatrix.size();
        
        rows.push_back(0); 

        for (size_t i = 0; i < n_size; i++) {
            int non_zero_count = 0;
            for (size_t j = 0; j < n_size; j++) {
                if (plotMatrix[i][j] != T()) { // Если элемент не 0, сохраняем значение, столбец, считаем нужные эл-ты
                    data.push_back(plotMatrix[i][j]);
                    cols.push_back(j);
                    non_zero_count++;
                }
            }
            rows.push_back(rows.back() + non_zero_count); // сколько эл-тов != 0
        }
    }

    size_t size() const noexcept { return n_size; }

    // чтение по индексу
    T at(size_t i, size_t j) const { 
        if (i >= n_size || j >= n_size) throw std::out_of_range("Index out of range");
        
        for (size_t k = rows[i]; k < rows[i+1]; k++) {
            if (cols[k] == j) {
                return data[k]; 
            }
        }
        return T(); 
    }

    bool operator==(const SparseMatrix& m) const noexcept {
        return n_size == m.n_size && data == m.data && cols == m.cols && rows == m.rows;
    }
    bool operator!=(const SparseMatrix& m) const noexcept {
        return !(*this == m);
    }

    SparseMatrix operator*(const T& val) const {
        SparseMatrix res(n_size);
        if (val == T()) return res; // умн на 0

        res.data = data;
        res.cols = cols;
        res.rows = rows;
        for (size_t i = 0; i < res.data.size(); i++) {
            res.data[i] = res.data[i] * val;
        }
        return res;
    }

    TDynamicVector<T> operator*(const TDynamicVector<T>& v) const {
        if (n_size != v.size()) {
            throw std::invalid_argument("Matrix and vector sizes are not same");
        }

        TDynamicVector<T> result(n_size);

        #pragma omp parallel for
        for (int i = 0; i < static_cast<int>(n_size); i++) {
            T sum = T();
            
            for (size_t j = rows[i]; j < rows[i+1]; j++) { // сокращаем время, идем от ровс[i] До ровс[i+1]
                sum += data[j] * v[cols[j]];
            }
            result[i] = sum;
        }
        return result;
    }

    SparseMatrix operator+(const SparseMatrix& m) const {
        if (n_size != m.n_size) throw std::invalid_argument("Sizes must match");
        SparseMatrix res(n_size);
        
        for (size_t i = 0; i < n_size; i++) {
            size_t ptr1 = rows[i], end1 = rows[i+1]; // начало и конец i строки
            size_t ptr2 = m.rows[i], end2 = m.rows[i+1];

            // Слияние двух отсортированных строк
            while (ptr1 < end1 && ptr2 < end2) {
                if (cols[ptr1] < m.cols[ptr2]) {
                    res.data.push_back(data[ptr1]);
                    res.cols.push_back(cols[ptr1]);
                    ptr1++;
                } else if (cols[ptr1] > m.cols[ptr2]) {
                    res.data.push_back(m.data[ptr2]);
                    res.cols.push_back(m.cols[ptr2]);
                    ptr2++;
                } else {
                    T sum = data[ptr1] + m.data[ptr2];
                    if (sum != T()) {
                        res.data.push_back(sum);
                        res.cols.push_back(cols[ptr1]);
                    }
                    ptr1++; ptr2++;
                }
            }
            // Если вторая строка закончилась раньше первой, дописываем остаток и наоборот
            while (ptr1 < end1) { res.data.push_back(data[ptr1]); res.cols.push_back(cols[ptr1++]); }
            while (ptr2 < end2) { res.data.push_back(m.data[ptr2]); res.cols.push_back(m.cols[ptr2++]); }
            
            res.rows[i+1] = res.data.size();
        }
        return res;
    }

    SparseMatrix operator-(const SparseMatrix& m) const {
        if (n_size != m.n_size) throw std::invalid_argument("Sizes must match");
        SparseMatrix res(n_size);
        
        for (size_t i = 0; i < n_size; i++) {
            size_t ptr1 = rows[i], end1 = rows[i+1];
            size_t ptr2 = m.rows[i], end2 = m.rows[i+1];

            while (ptr1 < end1 && ptr2 < end2) {
                if (cols[ptr1] < m.cols[ptr2]) {
                    res.data.push_back(data[ptr1]);
                    res.cols.push_back(cols[ptr1]);
                    ptr1++;
                } else if (cols[ptr1] > m.cols[ptr2]) {
                    res.data.push_back(-m.data[ptr2]); // отриц
                    res.cols.push_back(m.cols[ptr2]);
                    ptr2++;
                } else {
                    T diff = data[ptr1] - m.data[ptr2];
                    if (diff != T()) {
                        res.data.push_back(diff);
                        res.cols.push_back(cols[ptr1]);
                    }
                    ptr1++; ptr2++;
                }
            }
            while (ptr1 < end1) { res.data.push_back(data[ptr1]); res.cols.push_back(cols[ptr1++]); }
            while (ptr2 < end2) { res.data.push_back(-m.data[ptr2]); res.cols.push_back(m.cols[ptr2++]); }
            
            res.rows[i+1] = res.data.size();
        }
        return res;
    }

    SparseMatrix operator*(const SparseMatrix& m) const {
        if (n_size != m.n_size) throw std::invalid_argument("Sizes must match");
        SparseMatrix res(n_size);
        
        std::vector<T> temp_row(n_size, T());
        std::vector<size_t> marker(n_size, n_size);

        for (size_t i = 0; i < n_size; i++) {
            std::vector<size_t> non_zero_cols; // где не 0

            for (size_t j = rows[i]; j < rows[i+1]; j++) { // перебираем эл-ты != 0
                size_t col_A = cols[j]; // эл-т, стоящий в столбце col_A первой матрицы, должен умножаться на всю строку col_A второй матрицы
                T val_A = data[j];

                for (size_t k = m.rows[col_A]; k < m.rows[col_A+1]; k++) { // перебираем эл-ты 2-ой матрицы != 0
                    size_t col_B = m.cols[k];
                    T val_B = m.data[k];

                    if (marker[col_B] != (i)) { // берем впервые
                        marker[col_B] = (i);
                        temp_row[col_B] = val_A * val_B;
                        non_zero_cols.push_back(col_B);
                    } else {
                        temp_row[col_B] += val_A * val_B; // копим сумму
                    }
                }
            }

            std::sort(non_zero_cols.begin(), non_zero_cols.end());
            for (size_t col : non_zero_cols) {
                if (temp_row[col] != T()) {
                    res.data.push_back(temp_row[col]);
                    res.cols.push_back(col);
                }
                temp_row[col] = T(); // Очищаем для следующей строки
            }
            res.rows[i+1] = res.data.size();
        }
        return res;
    }
    
    const std::vector<T>& getData() const { return data; }
    const std::vector<size_t>& getCols() const { return cols; }
    const std::vector<size_t>& getRows() const { return rows; }
};

#endif
