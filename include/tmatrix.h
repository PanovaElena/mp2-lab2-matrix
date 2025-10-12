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
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Error!");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (arr == nullptr || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Error!");
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++)
            pMem[i] = arr[i];
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[v.sz])
    {
        for (size_t i = 0; i < sz; i++)
            pMem[i] = v.pMem[i];
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
        if (this == &v) return *this;

        if (sz != v.sz) {
            delete[] pMem;
            sz = v.sz;
            pMem = new T[sz];
        }

        for (size_t i = 0; i < sz; i++)
            pMem[i] = v.pMem[i];

        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v) {
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
        if (ind >= sz)
            throw out_of_range("Error!");
        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Error!");
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
        if (sz != v.sz)
            throw invalid_argument("Error!");

        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] + v.pMem[i];
        return res;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Error!");

        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
            res.pMem[i] = pMem[i] - v.pMem[i];
        return res;
    }

    T operator*(const TDynamicVector& v) 
    {
        if (sz != v.sz)
            throw invalid_argument("Error!");

        T sum = T();
        for (size_t i = 0; i < sz; i++)
            sum += pMem[i] * v.pMem[i];
        return sum;
    }

    friend void swap(TDynamicVector& a, TDynamicVector& b) noexcept
    {
        size_t temp_sz = a.sz;
        a.sz = b.sz;
        b.sz = temp_sz;

        T* temp_pMem = a.pMem;
        a.pMem = b.pMem;
        b.pMem = temp_pMem;
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
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("Error!");
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    size_t size() const noexcept { return sz; }

    // индексация с контролем для матрицы
    TDynamicVector<T>& at(size_t ind)
    {
        if (ind >= sz) throw out_of_range("Error!");
        return pMem[ind];
    }

    const TDynamicVector<T>& at(size_t ind) const
    {
        if (ind >= sz)
            throw out_of_range("Error!");
        return pMem[ind];
    }

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

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) throw invalid_argument("Error!");

        TDynamicVector<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            T sum = T();
            for (size_t j = 0; j < sz; j++)
                sum += pMem[i][j] * v[j];
            res[i] = sum;
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Error!");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] + m[i];
        return res;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Error!");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++)
            res[i] = pMem[i] - m[i];
        return res;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw invalid_argument("Error!");

        TDynamicMatrix res(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                T sum = T();
                for (size_t k = 0; k < sz; k++)
                    sum += pMem[i][k] * m[k][j];
                res[i][j] = sum;
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++)
            istr >> m.pMem[i];
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++) {
            for (size_t j = 0; j < m.sz; j++)
                ostr << m.pMem[i][j] << ' ';
        }
        return ostr;
    }
};

#endif