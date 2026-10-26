// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <algorithm>

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
            throw std::out_of_range("Vector size should be greater than zero and less than MAX_VECTOR_SIZE");
        pMem = new T[sz]();
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw std::out_of_range("Vector size should be greater than zero and less than MAX_VECTOR_SIZE");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;
        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        if (pMem != nullptr)
        {
            delete[] pMem;
            pMem = nullptr;
        }
        sz = 0;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this != &v)
        {
            if (sz != v.sz)
            {
                if (pMem != nullptr)
                {
                    delete[] pMem;
                }
                sz = v.sz;
                pMem = new T[sz];
            }
            for (size_t i = 0; i < sz; i++)
            {
                pMem[i] = v.pMem[i];
            }
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v)
        {
            if (pMem != nullptr)
            {
                delete[] pMem;
            }
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
        if (ind >= sz)
        {
            throw std::out_of_range("Index out of range");
        }
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Index out of range");
        }
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Index out of range");
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Index out of range");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
        {
            return false;
        }
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != v.pMem[i])
            {
                return false;
            }
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
        for (size_t i = 0; i < sz; i++)
        {
            temp.pMem[i] = pMem[i] + val;
        }
        return temp;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            temp.pMem[i] = pMem[i] - val;
        }
        return temp;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            temp.pMem[i] = pMem[i] * val;
        }
        return temp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw std::invalid_argument("Vectors must be of equal size");
        }
        TDynamicVector temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            temp.pMem[i] = pMem[i] + v.pMem[i];
        }
        return temp;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw std::invalid_argument("Vectors must be of equal size");
        }
        TDynamicVector temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            temp.pMem[i] = pMem[i] - v.pMem[i];
        }
        return temp;
    }
    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw std::invalid_argument("Vectors must be of equal size");
        }
        T res = T();
        for (size_t i = 0; i < sz; i++)
        {
            res += pMem[i] * v.pMem[i];
        }
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
            istr >> v.pMem[i];
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' ';
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix
{
protected:
    size_t sz;
    TDynamicVector<T>* pMem;
public:
    TDynamicMatrix(size_t s = 1) : sz(s)
    {
        if (sz == 0 || sz > MAX_MATRIX_SIZE)
            throw std::out_of_range("Matrix size out of bounds");
        pMem = new TDynamicVector<T>[sz];
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }
    TDynamicMatrix(const TDynamicMatrix& m)
    {
        sz = m.sz;
        pMem = new TDynamicVector<T>[sz];
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = m.pMem[i];
        }
    }
    TDynamicMatrix(TDynamicMatrix&& m) noexcept
    {
        sz = m.sz;
        pMem = m.pMem;
        m.sz = 0;
        m.pMem = nullptr;
    }
    ~TDynamicMatrix()
    {
        if (pMem != nullptr)
        {
            delete[] pMem;
            pMem = nullptr;
        }
        sz = 0;
    }
    TDynamicMatrix& operator=(const TDynamicMatrix& m)
    {
        if (this != &m)
        {
            if (sz != m.sz)
            {
                if (pMem != nullptr)
                {
                    delete[] pMem;
                }
                sz = m.sz;
                pMem = new TDynamicVector<T>[sz];
            }
            for (size_t i = 0; i < sz; i++)
            {
                pMem[i] = m.pMem[i];
            }
        }
        return *this;
    }
    TDynamicMatrix& operator=(TDynamicMatrix&& m) noexcept
    {
        if (this != &m)
        {
            if (pMem != nullptr)
            {
                delete[] pMem;
            }
            sz = m.sz;
            pMem = m.pMem;
            m.sz = 0;
            m.pMem = nullptr;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }

    TDynamicVector<T>& operator[](size_t ind)
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Matrix row index out of range");
        }
        return pMem[ind];
    }
    const TDynamicVector<T>& operator[](size_t ind) const
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Matrix row index out of range");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz)
        {
            return false;
        }
        for (size_t i = 0; i < sz; i++)
        {
            if (pMem[i] != m.pMem[i])
            {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val)
    {
        TDynamicMatrix<T> temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            temp.pMem[i] = pMem[i] * val;
        }
        return temp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
        {
            throw std::invalid_argument("Matrix and vector sizes must be equal");
        }
        TDynamicVector<T> temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            T sum = T();
            for (size_t j = 0; j < sz; j++)
            {
                sum += pMem[i][j] * v[j];
            }
            temp[i] = sum;
        }
        return temp;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw std::invalid_argument("Matrix sizes must be equal");
        }
        TDynamicMatrix temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            temp.pMem[i] = pMem[i] + m.pMem[i];
        }
        return temp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw std::invalid_argument("Matrix sizes must be equal");
        }
        TDynamicMatrix temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            temp.pMem[i] = pMem[i] - m.pMem[i];
        }
        return temp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw std::invalid_argument("Matrix sizes must be equal");
        }
        TDynamicMatrix temp(sz);
        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                T sum = T();
                for (size_t k = 0; k < sz; k++)
                {
                    sum += pMem[i][k] * m.pMem[k][j];
                }
                temp.pMem[i][j] = sum;
            }
        }
        return temp;
    }
    // ввод/вывод
    friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        {
            istr >> v.pMem[i];
        }
        return istr;
    }
    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++)
        {
            ostr << v.pMem[i] << "\n";
        }
        return ostr;
    }
};
#endif