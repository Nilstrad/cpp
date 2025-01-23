#include "lib.h"

char board[100][100]; // объявляем игровое поле глобальным массивом
int boardSize; // размер игрового поля

void initBoard() { // инициализируем игровое поле
for (int i = 0; i < boardSize; i++) {
for (int j = 0; j < boardSize; j++) {
board[i][j] = '-';
}
}
}

void printBoard() { // выводим игровое поле на экран
for (int i = 0; i < boardSize; i++) {
for (int j = 0; j < boardSize; j++) {
cout << board[i][j] << " ";
}
cout << endl;
}
}

bool isFull() { // проверяем, заполнено ли игровое поле
for (int i = 0; i < boardSize; i++) {
for (int j = 0; j < boardSize; j++) {
if (board[i][j] == '-') {
return false;
}
}
}
return true;
}

bool checkForWin(char player) { // проверяем, есть ли победитель
int count;

// проверяем строки на наличие выигрышной комбинации
for (int i = 0; i < boardSize; i++) {
count = 0;
for (int j = 0; j < boardSize; j++) {
if (board[i][j] == player) {
count++;
}
}
if (count == boardSize) {
return true;
}
}

// проверяем столбцы на наличие выигрышной комбинации
for (int j = 0; j < boardSize; j++) {
count = 0;
for (int i = 0; i < boardSize; i++) {
if (board[i][j] == player) {
count++;
}
}
if (count == boardSize) {
return true;
}
}

// проверяем диагонали на наличие выигрышной комбинации
count = 0;
for (int i = 0; i < boardSize; i++) {
if (board[i][i] == player) {
count++;
}
}
if (count == boardSize) {
return true;
}

count = 0;
for (int i = 0; i < boardSize; i++) {
if (board[i][boardSize - i - 1] == player) {
count++;
}
}
if (count == boardSize) {
return true;
}

return false;
}

void playGame() {
    char player1 = 'X';
    char player2 = 'O';
    char currentPlayer = player1;
    int row, col;

    cout << "Введите размер игрового поля: ";
    cin >> boardSize;

    initBoard();
    printBoard();

    while (!isFull()) {
        cout << "Ход игрока " << currentPlayer << endl;
        
        // Проверка на корректность введенных данных
        while (true) {
            cout << "Введите номер строки: ";
            if (cin >> row && row >= 0 && row < boardSize) {
                break;
            }
            cout << "Некорректные данные!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        while (true) {
            cout << "Введите номер столбца: ";
            if (cin >> col && col >= 0 && col < boardSize) {
                break;
            }
            cout << "Некорректные данные!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

        if (board[row][col] != '-') {
            cout << "Эта клетка уже занята!" << endl;
            continue;
        }

        board[row][col] = currentPlayer;
        printBoard();

        if (checkForWin(currentPlayer)) {
            cout << "Игрок " << currentPlayer << " победил!" << endl;

            // Запрос на продолжение игры
            char answer;
            cout << "Хотите начать новую игру? (y/n)" << endl;
            cin >> answer;
            if (answer == 'y' || answer == 'Y') {
                playGame();
                return;
            } else {
                return;
            }
        }

        if (currentPlayer == player1) {
            currentPlayer = player2;
        } else {
            currentPlayer = player1;
        }
    }

    cout << "Ничья!" << endl;

    // Запрос на продолжение игры
    char answer;
    cout << "Хотите начать новую игру? (y/n)" << endl;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        playGame();
        return;
    } else {
        return;
    }
}
