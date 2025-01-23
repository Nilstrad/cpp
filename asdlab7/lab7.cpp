#include <iostream>

const int SIZE = 5;

int grid[SIZE][SIZE] = {0};

int randomNumber() {
    static int seed = 12345; // Фиксированное значение для генерации случайных чисел
    seed = (seed * 1103515245 + 12345) & 0x7fffffff;
    return seed % 2;
}

void generateGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = randomNumber();
        }
    }
}

void printGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool checkValidMove(int rowIndex, int colIndex) {
    int val = grid[rowIndex][colIndex];
    
    // Check for duplications in row or column
    for (int i = 0; i < SIZE; i++) {
        if (grid[rowIndex][i] == val && i != colIndex) {
            return false;
        }
        if (grid[i][colIndex] == val && i != rowIndex) {
            return false;
        }
    }
    
    // Check for isolated white cells
    if (val == 0) {
        if (rowIndex - 1 >= 0 && colIndex - 1 >= 0 && grid[rowIndex - 1][colIndex - 1] == 1) {
            return false;
        }
        if (rowIndex + 1 < SIZE && colIndex + 1 < SIZE && grid[rowIndex + 1][colIndex + 1] == 1) {
            return false;
        }
        if (rowIndex - 1 >= 0 && colIndex + 1 < SIZE && grid[rowIndex - 1][colIndex + 1] == 1) {
            return false;
        }
        if (rowIndex + 1 < SIZE && colIndex - 1 >= 0 && grid[rowIndex + 1][colIndex - 1] == 1) {
            return false;
        }
    }
    
    return true;
}

bool isGameOver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!checkValidMove(i, j)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    generateGrid();
    
    while (!isGameOver()) {
        int rowIndex, colIndex;
        
        std::cout << "Enter the row index (0-4): ";
        std::cin >> rowIndex;
        
        std::cout << "Enter the column index (0-4): ";
        std::cin >> colIndex;
        
        if (rowIndex < 0 || rowIndex >= SIZE || colIndex < 0 || colIndex >= SIZE) {
            std::cout << "Invalid input! Try again." << std::endl;
            continue;
        }
        
        if (!checkValidMove(rowIndex, colIndex)) {
            std::cout << "Invalid move! Try again." << std::endl;
            continue;
        }
        
        grid[rowIndex][colIndex] = -1; // Mark the cell as crossed out
        
        printGrid();
    }
    
    std::cout << "Game over! Congratulations!" << std::endl;
    
    return 0;
}
