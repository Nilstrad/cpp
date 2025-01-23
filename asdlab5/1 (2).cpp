#include <iostream>
#include <string>
#include <fstream>

class Node {
public:
    long int key;
    Node* next;

    Node(long int key) {
        this->key = key;
        this->next = nullptr;
    }
};

class HashTable {
private:
    int size;
    Node** table;

public:
    HashTable(int size) {
        this->size = size;
        table = new Node*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    int hashFunction(long int key) {
        return key % size;
    }

    void insert(long int key) {
        int index = hashFunction(key);
        Node* newNode = new Node(key);
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    bool search(long int key) {
        int index = hashFunction(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void remove(long int key) {
        int index = hashFunction(key);
        if (table[index] == nullptr) {
            return;
        }
        if (table[index]->key == key) {
            Node* temp = table[index];
            table[index] = table[index]->next;
            delete temp;
            return;
        }
        Node* current = table[index];
        while (current->next != nullptr) {
            if (current->next->key == key) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << "[" << i << "]: ";
            Node* current = table[i];
            while (current != nullptr) {
                std::cout << current->key << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }

    void rehash() {
        int newSize = size * 2;
        Node** newTable = new Node*[newSize];
        for (int i = 0; i < newSize; i++) {
            newTable[i] = nullptr;
        }

        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* next = current->next;
                int newIndex = hashFunction(current->key) % newSize;
                current->next = newTable[newIndex];
                newTable[newIndex] = current;
                current = next;
            }
        }

        delete[] table;
        table = newTable;
        size = newSize;
    }
};

void processChoice(HashTable& hashtable) {
    int choice;
    long int key;

    while (true) {
        std::cout << "1. Добавить\n2. Найти\n3. Удалить\n4. Вывести таблицу\n5. Рехешировать\n0. Выйти" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите СНИЛС: ";
                std::cin >> key;
                hashtable.insert(key);
                break;

            case 2:
                std::cout << "Введите СНИЛС для поиска: ";
                std::cin >> key;
                if (hashtable.search(key)) {
                    std::cout << "СНИЛС найден" << std::endl;
                } else {
                    std::cout << "СНИЛС не найден" << std::endl;
                }
                break;

            case 3:
                std::cout << "Введите СНИЛС для удаления: ";
                std::cin >> key;
                hashtable.remove(key);
                break;

            case 4:
                std::cout << "Таблица:" << std::endl;
                hashtable.print();
                break;

            case 5:
                hashtable.rehash();
                std::cout << "Таблица перехеширована" << std::endl;
                break;

            case 0:
                return;

            default:
                std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./program <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }

    std::string line;
    HashTable hashtable(10);
    while (std::getline(file, line)) {
        long int key = std::stol(line);
        hashtable.insert(key);
    }

    file.close();

    processChoice(hashtable);

    return 0;
}