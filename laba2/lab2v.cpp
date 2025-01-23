#include "lib2v.h"

using namespace std;

int main(int argc, char** argv) {

    char logo[] =
        "**********************************************\n"
        "* Nizhniy Novgorod Technical University      *\n"
        "* Study work number 2 Task number 1          *\n"
        "* Performed student 22-IVT-3 Artamonov Nikita*\n"
        "**********************************************\n";

    setlocale(LC_ALL, "RUSSIAN");

    string str, namefile{ argv[3] }, help{ "-h" }, create{ "-c" }, read{ "-r" };

    //защита

    int db_size{ 0 };
    cout << logo;
    if (argc == 1)
    {
        cout << "No arguments! Use -h for help";
        exit(1);
    }
    if (argv[1][0] != '-')
    {
        cout << "Invalid key argument! Use -h for help";
        exit(1);
    }
    if (!(strcmp(argv[1], "-h") && strcmp(argv[1], "--help")))
        print_help();
    else if (argc < 4)
    {
        cout << "Invalid arguments! Use -h for help";
        exit(1);
    }
    db_size = atoi(argv[2]);
    if (db_size < 1)
    {
        cout << "Invalid size argument! Use -h for help";
        exit(1);
    }
    if (argc == 1) {
        cout << "Ошибка, посмотрите опции" << endl;
        cout << "Help:./lab2 -h" << endl;
        cout << "Create:./lab2 -c" << endl;
        cout << "Read:./lab2 -r" << endl;
    }
    else {
        int k = 0;
        if (argv[1] == help) {
            k = 1;
        }
        if (argv[1] == create) {
            k = 2;
        }
        if (argv[1] == read) {
            k = 3;
        }
        switch (k) {
        case 1:
        {
            cout << "Help:\n";
            cout << "How to use this program:\n";
            cout << "To create a new abject in fire, enter './lab2 -c N file.txt' without quotes\n";
            cout << "To read the fire data,enter './lab2 -r N file.txt' without quotes\n";
            cout << "Where N is the number of objects and name.txt is the file name\n";
        }
        break;
        case 2: {
            int amount = atoi(argv[2]);//ПРЕОБРАЗОВАНИЕ B int
            vector<Pasagirskie> flat(amount);
            for (int k = 0; k < amount; k++) {
                cout << "God vqpuska:";
                cin >> flat[k].god_vqpuska;
                cout << "Familiya konstructora:";
                cin >> flat[k].familiya;
                cout << "Naimenovanie tipa:";
                cin >> flat[k].tip;
                cout << "Kolichestvo kresel:";
                cin >> flat[k].kolvo_kresel;
                cout << "Gruzopod'emnost':";
                cin >> flat[k].gruz;
                cin.get();
                cout << endl;
            }
            printin(flat, namefile);
        }
        break;
        case 3: {
            ifstream pasdata;
            pasdata.open(argv[3]);
            std::string str;
            if (!pasdata) {
                cout << "Ошибка открытия файла\n";
            }
            else {//ПРОВЕРКА НА СОДЕРЖАНИЕ
                if (pasdata.peek() == EOF) {
                    cout << "Empty file\n";
                }
                else {
                    while (!pasdata.eof()) {
                        getline(pasdata, str);
                        cout << str << endl;
                    }
                    pasdata.close();
                }
            }
        }
              break;
        default:
        {
            cout << "Ошибка, посмотрите опции" << endl;
            cout << "Help:./lab2 -h" << endl;
            cout << "Create:./lab2 -c" << endl;
            cout << "Read:./lab2 -r" << endl;
        }
        }
    }
    return 0;
}