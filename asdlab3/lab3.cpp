#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Функция для подсчета количества листьев в дереве
int countLeaves(TreeNode* root) { 
    if (root == nullptr)
        return 0;
    if (root->left == nullptr && root->right == nullptr)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}


// Функция для вычисления высоты дерева
int getHeight(TreeNode* root) {
    if (root == nullptr)
        return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

// Функция для вычисления соотношения высоты к количеству листьев
double calculateRatio(TreeNode* root) {
    int numLeaves = countLeaves(root);
    int height = getHeight(root);
    return static_cast<double>(height) / numLeaves; // Соотношение высоты к количеству листьев
}

// Рекурсивная функция для вывода структуры дерева
void printTree(TreeNode* root, string prefix = "", bool isLeft = true) {
    if (root == nullptr)
        return;

    cout << prefix;
    cout << (isLeft ? "├──" : "└──");
    cout << root->data << endl;

    printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
    printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

// Рекурсивная функция для поиска минимального и максимального соотношения
void findMinMaxSubtrees(TreeNode* root, double& minRatio, double& maxRatio, TreeNode*& minRoot, TreeNode*& maxRoot) {
    if (root == nullptr)
        return;

    double ratio = calculateRatio(root); // Вычисление соотношения текущего поддерева
    
     // Обновляем минимальное или максимальное соотношение, если необходимо
    if (ratio < minRatio) {
        minRatio = ratio;
        minRoot = root;
    }
    if (ratio > maxRatio) {
        maxRatio = ratio;
        maxRoot = root;
    }

 // Рекурсивно вызываем функцию для левого и правого поддерева
    findMinMaxSubtrees(root->left, minRatio, maxRatio, minRoot, maxRoot);
    findMinMaxSubtrees(root->right, minRatio, maxRatio, minRoot, maxRoot);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: ./program <input_file>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    int rootData;
    inputFile >> rootData;
    
    TreeNode* root = new TreeNode(rootData);
    int leftData, rightData;
    inputFile >> leftData >> rightData;
 
    root->left = new TreeNode(leftData);
    root->right = new TreeNode(rightData);

    inputFile >> leftData >> rightData;

    root->left->left = new TreeNode(leftData);
    root->left->right = new TreeNode(rightData);

    inputFile >> leftData;

    root->right->left = new TreeNode(leftData);

    inputFile.close();

    printTree(root);

    double minRatio = calculateRatio(root);
    double maxRatio = calculateRatio(root);
    TreeNode* minRoot = root;
    TreeNode* maxRoot = root;
    findMinMaxSubtrees(root, minRatio, maxRatio, minRoot, maxRoot);

    cout << "Minimum Ratio Subtree: " << minRatio << endl;
    printTree(minRoot);

    cout << "Maximum Ratio Subtree: " << maxRatio << endl;
    printTree(maxRoot);

    return 0;
}