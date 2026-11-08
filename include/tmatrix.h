// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#pragma once

#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>// для std::copy
#include <cassert>// для assert
#include <stdexcept>// для std::out_of_range, std::invalid_argument
template<class T> class SparseMatrixCoo;
const static int MAX_VECTOR_SIZE = 100'000'000;
const static int MAX_MATRIX_SIZE = 10'000;
// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz = 1;
	T* pMem = nullptr;
public:
	TDynamicVector(int size = 1, T value = T()) : sz(static_cast<size_t>(size))
	{
		if (size <= 0)
			throw std::out_of_range("Vector size should be greater than zero");
		else if (size > MAX_VECTOR_SIZE)
			throw std::out_of_range("Vector size should be less than one hundred million");
		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
		if (value != T()) {
			for (size_t i = 0; i < sz; i++)
				pMem[i] = value;
		}
	}
	TDynamicVector(T* arr, int s) :sz(static_cast<size_t>(s))
	{
		assert(arr != nullptr && "TDynamicVector requires non-nullptr argument");
		if (s <= 0)
			throw std::out_of_range("Vector size should be greater than zero");
		else if (s > MAX_VECTOR_SIZE)
			throw std::out_of_range("Vector size should be less than one hundred million");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}
	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}
	TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
	{
		v.pMem = nullptr;
	}

	~TDynamicVector() { delete[] pMem; }

	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this != &v) {
			TDynamicVector tmp(v);
			swap(*this, tmp);
		}
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		swap(*this, v);
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
	T& at(int ind)
	{
		if (!(0 <= ind && static_cast<size_t>(ind) < sz))
			throw std::out_of_range("It's impossible to turn to element");
		return pMem[static_cast<size_t>(ind)];
	}
	const T& at(int ind) const
	{
		if (!(0 <= ind && static_cast<size_t>(ind) < sz))
			throw std::out_of_range("It's impossible to turn to element");
		return pMem[static_cast<size_t>(ind)];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const
	{
		if (sz != v.sz)	return false;
		for (size_t i = 0; i < sz; i++) {
			if (pMem[i] != v[i]) return false;
		}
		return true;
	}
	bool operator!=(const TDynamicVector& v) const
	{
		return !(this->operator==(v));
	}

	// скалярные операции
	TDynamicVector<T> operator+(T val) const
	{
		TDynamicVector<T> tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] + val;
		return tmp;
	}
	TDynamicVector<T>& operator+=(T val) {
		for (size_t i = 0; i < sz; i++)
			pMem[i] += val;
		return *this;
	}
	TDynamicVector<T> operator-(T val) const
	{
		TDynamicVector<T> tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] - val;
		return tmp;
	}
	TDynamicVector<T>& operator-=(T val) {
		for (size_t i = 0; i < sz; i++)
			pMem[i] -= val;
		return *this;
	}
	TDynamicVector<T> operator*(T val) const
	{
		TDynamicVector<T> tmp(sz);
		for (size_t i = 0; i < sz; i++)
			tmp.pMem[i] = pMem[i] * val;
		return tmp;
	}
	TDynamicVector<T>& operator*=(T val) {
		for (size_t i = 0; i < sz; i++)
			pMem[i] *= val;
		return *this;
	}
	// векторные операции
	TDynamicVector<T> operator+(const TDynamicVector& v) const
	{
		if (sz == v.sz) {
			TDynamicVector<T> tmp(sz);
			for (size_t i = 0; i < sz; i++)
				tmp.pMem[i] = pMem[i] + v.pMem[i];
			return tmp;
		}
		else
			throw std::invalid_argument("Size mismatch during addition");

	}
	TDynamicVector<T>& operator+=(const TDynamicVector& v) {
		if (sz == v.sz) {
			for (size_t i = 0; i < sz; i++)
				pMem[i] += v.pMem[i];
			return *this;
		}
		else
			throw std::invalid_argument("Size mismatch during addition");

	}
	TDynamicVector<T> operator-(const TDynamicVector& v) const
	{
		if (sz == v.sz) {
			TDynamicVector<T> tmp(sz);
			for (size_t i = 0; i < sz; i++)
				tmp.pMem[i] = pMem[i] - v.pMem[i];
			return tmp;
		}
		else
			throw std::invalid_argument("Size mismatch during substraction");

	}
	TDynamicVector<T>& operator-=(const TDynamicVector& v) {
		if (sz == v.sz) {
			for (size_t i = 0; i < sz; i++)
				pMem[i] -= v.pMem[i];
			return *this;
		}
		else
			throw std::invalid_argument("Size mismatch during substraction");

	}
	T operator*(const TDynamicVector& v) const
	{
		if (sz == v.sz) {
			T res{};
			for (size_t i = 0; i < sz; i++)
				res += pMem[i] * v.pMem[i];
			return res;
		}
		else
			throw std::invalid_argument("Size mismatch during multiplication");
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
	//static size_t cor_size(int sz) {
	//	if (sz <= 0)
	//		throw std::out_of_range("Matrix size should be greater than zero");
	//	else if (sz > MAX_MATRIX_SIZE)
	//		throw std::out_of_range("Matrix size should be less than ten hundred");
	//	else
	//		return static_cast<size_t>(sz);
	//}
public:
	TDynamicMatrix(int s = 1) : TDynamicVector<TDynamicVector<T>>(s, TDynamicVector<T>(s))
	{
		if (sz > MAX_MATRIX_SIZE)
			throw std::out_of_range("Matrix size should be less than ten thousand");
		sz = s;
	}

	using TDynamicVector<TDynamicVector<T>>::operator[];
	//using TDynamicVector<TDynamicVector<T>>::at();

	TDynamicVector<T>& at(int ind) {
		if (!(0 <= ind && static_cast<size_t>(ind) < sz))
			throw std::out_of_range("It's impossible to turn to element");
		return pMem[static_cast<size_t>(ind)];
	}
	const TDynamicVector<T>& at(int ind) const {
		if (!(0 <= ind && static_cast<size_t>(ind) < sz))
			throw std::out_of_range("It's impossible to turn to element");
		return pMem[static_cast<size_t>(ind)];
	}
	size_t size() const noexcept { return sz; }

	// сравнение
	bool operator==(const TDynamicMatrix& m) const
	{
		if (sz != m.sz) return false;
		for (size_t i = 0; i < sz; i++)
			for (size_t j = 0; j < sz; j++)
				if (pMem[i][j] != m.pMem[i][j])
					return false;
		return true;
	}
	bool operator!=(const TDynamicMatrix& m) const
	{
		if (sz != m.sz) return true;
		for (size_t i = 0; i < sz; i++)
			if (pMem[i] != m[i])
				return true;
		return false;
	}

	// матрично-скалярные операции
	TDynamicMatrix<T> operator*(const T& val) const
	{
		TDynamicMatrix<T> res(*this);
		for (size_t i = 0; i < sz; i++)
			res[i] *= val;
		return res;	
	}
	TDynamicMatrix<T>& operator*=(const T& val)
	{
		for (size_t i = 0; i < sz; i++)
			pMem[i] *= val;
		return *this;
	}
	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v) const
	{
		if (sz == v.size()) {
			TDynamicVector<T> res(sz);
			for (size_t i = 0; i < sz; i++)
				res[i] = pMem[i] * v;
			return res;
		}
		else
			throw std::invalid_argument("Size mismatch during multiplication");
	}
	// матрично-матричные операции
	TDynamicMatrix<T> operator+(const TDynamicMatrix& m) const
	{
		// можно ли написать реализацию, используя operator+ вектора?
		if (sz == m.sz) {
			TDynamicMatrix<T> res(sz);
			for (size_t i = 0; i < sz; i++)
				res.pMem[i] = pMem[i] + m.pMem[i];
			return res;
		}
		else
			throw std::invalid_argument("Size mismatch during addition");

	}
	TDynamicMatrix<T>& operator+=(const TDynamicMatrix& m)
	{
		if (sz == m.sz) {

			for (size_t i = 0; i < sz; i++)
				pMem[i] += m.pMem[i];
			return *this;
		}
		else
			throw std::invalid_argument("Size mismatch during addition");

	}
	TDynamicMatrix<T> operator-(const TDynamicMatrix& m) const
	{
		if (sz == m.sz) {

			TDynamicMatrix<T> res(sz);
			for (size_t i = 0; i < sz; i++)
				res.pMem[i] = pMem[i] - m.pMem[i];
			return res;
		}
		else
			throw std::invalid_argument("Size mismatch during substraction");

	}
	TDynamicMatrix<T>& operator-=(const TDynamicMatrix& m)
	{
		if (sz == m.sz) {

			for (size_t i = 0; i < sz; i++)
				pMem[i] -= m.pMem[i];
			return *this;
		}
		else
			throw std::invalid_argument("Size mismatch during substraction");

	}
	TDynamicMatrix<T> operator*(const TDynamicMatrix& m) const
	{
		if (sz == m.sz) {

			TDynamicMatrix<T> res(sz);
#pragma omp parallel for
			for (size_t i = 0; i < sz; i++) //вроде бы нужен знаковый тип? 
				for (size_t k = 0; k < sz; k++) {
					T sum = T(0);
					for (size_t j = 0; j < sz; j++)
						sum += pMem[i][j] * m[j][k]; //оптимизация обращения к памяти
					res[i][k] = sum;
				}
			return res;
		}
		else
			throw std::invalid_argument("Size mismatch during multiplication");
	}

	// ввод/вывод
	friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.size(); i++)
			istr >> m[i];
		return istr;
	}
	friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.size(); i++)
			ostr << m[i];
		return ostr;
	}

};

