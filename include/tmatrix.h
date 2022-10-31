// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//
#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__
#include <iostream>
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
        if (sz <= 0)
        {
            throw out_of_range("Vector size should be greater than zero");
        }
        if (sz > MAX_VECTOR_SIZE)
        {
            throw out_of_range("Vector size should be less than max size");
        }
        pMem = new T[sz]();// У типа Т должен быть коснтруктор по умолчанию
        for (int i = 0; i < sz; i++)
        {
            pMem[i] = T();
        }
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        if (sz <= 0)
        {
            throw out_of_range("Vector size should be greater than zero");
        }
        if (sz > MAX_VECTOR_SIZE)
        {
            throw out_of_range("Vector size should be less than max size");
        }

        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz]();
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v)
    {
        pMem = new T[v.sz]();
        sz = v.sz;
        for (int i = 0; i < sz; i++)
        {
            pMem[i] = v.pMem[i];
        }
    }

    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }

    ~TDynamicVector()
    {
        delete[]pMem;
        pMem = nullptr;
        sz = 0;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (&v == this)
        {
            return *this;
        }

        if (sz != v.sz)
        {
            T* tmp = new T[v.sz]();
            delete[]pMem;
            sz = v.sz;
            pMem = tmp;
        }

        for (int i = 0; i < sz; i++)
        {
            pMem[i] = v.pMem[i];
        }

        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if ((&v == this) && (sz == v.sz))
        {
            return *this;
        }

        delete[]pMem;
        sz = v.sz;
        pMem = v.pMem;
        v.pMem = nullptr;
        v.sz = 0;

        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind < 0 || ind >= sz)
        {
            throw out_of_range("index out of range");
        }
        return pMem[ind];
    }

    const T& operator[](size_t ind) const
    {
        if (ind < 0 || ind >= sz)
        {
            throw out_of_range("index out of range");
        }
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < 0 || ind >= sz)
        {
            throw out_of_range("index out of range");
        }
        return pMem[ind];
    }

    const T& at(size_t ind) const
    {
        if (ind < 0 || ind >= sz)
        {
            throw out_of_range("index out of range");
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
        for (int i = 0; i < sz; i++)
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
        if (sz != v.sz)
        {
            return true;
        }
        for (int i = 0; i < sz; i++)
        {
            if (pMem[i] != v.pMem[i])
            {
                return true;
            }
        }
        return false;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++)
        {
            tmp[i] += val;
        }
        return tmp;
    }

    TDynamicVector operator-(double val)
    {
        TDynamicVector tmp(*this);
        for (int i = 0; i < tmp.sz; i++)
        {
            tmp.pMem[i] -= val;
        }
        return tmp;
    }

    TDynamicVector operator*(double val)
    {
        TDynamicVector tmp(*this);
        for (int i = 0; i < tmp.sz; i++)
        {
            tmp.pMem[i] *= val;
        }
        return tmp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw "Can't do addition, Sizes should be equal";
        }
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++)
        {
            tmp.pMem[i] += v.pMem[i];
        }
        return tmp;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw "Can't do '-', Sizes should be equal";
        }
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++)
        {
            tmp.pMem[i] -= v.pMem[i];
        }
        return tmp;
    }

    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw "Can't do '*', Sizes should be equal";
        }
        T tmp = 0;
        for (int i = 0; i < sz; i++)
        {
            tmp += pMem[i] * v.pMem[i];
        }
        return tmp;
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
        if (s <= 0)
        {
            throw out_of_range("Vector size should be greater than zero");
        }
        if (sz > MAX_MATRIX_SIZE)
        {
            throw out_of_range("Vector size should be less than max size");
        }
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz)
        {
            return false;
        }
        for (int i = 0; i < sz; ++i)
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
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix tmp(*this);
        for (int i = 0; i < sz; i++)
        {
            tmp[i] = tmp[i] * val;
        }
        return tmp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.sz)
        {
            throw "Can't do matrix-vector '*', Sizes should be match";
        }
        TDynamicVector<T> tmp(v.sz);
        for (int i = 0; i < sz; i++)
        {
            tmp[i] = 0;
            for (int j = 0; j < sz; j++)
            {
                tmp[i] += pMem[i][j] * v[j];
            }
        }

        return tmp;
    }

    size_t size() const noexcept { return sz; }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw "Can't do matrix '+', Sizes should be equal";
        }
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] + m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw "Can't do matrix '-', Sizes should be equal";
        }
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
        {
            tmp.pMem[i] = pMem[i] - m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
        {
            throw "Can't do matrix '*', Sizes should be match";
        }
        TDynamicMatrix<T> tmp(m.sz);
        for (int i = 0; i < sz; ++i) {
            for (int k = 0; k < sz; ++k) {
                for (int j = 0; j < sz; ++j) {
                    tmp.pMem[i][j] += pMem[i][k] * pMem[k][j];
                }
            }
        }

        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
        {
            cin >> v.pMem[i];
        }

        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
        {
            cout << v.pMem[i] << "\n";
        }

        return ostr;
    }
};
#endif