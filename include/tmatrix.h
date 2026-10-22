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
#include <vector>

//чтобы скомпилировался на случай отсуствия omp
#ifdef _OPENMP
#include <omp.h> 
#endif

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
  TDynamicMatrix badMult(const TDynamicMatrix& m) const
  {
    if (sz != m.sz){
      throw std::out_of_range("Matrici doljni bit' odinakovoi razmernosti");
    }

    TDynamicMatrix<T> tmp(sz);

    for (size_t i = 0; i < sz; i++){
      for (size_t j = 0; j < sz; j++){        
        for (size_t k = 0; k < sz; k++){   
          tmp[i][j] += pMem[i][k] * m[k][j];
        }
      }
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
        T temp = pMem[i][k];            // chtobi lishniy raz v pamyat' ne obraschatsya
        for (size_t j = 0; j < sz; j++){   // po pamyaty ne prigaem, gladko idem!!
          tmp[i][j] += temp * m[k][j];
        }
      }
    }
    return tmp;
  }
   
  TDynamicMatrix<T> blockMult(const TDynamicMatrix<T>& m) const;

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



// CSR



template <typename T>
class TCSRmatrix{
  
  size_t row_count;
  size_t col_count;

  std::vector<T> values;
  std::vector<size_t> col_index;
  std::vector<size_t> row_ptr;
  
  public:

  TCSRmatrix (size_t row = 1, size_t col = 1) : row_count(row), col_count(col), row_ptr(row + 1) {
    if (row == 0 || col == 0 || row > MAX_MATRIX_SIZE || col > MAX_MATRIX_SIZE) {
      throw std::out_of_range("Matrica doljna bit' < 10000");
    }
  }

  TCSRmatrix (const TDynamicMatrix<T>& m) : row_count(m.size()), col_count(m.size()), row_ptr(m.size() + 1) //kontructor preobrazovaniya v CSRmatrix
  {

    if (m.size() > MAX_MATRIX_SIZE || m.size() == 0){ throw std::out_of_range("Size matrice doljni bit' 0 < x <= MAX_MATRIX_SIZE");}

    for (size_t i = 0; i < row_count; i++){
      for(size_t j = 0; j < col_count; j++){
        
        if (m[i][j] != 0){
          values.push_back(m[i][j]);
          col_index.push_back(j);
        }

      }
      row_ptr[i + 1] = values.size(); // count_not_zero_elem[i] = row_ptr[i + 1] - row_ptr[i]
    }
  }
  

  T at(size_t row, size_t col) const{
    
    if (row >= row_count || col >= col_count) { throw std::out_of_range("Index doljen bit' < row_count and < col_count"); }

    //indexi elemntov i-th stroki prinadlejat polu-intervalu [ row_ptr[i], row_ptr[i + 1] )
    size_t start = row_ptr[row]; 
    size_t end = row_ptr[row + 1];

    for (size_t j = start; j < end; j++){
      if (col_index[j] > col){  //v etoi stroke uje ne budet nenulevogo elem, vihodim iz cycle
        return T{};
      }
      if (col_index[j] == col){
        return values[j];
      }
    }

    return T{}; // if start = end (popalas' nulevaya stroka)
  }

  bool operator==(const TCSRmatrix& m) const{
    return row_count == m.row_count &&
        col_count == m.col_count &&
        values == m.values &&
        col_index == m.col_index &&
        row_ptr == m.row_ptr;
  }

  bool operator!=(const TCSRmatrix& m) const{
    return !(*this == m);
  }

  size_t get_row() const { return row_count;}

  size_t get_col() const { return col_count;}

  void set(size_t row, size_t col, T val){

    if (row >= row_count || col >= col_count) { throw std::out_of_range("Index doljen bit' < row_count and < col_count"); }

    size_t start = row_ptr[row]; 
    size_t end = row_ptr[row + 1];
    size_t insertion_index = end; //если строка фулл нули, то цикл работать не будет, поэтому сразу запоминаем

    for (size_t j = start; j < end; j++){
      
      if (col_index[j] == col){

         if (val == T{}){  // if zamenyem nenulevoi elem nulevim elem
            values.erase(values.begin() + j);
            col_index.erase(col_index.begin() + j);
            for (size_t k = row + 1; k < row_count + 1; k++) {row_ptr[k]--; }
         }
         else{          //tupo menyem znachenie
            values[j] = val;
         }
         
         return;
      }
      if (col_index[j] > col){ // столбцы в рамках одной строки упорядоченны, если такое условие выполняется - значит искать нечего - наш элемент 0
        insertion_index = j; 
        break;
      }
    }
    //esli popali v 0
    if (val != T{}){   // if val = T{} , to nichego ne delaem

      values.insert(values.begin() + insertion_index, val);
      col_index.insert(col_index.begin() + insertion_index, col);
      for (size_t k = row + 1; k < row_count + 1; k++) {row_ptr[k]++; }
    }
  }
  TCSRmatrix operator+(const TCSRmatrix<T>& m) const{

    if (row_count != m.row_count || col_count != m.col_count){
      throw std::out_of_range("Matrici doljni bit' odinakovoi razmernosti");
    }

    TCSRmatrix<T> tmp(row_count, col_count);

    size_t start_this, end_this, start_m, end_m, min_end;
    for (size_t i = 0; i < row_count; i++){ //идем по строкам

      start_this = row_ptr[i]; end_this = row_ptr[i + 1]; // указаьели на начало/конец i-ой строки по столбцам
      start_m = m.row_ptr[i]; end_m = m.row_ptr[i + 1];

      //пользуемся, что в рамках одной строки индексы столбцов упорядоченны по овзрастанию
      while (start_this < end_this && start_m < end_m){ //пока у кого-то не закончится строка

          if (col_index[start_this] > m.col_index[start_m]){ 

            tmp.col_index.push_back(m.col_index[start_m]);
            tmp.values.push_back(m.values[start_m]);

            start_m++;
          }

          else if (m.col_index[start_m] > col_index[start_this]){

            tmp.col_index.push_back(col_index[start_this]);
            tmp.values.push_back(values[start_this]);

            start_this++;
          }

          else{
            
            T temp = values[start_this] + m.values[start_m];

            if (temp != T {}){

              tmp.col_index.push_back(col_index[start_this]);
              tmp.values.push_back(temp);

            }
            start_m++;
            start_this++;
          }
      }

      //остатки, всегда будет работать один из циклов 
      while (start_this < end_this){
        tmp.col_index.push_back(col_index[start_this]);
        tmp.values.push_back(values[start_this]);

        start_this++;
      }

      while (start_m < end_m){
        tmp.col_index.push_back(m.col_index[start_m]);
        tmp.values.push_back(m.values[start_m]);

        start_m++;
      }

      tmp.row_ptr[i + 1] = tmp.values.size(); 
    }

    return tmp;
  }

