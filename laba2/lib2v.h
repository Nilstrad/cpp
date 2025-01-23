#ifndef LIB2
#define LIB2


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

struct Pasagirskie{
int god_vqpuska;
int kolvo_kresel;
char familiya[32];
char tip[32];
double gruz;
};

void printin(const vector<Pasagirskie>& data, string namefile);
void print_help();

#endif