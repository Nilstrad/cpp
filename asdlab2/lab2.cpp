#include <iostream>
#include <fstream>

struct SparseMatrix {
    int* row;
    int* col;
    int* value;
    int size;
};

void multiplySparseMatrices(const SparseMatrix& matrix1, const SparseMatrix& matrix2, SparseMatrix& result) {
    int rows1 = matrix1.row[0];
    int cols1 = matrix1.col[0];
    int cols2 = matrix2.col[0];

    result.row = new int[rows1 * cols2];
    result.col = new int[rows1 * cols2];
    result.value = new int[rows1 * cols2];
    result.size = 0;

    for (int i = 1; i <= matrix1.size; i++) {
        for (int j = 1; j <= matrix2.size; j++) {
            if (matrix1.col[i] == matrix2.row[j]) {
                int newValue = matrix1.value[i] * matrix2.value[j];
                bool found = false;

                for (int k = 1; k <= result.size; k++) {
                    if (result.row[k] == matrix1.row[i] && result.col[k] == matrix2.col[j]) {
                        result.value[k] += newValue;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    result.size++;
                    result.row[result.size] = matrix1.row[i];
                    result.col[result.size] = matrix2.col[j];
                    result.value[result.size] = newValue;
                }
            }
        }
    }
}

void readSparseMatrixFromFile(const std::string& fileName, SparseMatrix& matrix) {
    std::ifstream file(fileName);

    file >> matrix.row[0] >> matrix.col[0];
    if(matrix.row[0] == 0 || matrix.col[0] == 0) {
        std::cout << "Error: Invalid matrix size!" << std::endl;
        return;
    }

    int maxElements = matrix.row[0] * matrix.col[0];
    matrix.row = new int[maxElements];
    matrix.col = new int[maxElements];
    matrix.value = new int[maxElements];
    matrix.size = 0;

    for (int i = 1; i <= maxElements; i++) {
        if (!file.eof()) {
            file >> matrix.row[i] >> matrix.col[i] >> matrix.value[i];
            if (matrix.value[i] != 0) {
                matrix.size++;
            }
        } else {
            break;
        }
    }

    file.close();
}

void readSparseMatrixFromConsole(SparseMatrix& matrix) {
    std::cout << "Введите количество строк матрицы: ";
    std::cin >> matrix.row[0];
    std::cout << "Введите количество столбцов матрицы: ";
    std::cin >> matrix.col[0];

    if(matrix.row[0] == 0 || matrix.col[0] == 0) {
        std::cout << "Error: Invalid matrix size!" << std::endl;
        return;
    }

    int maxElements = matrix.row[0] * matrix.col[0];
    matrix.row = new int[maxElements];
    matrix.col = new int[maxElements];
    matrix.value = new int[maxElements];
    matrix.size = 0;

    std::cout << "Введите элементы матрицы в формате <строка> <столбец> <значение>:" << std::endl;
    for (int i = 1; i <= maxElements; i++) {
        int row, col, value;
        std::cin >> row >> col >> value;
        if (value != 0) {
            matrix.size++;
            matrix.row[matrix.size] = row;
            matrix.col[matrix.size] = col;
            matrix.value[matrix.size] = value;
        }
        if (matrix.size == maxElements) {
            break;
        }
    }
}

void printSparseMatrix(const SparseMatrix& matrix) {
    std::cout << "Результат:" << std::endl;

    for (int i = 1; i <= matrix.size; i++) {
        std::cout << matrix.row[i] << " " << matrix.col[i] << " " << matrix.value[i] << std::endl;
    }
}

void deallocateSparseMatrixMemory(SparseMatrix& matrix) {
    delete[] matrix.row;
    delete[] matrix.col;
    delete[] matrix.value;
}

int main(int argc, char* argv[]) {
    SparseMatrix matrix1;
    SparseMatrix matrix2;
    SparseMatrix result;

    if (argc > 2) {
        matrix1.row = new int[1];
        matrix1.col = new int[1];
        matrix2.row = new int[1];
        matrix2.col = new int[1];

        readSparseMatrixFromFile(argv[1], matrix1);
        readSparseMatrixFromFile(argv[2], matrix2);
    } else {
        std::cout << "Входные данные для первой матрицы:" << std::endl;
        matrix1.row = new int[1];
        matrix1.col = new int[1];
        readSparseMatrixFromConsole(matrix1);

        std::cout << "Входные данные для второй матрицы:" << std::endl;
        matrix2.row = new int[1];
        matrix2.col = new int[1];
        readSparseMatrixFromConsole(matrix2);

        std::cin.ignore(); // Очистка буфера ввода после считывания
    }

    multiplySparseMatrices(matrix1, matrix2, result);

    printSparseMatrix(result);

    deallocateSparseMatrixMemory(matrix1);
    deallocateSparseMatrixMemory(matrix2);
    deallocateSparseMatrixMemory(result);

    return 0;
}