  TCSRmatrix operator-(const TCSRmatrix<T>& m) const{

    if (row_count != m.row_count || col_count != m.col_count){
      throw std::out_of_range("Matrici doljni bit' odinakovoi razmernosti");
    }

    TCSRmatrix<T> tmp(row_count, col_count);

    size_t start_this, end_this, start_m, end_m, min_end;
    for (size_t i = 0; i < row_count; i++){ //идем по строкам

      start_this = row_ptr[i]; end_this = row_ptr[i + 1]; // указаьели на начало/конец i-ой строки по столбцам
      start_m = m.row_ptr[i]; end_m = m.row_ptr[i + 1];

      //пользуемся, что в рамках одной строки индексы столбцов упорядоченны по овзрастанию
      while (start_this < end_this && start_m < end_m){ //пока у кого-то не закончится строка

          if (col_index[start_this] > m.col_index[start_m]){ 

            tmp.col_index.push_back(m.col_index[start_m]);
            tmp.values.push_back(m.values[start_m]);

            start_m++;
          }

          else if (m.col_index[start_m] > col_index[start_this]){

            tmp.col_index.push_back(col_index[start_this]);
            tmp.values.push_back(values[start_this]);

            start_this++;
          }

          else{
            
            T temp = values[start_this] - m.values[start_m];

            if (temp != T {}){

              tmp.col_index.push_back(col_index[start_this]);
              tmp.values.push_back(temp);

            }
            start_m++;
            start_this++;
          }
      }

      //остатки, всегда будет работать один из циклов 
      while (start_this < end_this){
        tmp.col_index.push_back(col_index[start_this]);
        tmp.values.push_back(values[start_this]);

        start_this++;
      }

      while (start_m < end_m){
        tmp.col_index.push_back(m.col_index[start_m]);
        tmp.values.push_back(m.values[start_m]);

        start_m++;
      }

      tmp.row_ptr[i + 1] = tmp.values.size(); 
    }

    return tmp;
  }

  TCSRmatrix operator*(const T& val) const{

    if (val != T{}){

      TCSRmatrix<T> tmp(*this);

      for (size_t i = 0; i < values.size(); i++){ tmp.values[i] = values[i] * val;}
      return tmp;
    }

    else{
      
      TCSRmatrix<T> tmp1(row_count, col_count);
      return tmp1;
    }
  }

  TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
  {
    if (col_count != v.size()) {
      throw std::out_of_range("doljni bit' ravni razmeri");
    }

    TDynamicVector<T> tmp(row_count);

    for (size_t i = 0; i < row_count; i++) {

      T temp{};
      size_t start = row_ptr[i];
      size_t end = row_ptr[i + 1];

      for (size_t k = start; k < end; k++) {
        temp += values[k] * v[col_index[k]];
      }

      tmp[i] = temp;
    }

    return tmp;
  }
};




// blochnoe umnojenie
template <typename T>
TDynamicMatrix<T> TDynamicMatrix<T>::blockMult(const TDynamicMatrix<T>& m) const{

  if (m.sz != sz) { throw std::out_of_range("Matrici doljni bit' odinakovogo razmera");}
  // testirovat' smisl est' dlya bol'shih matric
  // мы не знаем, какого размера эменты типа T, но предположим, что они <= 8 байт 
  size_t blockSize = 64; // razmer bloka = 64 * 64 * 8 = 32 kilobytes => pomeschaetsya v bistryi caсhe kernel
  TDynamicMatrix<T> tmp(sz);

  #pragma omp parallel for //rasparallelivanie cycle's
  for (size_t i_0 = 0; i_0 < sz; i_0 += blockSize){
    size_t i_max = (sz < i_0 + blockSize) ? sz : i_0 + blockSize; //granica bloka po kajdome indeksu

    for (size_t k_0 = 0; k_0 < sz; k_0 += blockSize){
      size_t k_max = (sz < k_0 + blockSize) ? sz : k_0 + blockSize;

      for (size_t j_0 = 0; j_0 < sz; j_0 += blockSize){
        size_t j_max = (sz < j_0 + blockSize) ? sz : j_0 + blockSize;

        // umnojaem v granicah bloka
        for (size_t i = i_0; i < i_max; i++){

          for (size_t k = k_0; k < k_max; k++){

            T temp = pMem[i][k];

            #pragma omp simd       //prosim kompilyator vectorizovat' cycle (esli on sam etogo ne sdelaet)
            for (size_t j = j_0; j < j_max; j++){
              tmp[i][j] += temp * m[k][j];
            }
          }
        }
      }
    }
  }
  return tmp;
}
#endif
