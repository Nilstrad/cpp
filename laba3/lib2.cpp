#include "lib.h"



int Samoletq::get_god()const{
	return god;
}
std::string Samoletq::get_tip()const{
	return tip;
}
int Samoletq::get_kresel()const{
	return kresel;
}
int Samoletq::get_gruz()const{
	return gruz;
}
std::string Samoletq::get_familiya()const{
	return familiya;
}
void Samoletq::set_god(int god_){
	god = god_;
	return;
}
void Samoletq::set_tip(std::string tip_){
	tip = tip_;
	return;
}
void Samoletq::set_kresel(int kresel_){
	kresel = kresel_;
	return;
}
void Samoletq::set_gruz(int gruz_){
	gruz = gruz_;
	return;
}
void Samoletq::set_familiya(std::string familiya_){
	familiya = familiya_;
	return;
}

void Samoletq::print_table(int size, int* max_width, int total_max)const{
	print_line(total_max + 5 + 1);
		std::cout << '|' << std::setw(max_width[0]) << "Naimenovanie tipa" << '|' <<
				std::setw(max_width[1]) << "Familiya" << '|' << 
				std::setw(max_width[2]) << "God" << '|' <<
				std::setw(max_width[3]) << "Kolichestvo kresel" << '|' <<
				std::setw(max_width[4]) << "Gruzopod'emnost" << "|\n";
		for(int i{0}; i < size; i++){
			print_line(total_max + 5 + 1);
			std::cout << '|' << std::setw(max_width[0]) << this[i].tip << '|' <<
				std::setw(max_width[1]) << this[i].familiya << '|' << 
				std::setw(max_width[2]) << this[i].god << '|' <<
				std::setw(max_width[3]) << this[i].kresel << '|' <<
				std::setw(max_width[4]) << this[i].gruz << "|\n";
		}
		print_line(total_max + 5 + 1);
		return;
}

void Samoletq::read_file(std::ifstream& file, int& size, int* max_width, int& total_max){
	char temp{};
	int temp_{};
	file >> temp_;
	size = min(size, temp_);
	for(int i{0}; i < size; i++){
		file >> this[i].god;
		max_width[0] = max(max_width[0], get_width(this[i].god));
		file.get(temp);
		getline(file, this[i].tip, ':');
		max_width[1] = max(max_width[1], this[i].tip.size());
		file >> this[i].kresel;
		max_width[2] = max(max_width[2], get_width(this[i].kresel));
		file.get(temp);
		file >> this[i].gruz;
		max_width[3] = max(max_width[3], get_width(this[i].gruz));
		file.get(temp);
		getline(file, this[i].familiya, '\n');
		max_width[4] = max(max_width[4], this[i].familiya.size());
		total_max = max_width[0] + max_width[1] + max_width[2] + max_width[3] + max_width[4];
	}	
}

std::ostream& operator<<(std::ostream& out, Samoletq& samolet){
	out << samolet.get_god() << ':' << samolet.get_tip() << ':' <<
		samolet.get_kresel() << ':' << samolet.get_gruz() << ':' << samolet.get_familiya() << std::endl;
	return out;
}
std::istream& operator>>(std::istream& in, Samoletq& samolet){
	std::cout << "Vvedite god: ";
	samolet.set_god(input_int());
	std::cout << "Vvedite naimenovanie tipa: ";
	samolet.set_tip(my_getline(in));
	std::cout << "Vvedite kolichestvo kresel: ";
	samolet.set_kresel(input_int());
	std::cout << "Vvedite gruzopod'emnost': ";
	samolet.set_gruz(input_int());
	std::cout << "Vvedite familiyu: ";
	samolet.set_familiya(input_word(in));
	return in;
}

int input_int(){
	int res{0};
	std::cin >> res;
	while(!std::cin.good()){
		std::cout << "Please, try again. Input an integer: ";
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cin >> res;
	}
	std::cin.ignore(32767, '\n');
	return res;
}

std::string input_word(std::istream& in){
	std::string res;
	in >> res;
	return res;
}

std::string my_getline(std::istream& in){
	std::string res{};
	std::getline(in, res);
	return res;
}

std::string my_getline(std::istream& in, char sep){
	std::string res{};
	std::getline(in, res, sep);
	std::cin.ignore(32767, '\n');
	return res;
}

void touch(const char* str){
	char touch[256] = "touch ";
	strcpy((touch + 6), str);
	system(touch);
}

void print_help(){
	std::cout << "Usage:\n"
                 "-c/--create <size> <filename> - create database\n"
                 "-r/--read <size> <filename> - read database\n";
	return;
}

void create_db(const char* filename, int size){
  touch(filename);
  std::ofstream file(filename);
  if(!file.good()) 
    throw std::ostream::failure("File can't be created!");
  else{
    std::vector<Samoletq> samolets(size);
    file << size << std::endl;
    for(int i{0}; i < size; i++){
      std::cin >> samolets[i];
      file << samolets[i];
    }
  }
  file.close();
  return;
}

void read_db(const char* filename, int size){
  std::ifstream file(filename);
  if(!file.good()) 
    throw std::istream::failure("File can't be read!");
  else{
    int max_width[5]{23, 12, 10, 23, 15};
    int total_max{0};
    std::vector<Samoletq> samolets(size);
    samolets[0].read_file(file, size, max_width, total_max);
    samolets[0].print_table(size, max_width, total_max);
  }
  file.close();
  return;
}

int get_width(int i){
  int res{0};
  while(i != 0){
    res++;
    i /= 10;
  }
  return res;
}

void print_line(int width){
  for(int i{0}; i < width; i++)
    std::cout << '-';
  std::cout << std::endl;
  return;
}

inline int max(int a,int b){
  return a > b ? a : b;
}

inline int min(int a,int b){
  return a < b ? a : b;
}



