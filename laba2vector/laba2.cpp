#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <exception>
#include <vector>

struct Airplane {
    std::string name; // наименование типа
    std::string constructor; // фамилия конструктора
    int year; // год выпуска
    int seats; // количество кресел
    int payload; // грузоподъемность
};

void create_table(int N, const std::string& file_name) {
    std::vector<Airplane> arr(N);

    // здесь можно добавить код для заполнения вектора данными

    std::ofstream file(file_name);
    if (!file) {
        std::cerr << "Error opening file\n";
        return;
    }

    for (const auto& elem : arr) {
        file << elem.name << ' ' << elem.constructor << ' '
             << elem.year << ' ' << elem.seats << ' ' << elem.payload << '\n';
    }

    std::cout << "Table created and saved in " << file_name << '\n';
}

void read_table(int N, const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::vector<Airplane> arr;
    Airplane elem;

    while (file >> elem.name >> elem.constructor >> elem.year >> elem.seats >> elem.payload) {
        arr.push_back(elem);
    }

    const int size = std::min(N, static_cast<int>(arr.size())); // выбираем количество записей для вывода

    for (int i = 0; i < size; ++i) {
        std::cout << arr[i].name << ' ' << arr[i].constructor << ' '
                  << arr[i].year << ' ' << arr[i].seats << ' ' << arr[i].payload << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2 || (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        std::cout << "Usage: prog --create N file_name OR prog --read N file_name\n";
        return 0;
    }

    if (std::string(argv[1]) == "--create" || std::string(argv[1]) == "-c") {
        if (argc != 4) {
            std::cerr << "Invalid number of arguments\n";
            return 1;
        }
        const int N = std::stoi(argv[2]);
        const std::string file_name = argv[3];
        create_table(N, file_name);
    }
    else if (std::string(argv[1]) == "--read" || std::string(argv[1]) == "-r") {
        if (argc != 4) {
            std::cerr << "Invalid number of arguments\n";
            return 1;
        }
        const int N = std::stoi(argv[2]);
        const std::string file_name = argv[3];
        read_table(N, file_name);
    }
    else {
        std::cerr << "Invalid argument\n";
        return 1;
    }

    return 0;
}
