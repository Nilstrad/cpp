#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void saveState(int currentFloor) {
    ofstream stateFile("state.txt");
    if (stateFile.is_open()) {
        stateFile << currentFloor << endl;
        stateFile.close();
    } else {
        cout << "Error: Unable to save state." << endl;
    }
}

void exitHandler(int currentFloor) {
    cout << "Exiting program..." << endl;
    saveState(currentFloor);
}


int main(int argc, char *argv[]) {
    bool isAdminMode = false;
    string username = "";
    string password = "12345";
    string configFile = "config.txt";
    int numFloors = 0;
    int lockedFloor = -1;
    vector<int> path;

   
    if (argc > 1) {
        if (string(argv[1]) == "admin" && argc > 2) {
            isAdminMode = true;
            username = argv[1];
            password = argv[2];
        }
    }

    
    ifstream fin(configFile);
    if (fin) {
        fin >> numFloors;
        fin >> lockedFloor;
        int floor;
        while (fin >> floor) {
            path.push_back(floor);
        }
        fin.close();
    } else {
        cout << "Error: Configuration file not found." << endl;
        return 1;
    }

    if (isAdminMode) {
        
        cout << "Enter new configuration:" << endl;
        cout << "Number of floors: ";
        cin >> numFloors;
        cout << "Locked floor (-1 for none): ";
        cin >> lockedFloor;
        path.clear();
        int floor = 0;
        while (floor != -1) {
            cout << "Add floor (-1 to finish): ";
            cin >> floor;
            if (floor != -1) {
                path.push_back(floor);
            }
        }

        
        ofstream fout(configFile);
        if (fout) {
            fout << numFloors << endl;
            fout << lockedFloor << endl;
            for (int floor : path) {
                fout << floor << endl;
            }
            fout.close();
            cout << "Configuration saved." << endl;
        } else {
            cout << "Error: Could not write to configuration file." << endl;
            return 1;
        }
    } else {
        
        int currentFloor = 1;
        int destinationFloor = 1;
         ifstream stateFile("state.txt");
    if (stateFile.is_open()) {
        stateFile >> currentFloor;
        stateFile.close();
        cout << "Resuming from floor " << currentFloor << endl;
    } else {
        cout << "Starting from floor 1" << endl;
    }

        while (true) {
            cout << "INPUT: ";
            //cin >> destinationFloor;
            string input;
            cin >> input;
            if (!cin.good()){
                cout << "Invalid destination floor." << endl;
                continue;
            }

            if (input == "exit") {
                exitHandler(currentFloor);
        exit(0);
            }

        try 
            {
             destinationFloor = stoi(input);
            if (destinationFloor < 1 || destinationFloor > numFloors) {
                cout << "Invalid destination floor." << endl;
                continue;
            }
            if (destinationFloor == lockedFloor) {
                string code;
                cout << "Enter access code: ";
                cin >> code;
                if (code != password) {
                    cout << "Access denied." << endl;
                    continue;
                }
            }
            
            
            
            path.clear();
            if (destinationFloor > currentFloor) {
                for (int floor = currentFloor + 1; floor <= destinationFloor; floor++) {
                    path.push_back(floor);
                }
            } else if (destinationFloor < currentFloor) {
                for (int floor = currentFloor - 1; floor >= destinationFloor; floor--) {
                    path.push_back(floor);
                }
            }
            cout << "OUTPUT: ";
            for (int floor : path) {
                cout << floor << " ";
            }
            cout << endl;
            currentFloor = destinationFloor;
        }
        catch (std::exception &e){
               cout << "Invalid input!!!";
               cout << endl;
            }
    }
    }


     //atexit(exitHandler);

    return 0;
}


