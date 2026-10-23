#include "../include/tmatrix.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

template<typename T>
void fillMatrix(TDynamicMatrix<T>& m)
{
    size_t n = m.size();
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            m[i][j] = static_cast<T>(rand() % 100 + 1);
}

int main()
{
    setlocale(LC_ALL, "");
    srand(42);

    cout << "=== Бенчмарк умножения матриц ===" << endl;
    cout << "Тип данных: double" << endl << endl;

    cout << "Запуск автотюнера (тест на матрице 256x256)..." << endl;
    size_t autoBlockSize = TDynamicMatrix<double>::FindOptimalBlockSize();
    cout << "Автотюнер выбрал размер блока: " << autoBlockSize << "\n\n";

    cout << "--- Проверка автотюнера на матрице 500x500 ---" << endl;
    TDynamicMatrix<double> TestA(500), TestB(500);
    fillMatrix(TestA);
    fillMatrix(TestB);

    size_t checkCandidates[] = { 16, 32, 64, 96, 128, 192, 256 };
    for (size_t bs : checkCandidates)
    {
        double t = TDynamicMatrix<double>::MeasureTime([&]() {
            auto C = TestA.BlockedMultiply(TestB, bs);
            (void)C;
            }, 3);

        cout << "  Блок " << setw(3) << bs << ": " << fixed << setprecision(2) << t << " ms" << endl;
    }
    cout << "----------------------------------------------\n\n";

    size_t sizes[] = { 100, 200, 300, 400, 500 };
    size_t fixedBlockSize = 64;

    cout << left << setw(8) << "Size"
        << setw(12) << "Simple"
        << setw(12) << "Permut."
        << setw(12) << "Block(Auto)"
        << setw(12) << "Block(64)"
        << setw(12) << "Speed(Perm)"
        << setw(12) << "Speed(Auto)"
        << setw(12) << "Speed(64)"
        << endl;
    cout << string(92, '-') << endl;

    for (size_t n : sizes)
    {
        TDynamicMatrix<double> A(n), B(n);
        fillMatrix(A);
        fillMatrix(B);

        double timeNaive = TDynamicMatrix<double>::MeasureTime([&]() {
            auto C = A.SimpleMultiply(B);
            (void)C;
            }, 3);

        double timeReordered = TDynamicMatrix<double>::MeasureTime([&]() {
            auto C = A.PermutationMultiply(B);
            (void)C;
            }, 3);

        double timeBlockedAuto = TDynamicMatrix<double>::MeasureTime([&]() {
            auto C = A.BlockedMultiply(B, autoBlockSize);
            (void)C;
            }, 3);

        double timeBlockedFixed = TDynamicMatrix<double>::MeasureTime([&]() {
            auto C = A.BlockedMultiply(B, fixedBlockSize);
            (void)C;
            }, 3);

        // Считаем ускорения
        double speedPerm = timeNaive / timeReordered;
        double speedAuto = timeNaive / timeBlockedAuto;
        double speedFixed = timeNaive / timeBlockedFixed;

        cout << left << setw(8) << n
            << setw(12) << fixed << setprecision(2) << timeNaive
            << setw(12) << timeReordered
            << setw(12) << timeBlockedAuto
            << setw(12) << timeBlockedFixed
            << setw(12) << speedPerm 
            << setw(12) << speedAuto 
            << setw(12) << speedFixed 
            << endl;
    }

    return 0;
}