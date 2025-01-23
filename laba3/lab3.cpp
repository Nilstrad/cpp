#include "lib.h"

char logo[] =
"********************************\n"
"* Nizhniy Novgorod Technical University*\n"
"* Study work number 2 Task number 1 *\n"
"* Performed student 22-IVT-3 Artamonov Nikita*\n"
"********************************************\n";

int main(int argc, char** argv){


	try{
        int db_size{0};
	    std::cout << logo;
	    if(argc == 1)
            throw std::invalid_argument("No arguments! Use -h for help");
	    if(argv[1][0] != '-')
            throw std::invalid_argument("Invalid key argument! Use -h for help");
	    if(!(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) 
			    print_help();
	    else if(argc < 4)
            throw std::invalid_argument("Invalid arguments! Use -h for help");
		db_size = atoi(argv[2]);
		if(db_size < 1)
            throw std::invalid_argument("Invalid size argument! Use -h for help");
		if(!(strcmp(argv[1], "-c") && strcmp(argv[1], "--create"))) 
			create_db(argv[3], db_size);
		else if(!(strcmp(argv[1], "-r") && strcmp(argv[1], "--read"))) 
			read_db(argv[3], db_size);
        else 
            throw std::invalid_argument("Invalid arguments! Use -h for help");
	    return 0;
    }
    catch(std::exception& ex){
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}



