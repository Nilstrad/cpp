#include "lib2v.h"



void print_help() {
    cout << "Usage:\n"
        "-c/--create <size> <filename> - create database\n"
        "-r/--read <size> <filename> - read database\n";
    return;
}

void printin(const vector<Pasagirskie>& data, string namefile) {
    ofstream pasdata;
    pasdata.open(namefile);
    pasdata << "-------------------------------------------------------------------------------------------------\n";
    pasdata << " №" << "| God vqpuska:" << "|Familiya konstructora:" << "|Naimenovanie tipa:" << "|Gruzopod'emnost': " << "|Kolichestvo kresel:\n";
    for (int i = 0; i < data.size(); i++) {
        pasdata << "-------------------------------------------------------------------------------------------------\n";
        pasdata << setw(1) << (i + 1) << "|" << setw(14) << data[i].god_vqpuska << "|" << setw(22)
            << data[i].familiya << "|" << setw(23) << data[i].tip << "|" << setw(24) << data[i].gruz << "|"
            << setw(17) << data[i].kolvo_kresel << "|" << endl;
    }
    pasdata << "-------------------------------------------------------------------------------------------------\n";
    pasdata.close();
}