template<class T> class SparseMatrixCoo {
	std::vector<T> data;
	std::vector<size_t> rowInd;
	std::vector<size_t> colInd;
	size_t row, col;
public:
	SparseMatrixCoo(int rows, int cols) {
		if (rows > 0 && cols > 0) {
			row = static_cast<size_t>(rows);
			col = static_cast<size_t>(cols);
		}
		else 
			throw std::out_of_range("Sparse matrix size should be greater than zero");
	}
	SparseMatrixCoo(const TDynamicMatrix<T>& m) : row(m.size()), col(m.size()) {
		for (size_t r = 0; r < row; r++) {
			for (size_t c = 0; c < col; c++) {
				if (m[r][c] != T(0)) { //тип T должен иметь конструктор преобразования типов
					data.push_back(m[r][c]);
					rowInd.push_back(r);
					colInd.push_back(c);
				}
			}
		}
	}
	SparseMatrixCoo(const TDynamicMatrix<T>& m, int rows, int cols) : 
		row(static_cast<size_t>(rows)), col(static_cast<size_t>(cols)) {

		if (rows <= 0 || cols <= 0)
			throw std::out_of_range("Sparse matrix size should be greater than zero");
		else {
			for (size_t r = 0; r < row; r++) {
				for (size_t c = 0; c < col; c++) {
					if (m[r][c] != T(0)) { //тип T должен иметь конструктор преобразования типов
						data.push_back(m[r][c]);
						rowInd.push_back(r);
						colInd.push_back(c);
					}
				}
			}
		}
	}
	size_t rows() const noexcept { return row; }
	size_t cols() const noexcept { return col; }
	size_t values() const noexcept { return data.size(); }

	/*
	* можно было попробовать operator[] с двумя аргументами,
	* в каком-то новом стандарте это разрешено(?)
	*/
	T operator()(int r, int c) const {
		size_t val = data.size();
		for (size_t i = 0; i < val; i++) {
			if (rowInd[i] == static_cast<size_t>(r)) {
				for (size_t j = i; (j < val && rowInd[j] == static_cast<size_t>(r)); j++) {
					if (colInd[j] == static_cast<size_t>(c))
						return data[j];
				}
				return T(0);
			}
		}
		return T(0);
	}
	//пришлось возвращать по значению, потому что может вернуться временный объект T(0);
	T at(int r, int c) const {
		if (r < 0 || c < 0)
			throw std::out_of_range("It's impossible to turn to element with negative index");
		if (static_cast<size_t>(r) >= row || static_cast<size_t>(c) >= col)
			throw std::out_of_range("It's impossible to turn to element with too large index");
		else {
			return operator()(r, c);
		}
	}
	void set_element(size_t r, size_t c, const T& value) {
		if (r >= row || c >= col)
			throw std::out_of_range("It's impossible to turn to element");
		
		size_t val = data.size();
		size_t pos = 0;
		while (pos < val && (rowInd[pos] < r || (rowInd[pos] == r && colInd[pos] < c)))
			++pos;

		//заменяем, если найден
		if (pos < val && rowInd[pos] == r && colInd[pos] == c) {
			if (value == T(0)) {
				data.erase(data.begin() + pos);
				rowInd.erase(rowInd.begin() + pos);
				colInd.erase(colInd.begin() + pos);
				return;
			}
			else {
				data[pos] = value;
			}
			return;
		}
		if (value == T(0)) return;
		//иначе вставляем в позицию pos
		data.insert(data.begin() + pos, value);
		rowInd.insert(rowInd.begin() + pos, r);
		colInd.insert(colInd.begin() + pos, c);
	}
	SparseMatrixCoo operator+(const SparseMatrixCoo& sm) const {
		if (row != sm.row || col != sm.col)
			throw std::invalid_argument("Size mismatch during addition");

		TDynamicMatrix<T> tmp1(static_cast<size_t>(std::max(row, col)));
		for (size_t i = 0; i < data.size(); i++) {
			tmp1[rowInd[i]][colInd[i]] = data[i];
		}
		TDynamicMatrix<T> tmp2(static_cast<size_t>(std::max(row, col)));
		for (size_t i = 0; i < sm.data.size(); i++) {
			tmp2[sm.rowInd[i]][sm.colInd[i]] = sm.data[i];
		}
		return SparseMatrixCoo<T>(tmp1 + tmp2, static_cast<int>(row), static_cast<int>(col));
	}
	friend std::ostream& operator<<(std::ostream& ostr, const SparseMatrixCoo& sm) {
		size_t k = 0;
		for (size_t r = 0; r < sm.row; r++) {
			for (size_t c = 0; c < sm.col; c++) {
				if (k < sm.data.size() && sm.rowInd[k] == r && sm.colInd[k] == c) {
					ostr << sm.data[k] << ' ';
					k++;
				}
				else {
					ostr << T(0) << ' ';
				}
			}
			ostr << '\n';
		}
		return ostr;
	}
	friend std::istream& operator>>(std::istream& istr, SparseMatrixCoo& sm) {
		sm.data.clear();
		sm.rowInd.clear();
		sm.colInd.clear();
		for (size_t r = 0; r < sm.row; r++) {
			for (size_t c = 0; c < sm.col; c++) {
				T x;
				if (!(istr >> x)) return istr; //тип T должен иметь operator>>
				if (x != T(0)) { //тип T должен иметь конструктор преобразования типов
					sm.data.push_back(x);
					sm.rowInd.push_back(r);
					sm.colInd.push_back(c);
				}
			}
		}
		return istr;
	}
	bool operator==(const SparseMatrixCoo& sm) const {
		if (data != sm.data || rowInd != sm.rowInd || colInd != sm.colInd
			|| row != sm.row || col != sm.col)
			return false;
		return true;
	}
	bool operator!=(const SparseMatrixCoo& sm) const {
		return !(*this == sm);
	}
};
