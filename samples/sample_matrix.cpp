// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <clocale>
#include "tmatrix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Программа тестирования динамических матриц" << endl << endl;

    int size;
    cout << "Введите размерность квадратных матриц: ";
    cin >> size;

    if (size <= 0) {
        cout << "Ошибка. Размер матрицы должен быть положительным" << endl;
        return 1;
    }

    try {
        cout << "\n Ввод матрицы A" << endl;
        TDynamicMatrix<int> m1(size);
        cout << "Введите элементы матрицы A (" << size * size << " - их количество):" << endl;
        cin >> m1;

        cout << "\n Ввод матрицы B" << endl;
        TDynamicMatrix<int> m2(size);
        cout << "Введите элементы матрицы B (" << size * size << " - их количество):" << endl;
        cin >> m2;

        int op = -1;
        while (op != 0) {
            cout << "\n ===============МЕНЮ=============== " << endl;
            cout << "1. Вывести текущие матрицы (A и B)" << endl;
            cout << "2. Операция сложения: A + B" << endl;
            cout << "3. Операция вычитания: A - B" << endl;
            cout << "4. Операция умножения: A * B" << endl;
            cout << "5. Проверить матрицы на равенство (A == B)" << endl;
            cout << "0. Завершить работу" << endl;
            cout << "=======================================" << endl;
            cout << "Выберите пункт меню: ";
            cin >> op;

            switch (op) {
            case 1:
                cout << "\nМатрица A:" << endl << m1 << endl;
                cout << "Матрица B:" << endl << m2 << endl;
                break;
            case 2: {
                TDynamicMatrix<int> resAdd = m1 + m2;
                cout << "\nРезультат сложения (A + B):" << endl << resAdd << endl;
                break;
            }
            case 3: {
                TDynamicMatrix<int> resSub = m1 - m2;
                cout << "\nРезультат вычитания (A - B):" << endl << resSub << endl;
                break;
            }
            case 4: {
                TDynamicMatrix<int> resMul = m1 * m2;
                cout << "\nРезультат умножения (A * B):" << endl << resMul << endl;
                break;
            }
            case 5:
                if (m1 == m2) {
                    cout << "\nОтвет: Матрицы абсолютно идентичны." << endl;
                }
                else {
                    cout << "\nОтвет: Матрицы отличаются друг от друга." << endl;
                }
                break;
            case 0:
                cout << "\nВыход из программы" << endl;
                break;
            default:
                cout << "\nНеверный пункт меню, попробуйте снова." << endl;
                break;
            }
        }
    }
    catch (const exception& e) {
        cout << "\nПроизошло исключение: " << e.what() << endl;
    }

    return 0;
}
