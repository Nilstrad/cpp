#include "lib4.h"



void print_help(){
	cout << "Usage:\n"
                 "-c/--create <size> <filename> - create database\n"
                 "-r/--read <size> <filename> - read database\n";
	return;
}

void printin(const Pasagirskie data[],int quantity, string namefile){
ofstream pasdata;
pasdata.open(namefile);
pasdata<<"-------------------------------------------------------------------------------------------------\n";
pasdata<<" №"<<"| God vqpuska:"<<"|Familiya konstructora:"<<"|Naimenovanie tipa:"<<"|Gruzopod'emnost': "<<"|Kolichestvo kresel:\n";
for (int i=0; i<quantity;i++){
pasdata<<"-------------------------------------------------------------------------------------------------\n";
pasdata<<setw(1)<<(i+1)<<"|"<<setw(14)<<data[i].god_vqpuska<<"|"<<setw(22)<<data[i].familiya<<"|"<<setw(23)<<data[i].tip<<"|"<<setw(24)<<data[i].gruz<<"|"<<setw(17)<<data[i].kolvo_kresel<<"|"<<endl;
}
pasdata<<"-------------------------------------------------------------------------------------------------\n";
pasdata.close();
}

 //конструктор без параметров
    TCharArray::TCharArray(){
        cout<<"Index invalid or missing\n"<<endl;
        exit(1);
    }

    //конструктор с одним параметром
    TCharArray::TCharArray(int size1){
        arr=new char[size1];
        for(int q=0; q<size; q++){
            arr[q]=' '; 
        return;
        }
    }
    
    //деструктор
   TCharArray::~TCharArray(){
        delete []arr;
        return;
    }

    //перегрузка операции []
    char& TCharArray::operator [](int n){
    if((n<0)||(n>=size)){
        cout<<"\nInvalid index!"<<endl; 
        exit(1);
    }
    return arr[n]; 
    }
    
    void TCharArray::enter(){
        cin>>arr;
    }
    
    //метод at для доступа к элементам массива
    void TCharArray::at(int n){
        if((n<0)||(n>=size)){
        cout<<"\nInvalid index!"<<endl; 
        exit(1);
        }
        cout<<arr[n];
    }

    TString::~TString(){
        delete [] arr;
    }
    
    //определение длины строк
    size_t TString::TStrlen(const char* str){
        size_t i=0U;
        while(str[i]!='\n'){
            i++;
        }
        return i;
    }
    
    //копирование строки в строку
    char* TString::TStrcpy(char* dest, const char* str){
        size_t i=0;
        while (str[i]!=0){
            dest[i]=str[i]; 
            i++;
        }
    return dest;
    }
    
    //объединение строк
    char* TString::TStrcat(char* str1, const char* str2){
        size_t i=0U, j=0U;
        while(str1[i++]!='\n');
        while(str2[j]!='\n'){
            str1[i]=str2[j];
            i++;
            j++;
        }
        str1[i]='\n';
        return str1;
    }
    
    //сравнение строк
    int TString::TStrcmp(const char* str1, const char* str2){
        int res=0;
        size_t len1=TStrlen(str1), len2=TStrlen(str2), i;
        size_t len=(len1>len2? len1 : len2);
        for(i=0U; i<len; i++){
            res=str1[i]-str2[i];
            if(res!=0){
                break;
            }
        }
        return res;
    }

    //метод ввода строки
    void TString::enterStr(char* str){
        for(int q=0; str[q]!='\n'; q++){
		    size=q;
        }
        
        arr=new char[size+1];
        for (int q=0; q<size; q++){
            arr[q]=str[q];
        }
	//символьный массив в строку
        arr[size]='\n';
		return;
    }
    
   

    TString& TString::operator +(TString str){
    TString* sum = new TString();
    if(size+str.size<sum->size){ 
        strcpy(sum->arr, arr);  // копируем содержимое первой строки
        strcat(sum->arr, str.arr);  // добавляем содержимое второй строки
    } 
    else{ 
        cout<<"\nError! Overflow!"<<endl; 
        exit(1); 
    } 
    return *sum;
}
    
    //перегрузка оператора ==
    bool TString::operator ==(TString str){
        return(TStrcmp(arr, str.arr)==0)? true : false; 
    }
    
     //перегрузка оператора !=
     bool TString::operator !=(TString str){
        return(TStrcmp(arr, str.arr)!=0)? true : false; 
    }
    
     //перегрузка оператора >
     bool TString::operator >(TString str){
        return(TStrcmp(arr, str.arr)>0)? true : false; 
    }
    
     //перегрузка оператора <
     bool TString::operator <(TString str){
        return(TStrcmp(arr, str.arr)<0)? true : false; 
    }

TString::String(int capacity) : TCharArray(capacity), capacity(capacity) {}

TString::String(const char* str) : TCharArray(str), capacity(std::strlen(str)) {}

TString::String(const String& other) : TCharArray(other), capacity(other.capacity) {}

TString& String::operator=(const String& other) {
if (this != &other) {
delete[] buf;
size = other.size;
capacity = other.capacity;
buf = new char[capacity];
std::memcpy(buf, other.buf, size);
}
return *this;
}

void TString::add(char c) {
if (size + 1 > capacity) {
capacity *= 2;
char* temp = new char[capacity];
std::memcpy(temp, buf, size);
delete[] buf;
buf = temp;
}
buf[size++] = c;
}