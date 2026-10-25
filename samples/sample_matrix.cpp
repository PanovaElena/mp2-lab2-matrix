// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <clocale>
#include <limits>
#include "tmatrix.h"

using namespace std;
//---------------------------------------------------------------------------

int readInt(const char* prompt)
{
    int x;
    cout << prompt;
    while (!(cin >> x))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода, повторите: ";
    }
    return x;
}

TDynamicMatrix<int> readMatrix(const char* name)
{
    int n;
    while (true)
    {
        cout << "Матрица " << name << endl;
        n = readInt("Введите размер (число строк и столбцов): ");
        if (n > 0 && n <= MAX_MATRIX_SIZE)
            break;
        cout << "Размер должен быть от 1 до " << MAX_MATRIX_SIZE << endl;
    }

    TDynamicMatrix<int> m(n);
    cout << "Введите " << n * n << " элементов по строкам через пробел:" << endl;
    while (!(cin >> m))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода, введите матрицу заново:" << endl;
    }
    return m;
}

void printMenu()
{
    cout << endl
        << "1 - сложить A + B" << endl
        << "2 - вычесть A - B" << endl
        << "3 - умножить A * B" << endl
        << "4 - сравнить A и B" << endl
        << "5 - ввести матрицы заново" << endl
        << "6 - показать матрицы" << endl
        << "0 - выход" << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Тестовое приложение для работы с матрицами" << endl << endl;

    TDynamicMatrix<int> a = readMatrix("A");
    TDynamicMatrix<int> b = readMatrix("B");

    int choice;
    do
    {
        printMenu();
        choice = readInt("Ваш выбор: ");

        try
        {
            switch (choice)
            {
            case 1:
                cout << "A + B =" << endl << a + b << endl;
                break;
            case 2:
                cout << "A - B =" << endl << a - b << endl;
                break;
            case 3:
                cout << "A * B =" << endl << a * b << endl;
                break;
            case 4:
                cout << (a == b ? "Матрицы равны" : "Матрицы не равны") << endl;
                break;
            case 5:
                a = readMatrix("A");
                b = readMatrix("B");
                break;
            case 6:
                cout << "A =" << endl << a << "B =" << endl << b << endl;
                break;
            case 0:
                break;
            default:
                cout << "Нет такого пункта меню" << endl;
            }
        }
        catch (const exception& e)
        {
            cout << "Ошибка: " << e.what() << endl;
        }
    } while (choice != 0);

    return 0;
}
//---------------------------------------------------------------------------