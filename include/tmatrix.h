// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cassert>


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
      if (sz == 0 || sz > MAX_MATRIX_SIZE)
        throw std::out_of_range("Vector size should be greater than zero");
      pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }

    TDynamicVector(T* arr, size_t s) : sz(s)
    {
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[v.sz]){
      for (size_t i = 0; i < sz; i++){ pMem[i] = v.pMem[i];}
    }

    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
    {
      v.sz = 0;
      v.pMem = nullptr; // chtobi ne vizvalsya destructor vectora v
    }
    ~TDynamicVector()
    {
      delete [] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
      if (&v == this) {return *this;}

      if (sz != v.sz){

        delete [] pMem;
        pMem = new T[v.sz];
      }

      sz = v.sz;
      for (size_t i = 0; i < sz; i++) {pMem[i] = v.pMem[i];}

      return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
      if (&v == this ) { return *this;} // hotya  mojem peredat' v func prvalue obj,
                                        // on  privedetsya k xvalue obj, poetomu mojem vzyat' adress
      delete [] pMem;

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
      if (ind >= sz){ throw std::out_of_range("Ind doljen bit' < size");}
      return pMem[ind];
    }
    const T& at(size_t ind) const
    {
      if (ind >= sz){ throw std::out_of_range("Ind doljen bit' < size");}
      return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
      if (sz == v.sz){

        for (size_t i = 0; i < sz; i++){
          if (pMem[i] != v.pMem[i]){
            return false;
          }
        }
        return true;
      }

      return false;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
      return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(const T& val) const
    {
      TDynamicVector<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {tmp.pMem[i] = pMem[i] + val;} 

      return tmp;
    }
    TDynamicVector operator-(const T& val) const
    {
      TDynamicVector<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {tmp.pMem[i] = pMem[i] - val;} 

      return tmp;
    }
    TDynamicVector operator*(const T& val) const
    {
      TDynamicVector<T> tmp(sz);
      for (size_t i = 0; i < sz; i++) {tmp.pMem[i] = pMem[i] * val;} 

      return tmp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) const
    {
      if (sz != v.sz){
        throw std::out_of_range("Vectori doljni bit' odinakovoi dlini");
      }

      TDynamicVector<T> tmp(sz);

      for (size_t i = 0; i < sz; i++){ tmp[i] = pMem[i] + v.pMem[i];}

      return tmp;
    }
    TDynamicVector operator-(const TDynamicVector& v) const
    {
      if (sz != v.sz){
        throw std::out_of_range("Vectori doljni bit' odinakovoi dlini");
      }

      TDynamicVector<T> tmp(sz);

      for (size_t i = 0; i < sz; i++){ tmp[i] = pMem[i] - v.pMem[i];}

      return tmp;
    }
    T operator*(const TDynamicVector& v) const //noexcept(noexcept(T())) 
    {
      if (sz != v.sz){
        throw std::out_of_range("Vectori doljni bit' odinakovoi dlini");
      }

      T val {};
      
      for (size_t i = 0; i < sz; i++){ val += (pMem[i] * v.pMem[i]);}

      return val;
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
  
  TDynamicMatrix (size_t size = 1) : TDynamicVector<TDynamicVector<T>>(size){
    if (sz == 0 || sz > MAX_MATRIX_SIZE){
      throw std::out_of_range("Matrica doljna bit' < 10000");
    }
    for (size_t i = 0; i < sz; i++){
      pMem[i] = TDynamicVector<T>(sz);
    }
  }

  using TDynamicVector<TDynamicVector<T>>::at;        // zachem pisat' noviy, esli uje vseo est'!
  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  // сравнение
  
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    //polzuemsya tem, chto v vectore eto vseo realizovano
    return static_cast<const TDynamicVector<TDynamicVector<T>>&>(*this) == static_cast<const TDynamicVector<TDynamicVector<T>>&>(m) ;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) const
  {
    TDynamicMatrix<T> tmp(sz);

    for (size_t i = 0; i < sz; i++) {tmp[i] = pMem[i] * val;}
    return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
    if (sz != v.sz){
      throw std::out_of_range("doljni bit' ravni razmeri");
    }

    TDynamicVector<T> tmp(sz);

    for (size_t i = 0; i < sz; i++){
      tmp[i] = pMem[i] * v;
    }
    return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) const
  {
    if (sz != m.sz){
      throw std::out_of_range("Matrici doljni bit' odinakovoi razmernosti");
    }

    TDynamicMatrix<T> tmp(sz);

    for (size_t i = 0; i < sz; i++){
      tmp[i] = pMem[i] + m[i];
    }

    return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m) const
  {
    if (sz != m.sz){
      throw std::out_of_range("Matrici doljni bit' odinakovoi razmernosti");
    }

    TDynamicMatrix<T> tmp(sz);

    for (size_t i = 0; i < sz; i++){
      tmp[i] = pMem[i] - m[i];
    }

    return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m) const
  {
    if (sz != m.sz){
      throw std::out_of_range("Matrici doljni bit' odinakovoi razmernosti");
    }

    TDynamicMatrix<T> tmp(sz);

    for (size_t i = 0; i < sz; i++){
      for (size_t k = 0; k < sz; k++){ // resultat takoi je, zato vsegda na odnoi stroke nahodimsya,
        for (size_t j = 0; j < sz; j++){   // po pamyaty ne prigaem, a gladko idem!!
          tmp[i][j] += pMem[i][k] * m[k][j];
        }
      }
    }
    return tmp;
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++){
      istr >> v[i];
    }
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++){
      ostr << v[i] << '\n';
    }

    return ostr;
  }
};

#endif
