#ifndef LIB
#define LIB

#include <iostream>
using namespace std;


void initBoard(); // инициализируем игровое поле

void printBoard(); // выводим игровое поле на экран

bool isFull(); // проверяем, заполнено ли игровое поле

bool checkForWin(char player); // проверяем, есть ли победитель

void playGame(); // основная функция игры

#endif