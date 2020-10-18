// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
    ValType* pVector;
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
public:
    TVector(int s = 10, int si = 0);          // одновременно конструктор по умолчанию
                                              // и конструктор с параметрами
    TVector(const TVector& v);                // конструктор копирования
    ~TVector();
    int GetSize() const { return Size; } // размер вектора
    int GetStartIndex() const { return StartIndex; } // индекс первого элемента
    ValType& operator[](int pos) const;             // доступ
    bool operator==(const TVector& v) const;  // сравнение
    bool operator!=(const TVector& v) const;  // сравнение
    TVector& operator=(const TVector& v);     // присваивание

    // скалярные операции
    TVector  operator+(const ValType& val) const;   // прибавить скаляр
    TVector  operator-(const ValType& val) const;   // вычесть скаляр
    TVector  operator*(const ValType& val) const;   // умножить на скаляр

    // векторные операции
    TVector  operator+(const TVector& v) const;     // сложение
    TVector  operator-(const TVector& v) const;     // вычитание
    ValType  operator*(const TVector& v) const;     // скалярное произведение

    // ввод-вывод
    friend istream& operator>>(istream& in, TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector& v)
    {
        for (int i = 0; i < v.Size; i++)
            out << v.pVector[i] << ' ';
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if ((s >= 0) && (si >= 0) && (s <= MAX_VECTOR_SIZE))
    {
        this->pVector = new ValType[s];
        this->Size = s;
        this->StartIndex = si;
    }
    else throw "Incorrect parameters of vector!";
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v)
{
    this->Size = v.Size;
    this->StartIndex = v.StartIndex;
    this->pVector = new ValType[Size];
    for (int i = 0; i < Size; i++)
    {
        this->pVector[i] = v.pVector[i];
    }
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    if (pVector != NULL)
    {
        delete[] pVector;
        this->pVector = NULL;
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos) const
{
    if ((pos >= 0) && (pos >= this->StartIndex) && (pos < this->Size))
        return this->pVector[pos];
    else throw "Incorrect index of vector!";
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
    if ((this->Size != v.Size) || (this->StartIndex != v.StartIndex))
        return false;
    for (int i = 0; i < Size; i++)
        if (this->pVector[i] != v.pVector[i])
            return false;
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
    if (*this == v)
        return false;
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
    if (*this != v)
    {
        if (this->pVector != NULL)
            delete[] this->pVector;
        this->Size = v.Size;
        this->StartIndex = v.StartIndex;
        this->pVector = new ValType[Size];
        for (int i = 0; i < this->Size; i++)
            this->pVector[i] = v.pVector[i];
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val) const
{
    TVector<ValType> result(*this);
    for (int i = 0; i < this->Size; i++)
        result.pVector[i] += val;
    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val) const
{
    TVector<ValType> result(*this);
    for (int i = 0; i < this->Size; i++)
        result.pVector[i] -= val;
    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val) const
{
    TVector<ValType> result(*this);
    for (int i = 0; i < this->Size; i++)
        result.pVector[i] *= val;
    return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v) const
{
    if (this->Size == v.Size)
    {
        TVector<ValType> result(this->Size);
        for (int i = 0; i < this->Size; i++)
            result.pVector[i] = this->pVector[i] + v.pVector[i];
        return result;
    }
    else throw "incorrect addition of vectors!";
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v) const
{
    if (this->Size == v.Size)
    {
        TVector<ValType> result(this->Size);
        for (int i = 0; i < this->Size; i++)
            result.pVector[i] = this->pVector[i] - v.pVector[i];
        return result;
    }
    else throw "incorrect subtraction of vectors!";
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v) const
{
    if (this->Size == v.Size)
    {
        ValType result = 0;
        for (int i = 0; i < this->Size; i++)
            result += this->pVector[i] * v.pVector[i];
        return result;
    }
    else throw "incorrect scalar product of vectors!";
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // копирование
    TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
    bool operator==(const TMatrix& mt) const;      // сравнение
    bool operator!=(const TMatrix& mt) const;      // сравнение
    TMatrix& operator= (const TMatrix& mt);        // присваивание
    TMatrix  operator+ (const TMatrix& mt) const;        // сложение
    TMatrix  operator- (const TMatrix& mt) const;        // вычитание

    // ввод / вывод
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
    // по умолчанию создается квадратная матрица sхs
    // надо заменить созданную матрицу верхнетреугольной
    // вектора должны быть разной длины в матрице
    if ((s >= 0) && (s < MAX_MATRIX_SIZE))
        for (int i = 0; i < s; i++)
        {
            TVector<ValType> row(s - i, i);
            this->pVector[i] = row;
        }
    else throw "Incorrect size of matrix!";
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
    TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
    TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
    return TVector<TVector<ValType> >::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
    return TVector<TVector<ValType> >::operator!=(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
    TVector<TVector<ValType> >::operator=(mt);
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt) const
{
    // благодаря наследованию от TVector<TVector<ValType> > operator+
    // уже есть, надо только его вызвать
    return TVector<TVector<ValType> >::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt) const
{
    return TVector<TVector<ValType> >::operator-(mt);
} /*--------------------------------------------------s-----------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif