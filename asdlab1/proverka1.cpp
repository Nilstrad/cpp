#include <iostream>
#include <fstream>

// Функция для проверки, является ли последовательность полной
bool isCompleteSequence(std::pair<char, char>* sequence, int N) {
  char* chars = new char[N * 2]; // Динамическое выделение памяти для массива символов без повторений
  int charsIndex = 0;

  // Заполняем массив символами без повторений
  for (int i = 0; i < N; i++) {
    bool firstFound = false;
    bool secondFound = false;
    for (int j = 0; j < charsIndex; j++) {
      if (sequence[i].first == chars[j]) {
        firstFound = true;
      }
      if (sequence[i].second == chars[j]) {
        secondFound = true;
      }
    }
    if (!firstFound) {
      chars[charsIndex++] = sequence[i].first;
    }
    if (!secondFound) {
      chars[charsIndex++] = sequence[i].second;
    }
  }

  // Проверяем, можно ли выстроить символы в цепочку
  for (int i = 1; i < charsIndex; i++) {
    bool found = false;
    for (int j = 0; j < N; j++) {
      if (sequence[j].first == chars[i - 1] && sequence[j].second == chars[i]) {
        found = true;
        break;
      }
    }
    if (!found) {
      delete[] chars; // Освобождение выделенной памяти перед возвратом
      return false;
    }
  }

  delete[] chars; // Освобождение выделенной памяти перед возвратом
  return true;
}

// Функция для проверки, является ли последовательность противоречивой
bool isContradictorySequence(std::pair<char, char>* sequence, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {

      // Если можно получить одновременно порядок (x, y) и (y, x), то последовательность противоречива
      if (sequence[i].first == sequence[j].second && sequence[i].second == sequence[j].first) {
        return true;
      }

      // Проверяем, есть ли путь от пары (x, y) к паре (y, z) через другие пары
      for (int k = 0; k < N; k++) {
        if (sequence[i].second == sequence[k].first) {
          for (int l = 0; l < N; l++) {
            if (sequence[k].second == sequence[l].first && sequence[i].first == sequence[l].second) {
              return true;
            }
          }
        }
      }
    }
  }

  return false;
}
void readSequenceFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }
    

    int N;
    file >> N;

      std::pair<char, char>* sequence = new std::pair<char, char>[N]; // Динамическое выделение памяти для массива последовательности пар символов

    for (int i = 0; i < N; i++) {
    char a, b;
    file >> a >> b;
    sequence[i] = std::make_pair(a, b);
  }

    file.close();
    // Проверка, является ли последовательность полной или противоречивой
  if (isCompleteSequence(sequence, N)) {
    std::cout << "Последовательность является полной." << std::endl;
  } else {
    std::cout << "Последовательность не является полной." << std::endl;
  }
  
  if (isContradictorySequence(sequence, N)) {
    std::cout << "Последовательность является противоречивой." << std::endl;
  } else {
    std::cout << "Последовательность не является противоречивой." << std::endl;
  }

  delete[] sequence; // Освобождение выделенной памяти
}

int main(int argc, char* argv[]) {

    if (argc > 1) {
        std::string filename = argv[1];
        readSequenceFromFile(filename);
    }
    else {
        
    
  int N; // Количество пар символов
  std::cout << "Введите количество пар символов: ";
  std::cin >> N;

  // Проверка на корректность ввода количества пар символов
  while (N <= 0) {
    std::cout << "Количество пар символов должно быть положительным. Введите корректное значение: ";
    std::cin >> N;
  }

  std::pair<char, char>* sequence = new std::pair<char, char>[N]; // Динамическое выделение памяти для массива последовательности пар символов

  // Ввод пар символов
  for (int i = 0; i < N; i++) {
    char a, b;
    std::cout << "Введите символы для пары #" << i + 1 << ": ";
    std::cin >> a >> b;
    sequence[i] = std::make_pair(a, b);
  }
    
  // Проверка, является ли последовательность полной или противоречивой
  if (isCompleteSequence(sequence, N)) {
    std::cout << "Последовательность является полной." << std::endl;
  } else {
    std::cout << "Последовательность не является полной." << std::endl;
  }
  
  if (isContradictorySequence(sequence, N)) {
    std::cout << "Последовательность является противоречивой." << std::endl;
  } else {
    std::cout << "Последовательность не является противоречивой." << std::endl;
  }

  delete[] sequence; // Освобождение выделенной памяти

  return 0;
}
}
