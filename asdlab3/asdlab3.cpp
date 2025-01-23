#include <iostream>
#include <fstream>

// Структура для представления узла бинарного дерева
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Функция для создания нового узла
Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        std::cerr << "Ошибка выделения памяти." << std::endl;
        return nullptr;
    }
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Функция для подсчета числа листьев в поддереве
int countLeaves(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}

// Функция для вычисления высоты поддерева
int height(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return std::max(leftHeight, rightHeight) + 1;
}

// Функция для поиска поддерева с максимальным соотношением
Node* findMaxRatioSubtree(Node* root) {
    if (root == nullptr) {
        return nullptr;
    }
    Node* maxRatioSubtree = root;
    double maxRatio = static_cast<double>(height(maxRatioSubtree)) / countLeaves(maxRatioSubtree);

    // Рекурсивно проверяем все поддеревья
    if (root->left) {
        Node* leftMaxRatioSubtree = findMaxRatioSubtree(root->left);
        double leftRatio = static_cast<double>(height(leftMaxRatioSubtree)) / countLeaves(leftMaxRatioSubtree);
        if (leftRatio > maxRatio) {
            maxRatioSubtree = leftMaxRatioSubtree;
            maxRatio = leftRatio;
        }
    }
    if (root->right) {
        Node* rightMaxRatioSubtree = findMaxRatioSubtree(root->right);
        double rightRatio = static_cast<double>(height(rightMaxRatioSubtree)) / countLeaves(rightMaxRatioSubtree);
        if (rightRatio > maxRatio) {
            maxRatioSubtree = rightMaxRatioSubtree;
            maxRatio = rightRatio;
        }
    }
    return maxRatioSubtree;
}

// Функция для поиска поддерева с минимальным соотношением
Node* findMinRatioSubtree(Node* root) {
    if (root == nullptr) {
        return nullptr;
    }
    Node* minRatioSubtree = root;
    double minRatio = static_cast<double>(height(minRatioSubtree)) / countLeaves(minRatioSubtree);

    // Рекурсивно проверяем все поддеревья
    if (root->left) {
        Node* leftMinRatioSubtree = findMinRatioSubtree(root->left);
        double leftRatio = static_cast<double>(height(leftMinRatioSubtree)) / countLeaves(leftMinRatioSubtree);
        if (leftRatio < minRatio) {
            minRatioSubtree = leftMinRatioSubtree;
            minRatio = leftRatio;
        }
    }
    if (root->right) {
        Node* rightMinRatioSubtree = findMinRatioSubtree(root->right);
        double rightRatio = static_cast<double>(height(rightMinRatioSubtree)) / countLeaves(rightMinRatioSubtree);
        if (rightRatio < minRatio) {
            minRatioSubtree = rightMinRatioSubtree;
            minRatio = rightRatio;
        }
    }
    return minRatioSubtree;
}

// Функция для чтения бинарного дерева из файла
Node* readBinaryTreeFromFile(std::ifstream& inputFile) {
    int data;
    if (!inputFile.eof()) {
        inputFile >> data;
        if (data == -1) {
            return nullptr;  // -1 обозначает пустой узел
        }
        Node* root = createNode(data);
        root->left = readBinaryTreeFromFile(inputFile);   // Рекурсивно считываем левое поддерево
        root->right = readBinaryTreeFromFile(inputFile);  // Рекурсивно считываем правое поддерево
        return root;
    }
    return nullptr;
}

// Функция для освобождения памяти, занятой деревом
void destroyTree(Node* root) {
    if (root != nullptr) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}

int main(int argc, char* argv[]) {
    std::ifstream inputFile;

    if (argc > 1) {
        inputFile.open(argv[1]);
        if (!inputFile) {std::cerr << "Не удалось открыть файл." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Не указан файл входных данных." << std::endl;
        return 1;
    }

    // Чтение бинарного дерева из файла
    Node* root = readBinaryTreeFromFile(inputFile);
    inputFile.close();

    // Поиск поддерева с максимальным соотношением
    Node* maxRatioSubtree = findMaxRatioSubtree(root);
    std::cout << "Поддерево с максимальным соотношением (высота/число листьев): ";
    if (maxRatioSubtree != nullptr) {
        std::cout << maxRatioSubtree->data << std::endl;
    } else {
        std::cout << "Нет поддеревьев." << std::endl;
    }

    // Поиск поддерева с минимальным соотношением
    Node* minRatioSubtree = findMinRatioSubtree(root);
    std::cout << "Поддерево с минимальным соотношением (высота/число листьев): ";
    if (minRatioSubtree != nullptr) {
        std::cout << minRatioSubtree->data << std::endl;
    } else {
        std::cout << "Нет поддеревьев." << std::endl;
    }

    // Освобождение памяти, занятой деревом
    destroyTree(root);

    return 0;
}