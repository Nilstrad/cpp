#ifndef LIB2
#define LIB2


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>


using namespace std;

struct Pasagirskie{
int god_vqpuska;
int kolvo_kresel;
char familiya[32];
char tip[32];
double gruz;
};



class TCharArray{
    
    
    public:
    char* arr;
    int size;

    TCharArray();

    TCharArray(int size1);
    
    ~TCharArray();

    char& operator [](int n);
    
    void  enter();
    
    void  at(int n);

    void add(char c);
};

class TString : public TCharArray{
    
    private:
    int capacity;

    public:
    ~TString();
    
    TString(int capacity = 0);
    
    size_t TStrlen(const char* str);
    
    char* TStrcpy(char* dest, const char* str);
    
    char* TStrcat(char* str1, const char* str2);
    
    int TStrcmp(const char* str1, const char* str2);

    void enterStr(char* str);

    void add(char c);

    TString& operator +(TString str);
    
    bool operator ==(TString str);
    
     bool operator !=(TString str);
    
     bool operator >(TString str);
    
     bool operator <(TString str);
     
};

void printin(const Pasagirskie data[], int quantity,string namefile);

void print_help();

#endif