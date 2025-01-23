#include <iostream>
#include <fstream>

struct Pair {
    char first;
    char second;
};

class SequenceList {
public:
    SequenceList() : head(nullptr), tail(nullptr) {}

    void addElement(const Pair& pair) {
        Node* newNode = new Node;
        newNode->value = pair;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void removeDuplicates() {
    Node* current = head;
    while (current != nullptr) {
        Node* runner = current;
        while (runner->next != nullptr) {
            if (current->value.first == runner->next->value.first || current->value.first == runner->next->value.second ||
                current->value.second == runner->next->value.first || current->value.second == runner->next->value.second) {
                Node* temp = runner->next;
                runner->next = runner->next->next;
                delete temp;
            }
            else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

bool isCompleteSequence() {
    removeDuplicates();

    int numChars = 0;
    Node* current = head;
    while (current != nullptr) {
        numChars++;
        current = current->next;
    }

    if (numChars != getSequenceLength()) {
        return false;
    }

    // Проверяем, что все символы предшествуют друг другу
    Node* runner = head;
    while (runner->next != nullptr) {
        if (runner->value.second != runner->next->value.first) {
            return false;
        }
        runner = runner->next;
    }

    return true;
}

bool isContradictorySequence() {
    Node* current = head;
    while (current != nullptr) {
        Node* current1 = current->next;
        while (current1 != nullptr) {
            if ((current->value.first == current1->value.second && current->value.second == current1->value.first) ||
                (current->value.first == current1->value.first && current->value.second == current1->value.second)) {
                return true;
            }
            current1 = current1->next;
        }
        current = current->next;
    }


    return false;
}

    ~SequenceList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

private:
    struct Node {
        Pair value;
        Node* next;
    };

    Node* head;
    Node* tail;

    int getSequenceLength() {
        int length = 0;
        Node* current = head;
        while (current != nullptr) {
            length++;
            current = current->next;
        }
        return length;
    }
};

void readSequenceFromFile(SequenceList& sequence, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    int N;
    file >> N;

    for (int i = 0; i < N; ++i) {
        Pair pair;
        file >> pair.first >> pair.second;
        sequence.addElement(pair);
    }

    file.close();
}

void readSequenceManually(SequenceList& sequence) {
    int N;
    std::cout << "Введите количество пар символов: ";
    std::cin >> N;

    while (N <= 0) {
        std::cout << "Количество пар символов должно быть положительным. Введите корректное значение: ";
        std::cin >> N;
    }

    for (int i = 0; i < N; ++i) {
        char a, b;
        std::cout << "Введите символы для пары #" << i + 1 << ": ";
        std::cin >> a >> b;
        sequence.addElement({ a, b });
    }
}

int main(int argc, char* argv[]) {
    SequenceList sequence;

    if (argc > 1) {
        std::string filename = argv[1];
        readSequenceFromFile(sequence, filename);
    }
    else {
        readSequenceManually(sequence);
    }

    if (sequence.isCompleteSequence()) {
        std::cout << "Последовательность является полной." << std::endl;
    }
    else {
        std::cout << "Последовательность не является полной." << std::endl;
    }

    if (sequence.isContradictorySequence()) {
        std::cout << "Последовательность является противоречивой." << std::endl;
    }
    else {
        std::cout << "Последовательность не является противоречивой." << std::endl;
    }

    return 0;
}