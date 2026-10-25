#include <iostream>
#include <stdexcept>
#include "tmatrix.h"

int main()
{
  size_t size;
  std::cout << "Enter the size of square matrices: ";
  if (!(std::cin >> size))
  {
    std::cerr << "Invalid matrix size.\n";
    return 1;
  }

  try
  {
    TDynamicMatrix<int> first(size);
    TDynamicMatrix<int> second(size);

    std::cout << "Enter elements of the first matrix (row by row):\n";
    if (!(std::cin >> first))
    {
      std::cerr << "Could not read the first matrix.\n";
      return 1;
    }

    std::cout << "Enter elements of the second matrix (row by row):\n";
    if (!(std::cin >> second))
    {
      std::cerr << "Could not read the second matrix.\n";
      return 1;
    }

    std::cout << "Choose operation:\n"
              << "1 - add matrices\n"
              << "2 - subtract matrices\n"
              << "3 - multiply matrices\n"
              << "4 - multiply the first matrix by a scalar\n"
              << "5 - multiply the first matrix by a vector\n"
              << "Choice: ";

    int choice;
    if (!(std::cin >> choice))
    {
      std::cerr << "Invalid operation.\n";
      return 1;
    }

    switch (choice)
    {
    case 1:
    {
      TDynamicMatrix<int> result = first + second;
      std::cout << "Result:\n" << result;
      break;
    }
    case 2:
    {
      TDynamicMatrix<int> result = first - second;
      std::cout << "Result:\n" << result;
      break;
    }
    case 3:
    {
      TDynamicMatrix<int> result = first * second;
      std::cout << "Result:\n" << result;
      break;
    }
    case 4:
    {
      int scalar;
      std::cout << "Enter scalar: ";
      if (!(std::cin >> scalar))
      {
        std::cerr << "Invalid scalar.\n";
        return 1;
      }
      TDynamicMatrix<int> result = first * scalar;
      std::cout << "Result:\n" << result;
      break;
    }
    case 5:
    {
      TDynamicVector<int> vector(size);
      std::cout << "Enter vector elements: ";
      if (!(std::cin >> vector))
      {
        std::cerr << "Could not read the vector.\n";
        return 1;
      }
      TDynamicVector<int> result = first * vector;
      std::cout << "Result vector: " << result << '\n';
      break;
    }
    default:
      std::cerr << "Unknown operation. Choose a number from 1 to 5.\n";
      return 1;
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << "Error: " << error.what() << '\n';
    return 1;
  }

  return 0;
}
