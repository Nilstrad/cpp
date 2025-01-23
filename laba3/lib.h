#ifndef LIB
#define LIB

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <exception>
#include <vector>

class Samoletq {
private:
	int god;
	std::string tip;
	int kresel;
	int gruz;
	std::string familiya;
public:
	int 		get_god()const;
	std::string get_tip()const;
	int 		get_kresel()const;
	int 		get_gruz()const;
	std::string get_familiya()const;
	
	void 		set_god(int);
	void 		set_tip(std::string);
	void 		set_kresel(int);
	void 		set_gruz(int);
	void 		set_familiya(std::string);
	
	void print_table(int, int*, int)const;
	void read_file(std::ifstream&, int&, int*, int&);
};

std::ostream& operator<<(std::ostream&, Samoletq&);
std::istream& operator>>(std::istream&, Samoletq&);

int input_int();
std::string input_word(std::istream&);
std::string my_getline(std::istream&);
std::string my_getline(std::istream&, char);

void touch(const char*);
void print_help();
void create_db(const char*, int);
void read_db(const char*, int);

int get_width(int);
void print_line(int);
inline int max(int,int);
inline int min(int,int);

#endif