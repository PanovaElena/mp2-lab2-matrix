// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <utility>   
#include <cstddef>  

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;

    static void CheckSize(size_t size)
    {
        if (size == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (size > static_cast<size_t>(MAX_VECTOR_SIZE))
            throw out_of_range("Vector size is too large");
    }

public:
    TDynamicVector(size_t size = 1) : sz(size), pMem(nullptr)
    {
        CheckSize(sz);
        pMem = new T[sz](); 
    }

    TDynamicVector(T* arr, size_t s) : sz(s), pMem(nullptr)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        CheckSize(sz);
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(nullptr)
    {
        CheckSize(sz);
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
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
        if (this == &v) return *this;
        TDynamicVector tmp(v);
        swap(*this, tmp);
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this == &v) return *this;

        delete[] pMem;
        pMem = v.pMem;
        sz = v.sz;

        v.pMem = nullptr;
        v.sz = 0;

        return *this;
    }

    size_t size() const noexcept { return sz; }

    T& operator[](size_t ind)
    {
        assert(ind < sz && "TDynamicVector::operator[] index out of range");
        return pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        assert(ind < sz && "TDynamicVector::operator[] index out of range");
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
            throw out_of_range("TDynamicVector::at index out of range");
        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("TDynamicVector::at index out of range");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; ++i)
            if (!(pMem[i] == v.pMem[i])) return false;
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
        for (size_t i = 0; i < sz; ++i)
            res.pMem[i] = pMem[i] + val;
        return res;
    }

    TDynamicVector operator-(double val)
    {
        TDynamicVector res(sz);
        const T tval = static_cast<T>(val);
        for (size_t i = 0; i < sz; ++i)
            res.pMem[i] = pMem[i] - tval;
        return res;
    }

    TDynamicVector operator*(double val)
    {
        TDynamicVector res(sz);
        const T tval = static_cast<T>(val);
        for (size_t i = 0; i < sz; ++i)
            res.pMem[i] = pMem[i] * tval;
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("TDynamicVector: different sizes in operator+");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; ++i)
            res.pMem[i] = pMem[i] + v.pMem[i];
        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("TDynamicVector: different sizes in operator-");
        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; ++i)
            res.pMem[i] = pMem[i] - v.pMem[i];
        return res;
    }

    // скалярное произведение
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz) {
            assert(false && "TDynamicVector::operator* (dot): different sizes");
            return T{};
        }

        T sum{}; 
        for (size_t i = 0; i < sz; ++i)
            sum = sum + (pMem[i] * v.pMem[i]);
        return sum;
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

    static void CheckMatrixSize(size_t s)
    {
        if (s == 0)
            throw out_of_range("Matrix size should be greater than zero");
        if (s > static_cast<size_t>(MAX_MATRIX_SIZE))
            throw out_of_range("Matrix size is too large");
    }

public:
    using TDynamicVector<TDynamicVector<T>>::size;
    using TDynamicVector<TDynamicVector<T>>::at;
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        CheckMatrixSize(s);
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; ++i)
            if (!(pMem[i] == m.pMem[i])) return false;
        return true;
    }

    // матрично-скалярные операции
    TDynamicVector<T> operator*(const T& val)
    {
        const size_t n = sz;
        if (n > 0 && n > static_cast<size_t>(MAX_VECTOR_SIZE) / n)
            throw out_of_range("TDynamicMatrix: result vector is too large");

        TDynamicVector<T> res(n * n);
        size_t k = 0;
        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < n; ++j, ++k)
                res[k] = pMem[i][j] * val;
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (v.size() != sz)
            throw invalid_argument("TDynamicMatrix: matrix/vector sizes mismatch");

        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; ++i) {
            T sum{};
            for (size_t j = 0; j < sz; ++j)
                sum = sum + (pMem[i][j] * v[j]);
            res[i] = sum;
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("TDynamicMatrix: different sizes in operator+");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
                res[i][j] = pMem[i][j] + m.pMem[i][j];
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("TDynamicMatrix: different sizes in operator-");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
                res[i][j] = pMem[i][j] - m.pMem[i][j];
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("TDynamicMatrix: different sizes in operator*");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; ++i) {
            for (size_t j = 0; j < sz; ++j) {
                T sum{};
                for (size_t k = 0; k < sz; ++k)
                    sum = sum + (pMem[i][k] * m.pMem[k][j]);
                res[i][j] = sum;
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i)
            for (size_t j = 0; j < v.sz; ++j)
                istr >> v.pMem[i][j];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i) {
            for (size_t j = 0; j < v.sz; ++j)
                ostr << v.pMem[i][j] << ' ';
            ostr << '\n';
        }
        return ostr;
    }
};

#endif
