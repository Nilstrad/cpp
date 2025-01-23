#include <iostream>
#include <fstream>

struct CS_Matrix {
    int* row_indices;
    int* column_indices;
    int* values;
    int nnz;
};

struct CRS_Matrix {
    int* values;
    int* column_indices;
    int* row_pointers;
    int nnz;
};

CS_Matrix readCSMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return { nullptr, nullptr, nullptr, 0 };
    }

    int rows, cols, nnz;
    file >> rows >> cols >> nnz;

    CS_Matrix matrix;
    matrix.row_indices = new int[nnz];
    matrix.column_indices = new int[nnz];
    matrix.values = new int[nnz];
    matrix.nnz = nnz;

    for (int i = 0; i < nnz; ++i) {
        file >> matrix.row_indices[i] >> matrix.column_indices[i] >> matrix.values[i];
    }

    file.close();

    return matrix;
}

void readCSMatrixFromConsole(CS_Matrix& matrix) {
    int rows, cols, nnz;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;
    std::cout << "Введите количество ненулевых элементов: ";
    std::cin >> nnz;

    matrix.row_indices = new int[nnz];
    matrix.column_indices = new int[nnz];
    matrix.values = new int[nnz];
    matrix.nnz = nnz;

    std::cout << "Введите ненулевые элементы (строка, столбец, значение):" << std::endl;
    for (int i = 0; i < nnz; ++i) {
        std::cin >> matrix.row_indices[i] >> matrix.column_indices[i] >> matrix.values[i];
    }
}

void multiplyCSMatrices(const CS_Matrix& matrix1, const CS_Matrix& matrix2, CRS_Matrix& result) {
    // Проверяем, можно ли перемножить матрицы
    if (matrix1.column_indices[matrix1.nnz - 1] != matrix2.row_indices[matrix2.nnz - 1]) {
        std::cerr << "Невозможно перемножить матрицы: количество столбцов первой матрицы не равно количеству строк второй матрицы." << std::endl;
        return;
    }

    int rows = matrix1.row_indices[matrix1.nnz - 1];
    int cols = matrix2.column_indices[matrix2.nnz - 1];

    result.values = new int[rows * cols];
    result.column_indices = new int[rows * cols];
    result.row_pointers = new int[rows + 1];
    result.nnz = 0;

    for (int i = 0; i < rows; ++i) {
        result.row_pointers[i] = result.nnz;
        int row_start1 = (i == 0) ? 0 : matrix1.row_indices[i - 1];
        int row_end1 = matrix1.row_indices[i];

        for (int j = 0; j < cols; ++j) {
            int col_start2 = (j == 0) ? 0 : matrix2.row_indices[j - 1];
            int col_end2 = matrix2.row_indices[j];

            int sum = 0;
            int col_index = j;
            for (int k = row_start1; k < row_end1; ++k) {
                int row_index = matrix1.column_indices[k];
                for (int l = col_start2; l < col_end2; ++l) {
                    if (matrix2.column_indices[l] == row_index) {
                        sum += matrix1.values[k] * matrix2.values[l];
                        break;
                    }
                    else if (matrix2.column_indices[l] > row_index) {
                        break;
                    }
                }
            }

            if (sum != 0) {
                result.values[result.nnz] = sum;
                result.column_indices[result.nnz] = col_index;
                result.nnz++;
            }
        }
    }

    result.row_pointers[rows] = result.nnz;
}

void printCRSMatrix(const CRS_Matrix& matrix) {
    std::cout << "Результат перемножения:" << std::endl;
    for (int i = 0; i < matrix.nnz; ++i) {
        std::cout << "Значение: " << matrix.values[i]
                  << ", Столбец: " << matrix.column_indices[i]
                  << ", Строка: " << (i == 0 ? 0 : (matrix.row_pointers[i - 1] / matrix.column_indices[matrix.nnz - 1]))
                  << std::endl;
    }
}

void freeCSMatrix(CS_Matrix& matrix) {
    delete[] matrix.row_indices;
    delete[] matrix.column_indices;
    delete[] matrix.values;
    matrix.row_indices = nullptr;

matrix.column_indices = nullptr;
    matrix.values = nullptr;
    matrix.nnz = 0;
}

void freeCRSMatrix(CRS_Matrix& matrix) {
    delete[] matrix.values;
    delete[] matrix.column_indices;
    delete[] matrix.row_pointers;
    matrix.values = nullptr;
    matrix.column_indices = nullptr;
    matrix.row_pointers = nullptr;
    matrix.nnz = 0;
}

int main(int argc, char* argv[]) {
    CS_Matrix matrix1, matrix2;
    CRS_Matrix result;

    // Чтение первой матрицы
    if (argc > 1) {
        std::string filename1 = argv[1];
        matrix1 = readCSMatrixFromFile(filename1);
    }
    else {
        std::cerr << "Ошибка: не указан файл для первой матрицы." << std::endl;
        return 1;
    }

    // Чтение второй матрицы
    if (argc > 2) {
        std::string filename2 = argv[2];
        matrix2 = readCSMatrixFromFile(filename2);
    }
    else {
        std::cerr << "Ошибка: не указан файл для второй матрицы." << std::endl;
        return 1;
    }

    multiplyCSMatrices(matrix1, matrix2, result);

    // Вывод результата в формате CRS
    printCRSMatrix(result);

    // Освобождение памяти
    freeCSMatrix(matrix1);
    freeCSMatrix(matrix2);
    freeCRSMatrix(result);

    return 0;
}