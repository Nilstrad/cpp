#include <iostream>
#include <fstream>

struct Coordinate {
    int row;
    int col;
    int value;
};

struct SparseMatrix {
    int rows;
    int cols;
    int num_values;
    Coordinate* values;
};

SparseMatrix read_matrix_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    int rows, cols, num_values;
    file >> rows >> cols >> num_values;

    SparseMatrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.num_values = num_values;
    matrix.values = new Coordinate[num_values];

    for (int i = 0; i < num_values; i++) {
        int row, col, value;
        file >> row >> col >> value;
        matrix.values[i] = { row, col, value };
    }

    file.close();

    return matrix;
}

int get_value(const SparseMatrix& matrix, int row, int col) {
    for (int i = 0; i < matrix.num_values; i++) {
        if (matrix.values[i].row == row && matrix.values[i].col == col) {
            return matrix.values[i].value;
        }
    }
    return 0;
}

SparseMatrix multiply_matrices(const SparseMatrix& matrix1, const SparseMatrix& matrix2);

struct CRSMatrix {
    int rows;
    int cols;
    int num_values;
    int* values;
    int* columns;
    int* row_pointers;
};

CRSMatrix convert_to_crs(const SparseMatrix& matrix) {
    int* rows = new int[matrix.rows];
    for (int i = 0; i < matrix.rows; i++) {
        rows[i] = 0;
    }

    for (int i = 0; i < matrix.num_values; i++) {
        rows[matrix.values[i].row]++;
    }

    CRSMatrix crsMatrix;
    crsMatrix.rows = matrix.rows;
    crsMatrix.cols = matrix.cols;
    crsMatrix.num_values = matrix.num_values;

    crsMatrix.values = new int[matrix.num_values];
    crsMatrix.columns = new int[matrix.num_values];
    crsMatrix.row_pointers = new int[matrix.rows + 1];

    int elements = 0;
    for (int i = 0; i < matrix.rows; i++) {
        crsMatrix.row_pointers[i] = elements;
        for (int j = 0; j < matrix.num_values; j++) {
            if (matrix.values[j].row == i) {
                crsMatrix.values[elements] = matrix.values[j].value;
                crsMatrix.columns[elements] = matrix.values[j].col;
                elements++;
            }
        }
    }
    crsMatrix.row_pointers[matrix.rows] = elements;

    return crsMatrix;
}

void print_crs_matrix(const CRSMatrix& matrix) {
    std::cout << matrix.rows << " " << matrix.cols << " " << matrix.num_values << std::endl;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = matrix.row_pointers[i]; j < matrix.row_pointers[i + 1]; j++) {
            std::cout << i << " " << matrix.columns[j] << " " << matrix.values[j] << std::endl;
        }
    }
}

void delete_sparse_matrix(SparseMatrix& matrix) {
    delete[] matrix.values;
}

void delete_crs_matrix(CRSMatrix& matrix) {
    delete[] matrix.values;
    delete[] matrix.columns;
    delete[] matrix.row_pointers;
}

int main(int argc, char* argv[]) {
    // Считывание матрицы CS из файла
    SparseMatrix matrix1 = read_matrix_from_file(argv[1]);
    SparseMatrix matrix2 = read_matrix_from_file(argv[2]);

    // Перемножение матриц
    SparseMatrix result = multiply_matrices(matrix1, matrix2);

    // Преобразование в формат CRS
    CRSMatrix crsMatrix = convert_to_crs(result);

    // Вывод матрицы в формате CRS
    print_crs_matrix(crsMatrix);

    // Освобождение памяти
    delete_sparse_matrix(matrix1);
    delete_sparse_matrix(matrix2);
    delete_sparse_matrix(result);
    delete_crs_matrix(crsMatrix);

    return 0;
}

SparseMatrix multiply_matrices(const SparseMatrix& matrix1, const SparseMatrix& matrix2) {
    if (matrix1.cols != matrix2.rows) {
        throw std::invalid_argument("Matrices cannot be multiplied");
    }

    SparseMatrix result;
    result.rows = matrix1.rows;
    result.cols = matrix2.cols;
    result.values = new Coordinate[result.rows * result.cols];
    result.num_values = 0;

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            int dot_product = 0;
            for (int k = 0; k < matrix1.cols; k++) {
                int value1 = get_value(matrix1, i, k);
                int value2 = get_value(matrix2, k, j);
                dot_product += value1 * value2;
            }
            if (dot_product != 0) {
                result.values[result.num_values++] = { i, j, dot_product };
            }
        }
    }

    return result;
}