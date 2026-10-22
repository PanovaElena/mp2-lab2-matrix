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
#include <algorithm>
#include <vector>

#ifdef _OPENMP // Если в компиляторе включена поддержка OpenMP, подключаем библиотеку для многопоточности
#include <omp.h>
#endif


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
      throw out_of_range("Vector size is greater than MAX_VECTOR_SIZE = 100000000 or negative");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
    // уже инициализируется по умолчанию нулями из-за (). инициализация пустым значением
  }
  TDynamicVector(T* arr, size_t s) : sz(s) //создается TDynamicVector из массива С
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg"); // Макрос для поиска багов: если arr равен nullptr, программа упадет и выведет этот текст в консоль
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
      throw out_of_range("Vector size is greater than MAX_VECTOR_SIZE = 100000000 or negative");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    sz = v.sz;
    pMem = new T[sz];
    std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept // noexcept - чтобы во время перемещения при ошибке не было такого, что старая память уже удалилась, а новая не смогла переместиться из-за исключения
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
  T operator*(const TDynamicVector& v)  // noexcept(noexcept(T()))
  // operator* является noexcept тогда и только тогда, когда конструктор по умолчанию типа T сам является noexcept. т.е внутренний noexcept это проверка на noexecept'ность конструктора Т
  {
    if (sz != v.sz) {
      throw out_of_range("Vector size mismatch");
    }
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

  using TDynamicVector<TDynamicVector<T>>::at; // используется для тестов

  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_MATRIX_SIZE)
      throw out_of_range("Vector size is greater than MAX_MATRIX_SIZE = 10000 or negative");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept{
    if (sz != m.sz) {
      return false;
    }
    for (size_t i = 0; i < sz; i++) {
      if (pMem[i] != m.pMem[i]) {
        return false;
      }
    }
    return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) // изменен на TDynamicMatrix
  {
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++) {
      res[i] = pMem[i] * val;
    }
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (sz != v.size()) {
    throw out_of_range("Vector size mismatch");
  }
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++) {
      res[i] = pMem[i] * v;
    }
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.sz) {
      throw out_of_range("Vector size mismatch");
    }
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++) {
      res[i] = pMem[i] + m.pMem[i];
    }
    return res;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.sz) {
      throw out_of_range("Vector size mismatch");
    }
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++) {
      res[i] = pMem[i] - m.pMem[i];
    }
    return res;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (sz != m.sz) {
      throw out_of_range("Vector size mismatch");
    }
    TDynamicMatrix res(sz);
#pragma omp parallel for schedule(dynamic) // делим строки между потоками
    for (size_t i = 0; i < sz; i++) {
      for (size_t k = 0; k < sz; k++) {
#pragma omp simd //Внутри потока включаем векторизацию, перед циклом т.к. обрабатываем сразу несколько итераций в одной процессорной инструкции
        for (size_t j = 0; j < sz; j++) {
          res[i][j] += pMem[i][k] * m[k][j];
        }
      }
    }
    return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++) {
      istr >> v.pMem[i];
    }
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++) {
      ostr << v.pMem[i] << '\n';
    }
    return ostr;
  }

  TDynamicMatrix blockMultiply (const TDynamicMatrix& m) const {
    if (sz != m.sz) {
      throw out_of_range("Matrix size mismatch");
    }
    TDynamicMatrix res(sz);
    size_t blocksize = 64;
#pragma omp parallel for schedule(dynamic) // делим блоки между потоками
    for (size_t ii = 0; ii < sz; ii += blocksize) {
      size_t iEnd = min(sz, ii + blocksize);
      for (size_t kk = 0; kk < sz; kk += blocksize) {
        size_t kEnd = min(kk + blocksize, sz);
        for (size_t jj = 0; jj < sz; jj += blocksize) {
          size_t jEnd = min(sz, jj + blocksize);

          for (size_t i = ii; i < iEnd; i++) {
            for (size_t k = kk; k < kEnd; k++) {
#pragma omp simd
              for (size_t j = jj; j < jEnd; j++) {
                res[i][j] += pMem[i][k] * m[k][j];
              }
            }
          }
        }
      }
    }
    return res;
  }

  size_t size() const noexcept {
    return sz;
  }

  TDynamicMatrix slowMultiply(const TDynamicMatrix& m) const
  {
    if (sz != m.sz) {
      throw out_of_range("Vector size mismatch");
    }
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++) {
      for (size_t j = 0; j < sz; j++) {
        T sum = T();
        for (size_t k = 0; k < sz; k++) {
          sum += pMem[i][k] * m[k][j];
        }
        res[i][j] = sum;
      }
    }
    return res;
  }
};


// класс разряженных матриц crs
template <typename T>
class SparseMatrix {
  vector<T>   data;
  vector<int> rows;   // n + 1 чисел: с какого места в data начинается каждая строка
  vector<int> cols;
  size_t n;           // строки
  size_t m;           // столбцы

public:
  //default
  SparseMatrix(size_t rowsCount = 1, size_t colsCount = 1) : rows(rowsCount + 1, 0), n(rowsCount), m(colsCount)
  {
    if (n == 0 || m == 0)
      throw out_of_range("Matrix size should be greater than zero");
    if (n > MAX_MATRIX_SIZE || m > MAX_MATRIX_SIZE)
      throw out_of_range("Matrix size is greater than MAX_MATRIX_SIZE = 10000");
  }

