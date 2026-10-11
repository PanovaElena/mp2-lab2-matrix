// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  int size, op;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ работы с матрицами" << endl;
  
  cout << "Введите размерность матриц: ";
  cin >> size;

  TDynamicMatrix<int> a(size), b(size), c(size);

  cout << "Введите элементы матрицы a:" << endl;
  cin >> a;
  
  cout << "Введите элементы матрицы b:" << endl;
  cin >> b;

  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;

  cout << "Выберите операцию:" << endl;
  cout << "1. a + b" << endl;
  cout << "2. a - b" << endl;
  cout << "3. a * b" << endl;
  cout << "Ваш выбор: ";
  cin >> op;

  switch (op)
  {
    case 1:
      c = a + b;
      cout << "Matrix c = a + b" << endl << c << endl;
      break;
    case 2:
      c = a - b;
      cout << "Matrix c = a - b" << endl << c << endl;
      break;
    case 3:
      c = a * b;
      cout << "Matrix c = a * b" << endl << c << endl;
      break;
    default:
      cout << "Неверная операция!" << endl;
      break;
  }
}
//---------------------------------------------------------------------------