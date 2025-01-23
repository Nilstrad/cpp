#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Lift {
private:
    int floorCount;
    int lockedFloor;

public:
    // конструктор
    Lift(int floors, int locked) {
        floorCount = floors;
        lockedFloor = locked;
    }

    // вызов лифта на этаж
    vector<int> callElevator(int floor, string code = "") {
        vector<int> path;

        // проверка кода доступа
        if (floor == lockedFloor && code != "12345") {
            cerr << "Access denied" << endl;
            return path;
        }

        // перемещение лифта на указанный этаж
        if (floor > 0 && floor <= floorCount) {
            int currentFloor = 1;
            while (currentFloor != floor) {
                if (currentFloor < floor) {
                    currentFloor++;
                }
                else {
                    currentFloor--;
                }
                path.push_back(currentFloor);
            }
        }
        else {
            cerr << "Invalid floor" << endl;
        }

        return path;
    }
};

int main() {
    // создание объекта лифта со значениями параметров по умолчанию
    Lift lift(10, 7);

    // рабочий режим программы
    string input;
    while (true) {
        cout << "<< INPUT >> ";
        getline(cin, input);

        // обработка команды на вызов лифта
        if (input.find("call ") == 0) {
            int floor = stoi(input.substr(5));
            vector<int> path = lift.callElevator(floor, "");
            if (!path.empty()) {
                cout << "<< OUTPUT >> ";
                for (int i = 0; i < path.size(); i++) {
                    cout << path[i] << " ";
                }
                cout << endl;
            }
        }
        else if (input == "exit") { // выход из программы
            break;
        }
        else { // некорректная команда
            cerr << "Invalid command" << endl;
        }
    }

    return 0;
}