#include <iostream>
#include <fstream>

bool canSplitStones(long long* stones, int N, long long* heap1, long long* heap2, int& size1, int& size2) {
    // Лексикографическая сортировка (пузырьковая сортировка)
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - i - 1; ++j) {
            if (stones[j] < stones[j + 1]) {
                // Обмен значениями
                long long temp = stones[j];
                stones[j] = stones[j + 1];
                stones[j + 1] = temp;
            }
        }
    }

    size1 = 0;
    size2 = 0;

    // Распределение камней по кучам
    for (int i = 0; i < N; ++i) {
        if (size1 <= size2) {
            heap1[size1++] = stones[i];
        } else {
            heap2[size2++] = stones[i];
        }
    }

    // Проверка условия
    for (int i = 0; i < std::min(size1, size2); ++i) {
        if (heap1[i] > 2 * heap2[i] || heap2[i] > 2 * heap1[i]) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_filename" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    int N;
    inputFile >> N;

    long long* stones = new long long[N];
    for (int i = 0; i < N; ++i) {
        inputFile >> stones[i];
    }

    inputFile.close();

    long long* heap1 = new long long[N];
    long long* heap2 = new long long[N];
    int size1, size2;

    if (canSplitStones(stones, N, heap1, heap2, size1, size2)) {
        std::cout << "Камни можно разбить на две кучи." << std::endl;
        std::cout << "Куча 1: ";
        for (int i = 0; i < size1; ++i) {
            std::cout << heap1[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "Куча 2: ";
        for (int i = 0; i < size2; ++i) {
            std::cout << heap2[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Нельзя разбить камни на две кучи так, чтобы их веса отличались не более чем в 2 раза." << std::endl;
    }

    delete[] stones;
    delete[] heap1;
    delete[] heap2;

    return 0;
}