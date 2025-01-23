#include <iostream>
#include <fstream>

struct Node {
    int value;
    int childCount;
    Node** children;
};

Node* createNode(int value, int childCount) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->childCount = childCount;
    newNode->children = new Node*[childCount];
    return newNode;
}

void deleteNode(Node* node) {
    delete[] node->children;
    delete node;
}

void deleteLeafNodes(Node* node, int maxDepth, int currentDepth) {
    if (node == nullptr) {
        return;
    }
    
    if (currentDepth == maxDepth) {
        node->childCount = 0;
        delete[] node->children;
        node->children = nullptr;
        return;
    }
    
    for (int i = 0; i < node->childCount; i++) {
        deleteLeafNodes(node->children[i], maxDepth, currentDepth + 1);
    }
}

void printNode(Node* node, int depth) {
    if (node == nullptr) {
        return;
    }
    
    for (int i = 0; i < depth; i++) {
        std::cout << " ";
    }
    std::cout << node->value << std::endl;
    
    for (int i = 0; i < node->childCount; i++) {
        printNode(node->children[i], depth + 1);
    }
}

int getMaxDepth(Node* node, int currentDepth) {
    if (node == nullptr) {
        return currentDepth;
    }
    
    int maxDepth = currentDepth;
    
    for (int i = 0; i < node->childCount; i++) {
        int childDepth = getMaxDepth(node->children[i], currentDepth + 1);
        if (childDepth > maxDepth) {
            maxDepth = childDepth;
        }
    }
    
    return maxDepth;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./a.out input.txt" << std::endl;
        return 1;
    }
    
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }
    
    Node* rootNode = nullptr;
    int nodeCount;
    inputFile >> nodeCount;
    
    Node** nodes = new Node*[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        int value, childCount;
        inputFile >> value >> childCount;
        
        Node* node = createNode(value, childCount);
        
        for (int j = 0; j < childCount; j++) {
            int childValue;
            inputFile >> childValue;
            
            Node* childNode = createNode(childValue, 0);
            node->children[j] = childNode;
        }
        
        nodes[i] = node;
    }
    
    rootNode = nodes[0];
    
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            if (i != j) {
                for (int k = 0; k < nodes[i]->childCount; k++) {
                    if (nodes[i]->children[k]->value == nodes[j]->value) {
                        nodes[i]->children[k] = nodes[j];
                    }
                }
            }
        }
    }
    
    std::cout << "Дерево до удаления листьев:" << std::endl;
    printNode(rootNode, 0);
    
    int maxDepth = getMaxDepth(rootNode, 0);
    deleteLeafNodes(rootNode, maxDepth, 1);
    
    std::cout << "Дерево после удаления листьев:" << std::endl;
    printNode(rootNode, 0);
    
    for (int i = 0; i < nodeCount; i++) {
        deleteNode(nodes[i]);
    }
    delete[] nodes;
    
    return 0;
}