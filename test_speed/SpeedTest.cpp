#include "../include/tmatrix.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;

// Функция для замера времени в миллисекундах
template<typename Func>
double measureTime(Func func, int iterations = 3)
{
    double totalMs = 0.0;
    for (int i = 0; i < iterations; i++)
    {
        auto start = chrono::high_resolution_clock::now();
        func();
        auto end = chrono::high_resolution_clock::now();
        totalMs += chrono::duration<double, milli>(end - start).count();
    }
    return totalMs / iterations;
}

// Заполнение матрицы случайными числами
template<typename T>
void fillMatrix(TDynamicMatrix<T>& m)
{
    size_t n = m.size();
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            m[i][j] = static_cast<T>(rand() % 100 + 1); // от 1 до 100
}
//Запускать в release
int main()
{
    setlocale(LC_ALL, "");
    srand(42); // фиксируем seed для воспроизводимости

    // Размеры матриц, которые будем тестировать
    size_t sizes[] = { 100, 200, 300, 400, 500 };

    // Размеры блоков, которые будем тестировать
    size_t blockSizes[] = { 8, 16, 32, 64, 128 };

    cout << "=== Бенчмарк умножения матриц ===" << endl;
    cout << "Тип данных: double" << endl;
    cout << "Итераций для замера: 3" << endl << endl;

    // Заголовок таблицы
    cout << left << setw(8) << "Size"
        << setw(15) << "simple (ms)"
        << setw(15) << "Permutation"
        << setw(15) << "Blocked"
        << setw(12) << "Best Block"
        << setw(12) << "Speedup"
        << endl;
    cout << string(75, '-') << endl;

    for (size_t n : sizes)
    {
        TDynamicMatrix<double> A(n), B(n);
        fillMatrix(A);
        fillMatrix(B);

        // 1. Наивное умножение
        double timeNaive = measureTime([&]() {
            auto C = A.SimpleMultiply(B);
            (void)C;
            });

        // 2. С перестановкой циклов
        double timeReordered = measureTime([&]() {
            auto C = A.PermutationMultiply(B);
            (void)C;
            });

        // 3. Блочное — ищем лучший блок
        double bestBlockTime = 1e18;
        size_t bestBlockSize = 0;

        for (size_t bs : blockSizes)
        {
            if (bs > n) continue; // блок больше матрицы — пропускаем

            double t = measureTime([&]() {
                auto C = A.BlockedMultiply(B, bs);
                (void)C;
                });

            if (t < bestBlockTime)
            {
                bestBlockTime = t;
                bestBlockSize = bs;
            }
        }

        // Считаем ускорение относительно простого
        double speedup = timeNaive / bestBlockTime;

        cout << left << setw(8) << n
            << setw(15) << fixed << setprecision(2) << timeNaive
            << setw(15) << timeReordered
            << setw(15) << bestBlockTime
            << setw(10) << bestBlockSize
            << setw(15) << setprecision(2) << speedup
            << endl;
    }
    return 0;
}