  //приведения типов
  SparseMatrix(const TDynamicMatrix<T>& a) : rows(1, 0), n(a.size()), m(a.size())
  {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < m; j++) {
        if (a[i][j] != T()) {
          data.push_back(a[i][j]);
          cols.push_back(j);
        }
      }
      rows.push_back(data.size()); // конец строки i = начало строки i + 1
    }
  }

  // конструктор копирования, оператор присваивания и деструктор не нужны, все поля - std::vector и size_t, поэтому копирование, освобождение памяти выполняются методами std::vector

  size_t getRows() const noexcept { return n; }
  size_t getCols() const noexcept { return m; }
  size_t nonZeroCount() const noexcept { return data.size(); } //число не нулевых эл-тов в матрице

  bool operator==(const SparseMatrix& a) const noexcept
  {
    return n == a.n && m == a.m && rows == a.rows && cols == a.cols && data == a.data; // идёт слева направо, если где-то встречается несоответствие возвращается false
  }
  bool operator!=(const SparseMatrix& a) const noexcept
  {
    return !(*this == a);
  }

  T at(size_t i, size_t j) const
  {
    if (i >= n || j >= m) {
      throw out_of_range("Matrix index out of bounds");
    }
    for (int k = rows[i]; k < rows[i + 1]; k++) {
      if (cols[k] == static_cast<int>(j)) {
        return data[k];
      }
    }
    return T(); // не нашли, значит там ноль
  }

  void set(size_t i, size_t j, const T& val)
  {
    if (i >= n || j >= m) {
      throw out_of_range("Matrix index out of bounds");
    }

    int k = rows[i];
    while (k < rows[i + 1] && cols[k] < static_cast<int>(j)) {
      k++; // ищем место, где должен стоять столбец j
    }
    bool found = (k < rows[i + 1] && cols[k] == static_cast<int>(j));

    if (found && val != T()) {
      data[k] = val;                                   // просто меняем
    }
    else if (found) {
      data.erase(data.begin() + k);                    // записали ноль - удаляем
      cols.erase(cols.begin() + k);
      for (size_t r = i + 1; r <= n; r++) rows[r]--;
    }
    else if (val != T()) {
      data.insert(data.begin() + k, val);              // был ноль - вставляем
      cols.insert(cols.begin() + k, static_cast<int>(j));
      for (size_t r = i + 1; r <= n; r++) rows[r]++;
    }
  }

  SparseMatrix operator*(const T& val) const
  {
    if (val == T()) {
      return SparseMatrix(n, m); // умножили на ноль: матрица пустая
    }
    SparseMatrix res(*this);
    for (size_t k = 0; k < res.data.size(); k++) {
      res.data[k] = res.data[k] * val;
    }
    return res;
  }

  SparseMatrix operator+(const SparseMatrix& b) const {
    if (n != b.n || m != b.m) {
      throw out_of_range("Matrix size mismatch");
    }
    SparseMatrix res(n, m);
    for (size_t i = 0; i < n; i++) {
      vector<T> row(m); // строка из нулей

      for (int k = rows[i]; k < rows[i + 1]; k++) {
        row[cols[k]] += data[k];
      }
      for (int k = b.rows[i]; k < b.rows[i + 1]; k++) {
        row[b.cols[k]] += b.data[k];
      }

      for (size_t j = 0; j < m; j++) { // оставляем только ненулевые
        if (row[j] != T()) {
          res.data.push_back(row[j]);
          res.cols.push_back(static_cast<int>(j));
        }
      }
      res.rows[i + 1] = res.data.size();
    }
    return res;
  }

  SparseMatrix operator-(const SparseMatrix& b) const {
    if (n != b.n || m != b.m) {
    throw out_of_range("Matrix size mismatch");
  }
    SparseMatrix res(n, m);
    for (size_t i = 0; i < n; i++) {
      vector<T> row(m); // строка из нулей

      for (int k = rows[i]; k < rows[i + 1]; k++) {
        row[cols[k]] += data[k];
      }
      for (int k = b.rows[i]; k < b.rows[i + 1]; k++) {
        row[b.cols[k]] -= b.data[k];
      }

      for (size_t j = 0; j < m; j++) { // оставляем только ненулевые
        if (row[j] != T()) {
          res.data.push_back(row[j]);
          res.cols.push_back(static_cast<int>(j));
        }
      }
      res.rows[i + 1] = res.data.size();
    }
    return res;}

  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
    if (m != v.size()) {
      throw out_of_range("Vector size mismatch");
    }
    TDynamicVector<T> res(n);
    for (size_t i = 0; i < n; i++) {
      for (int k = rows[i]; k < rows[i + 1]; k++) {
        res[i] += data[k] * v[cols[k]];
      }
    }
    return res;
  }

  friend istream& operator>>(istream& istr, SparseMatrix& a)
  {
    a.data.clear();
    a.cols.clear();
    a.rows.assign(1, 0);
    for (size_t i = 0; i < a.n; i++) {
      for (size_t j = 0; j < a.m; j++) {
        T x;
        istr >> x; // требуется оператор>> для типа T
        if (x != T()) {
          a.data.push_back(x);
          a.cols.push_back(static_cast<int>(j));
        }
      }
      a.rows.push_back(a.data.size());
    }
    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const SparseMatrix& a)
  {
    for (size_t i = 0; i < a.n; i++) {
      int k = a.rows[i];
      for (size_t j = 0; j < a.m; j++) {
        if (k < a.rows[i + 1] && a.cols[k] == static_cast<int>(j)) {
          ostr << a.data[k] << ' ';
          k++;
        }
        else {
          ostr << T() << ' ';
        }
      }
      ostr << '\n';
    }
    return ostr;
  }

};

#endif
