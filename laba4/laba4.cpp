




//дочерний класс для хранения строк


//Для хранения информации о квартирах
struct realty{
    char* adress = new char[256];	//Адрес с возможностью записи пробелов
    double area; 			//Площадь
    char side[16];			//Сторона света
    double price;			//Цена
    int level;				//Этаж
    int room;				//Количество комнат
};

//Записывает информацию в файл
void prInf(const realty data[], int quantity, string nameOfFile);

int main(int argc, char** argv){
    
    char logo[] =
"**************************************************************\n"
"*    ***********                                                                                              *\n" 
"*    ***********           Nizhniy Novgorid Technical University                   *\n"
"*          *****                 Study work number 4.                    	 	     *\n"
"*          *****                 Performed student 20-IVT-3 Polykov A.V.    	     *\n"
"*    ***********                                                  				     *\n"
"*    ***********                                                                                             *\n"
"**************************************************************\n";
    cout << logo << endl;
    
    string str, nameOfFile{argv[3]}, help{"-h"}, create{"-c"}, read{"-r"};
    
    //Защита
    if (argc==1){
        cout<<"Error! The second argument is invalid or missing. Please choose one of the following options:\n";
        cout<<"Help: ./realty -h\n";
        cout<<"Create: ./realty -c\n";
        cout<<"Read: ./realty -r\n"<<endl;
    }
    else{
        int q=0;	//Для switch-case
        if (argv[1]==help){
            q=1;
        }
        if (argv[1]==create){
            q=2;
        }
        if (argv[1]==read){
            q=3;
        }
        switch (q){

	    //Вывод на экран информации об использовании программы
            case 1:
                {
                cout<<"HELP:\n";
                cout<<"How to use this program:\n";
                cout<<"To create a new object in file, enter «./realty -c N file.txt» without quotes\n";
                cout<<"To read the file data, enter «./realty -r N file.txt» without quotes\n";
                cout<<"Where N is the number of objects, and name.txt is the file name\n"<<endl;
                }
                break;

	    //Создание объектов
            case 2:   
                {
                int amount=stoi(argv[2]);
                realty flat[amount]={};
                for (int q=0; q<amount; q++){

                    cout<<"ADRESS: ";
                    cin.getline(flat[q].adress, 256);

                    cout<<"LEVEL: ";
                    cin>>flat[q].level;

                    cout<<"SIDE: ";
                    cin>>flat[q].side;

                    cout<<"ROOM: ";
                    cin>>flat[q].room;

                    cout<<"AREA: ";
                    cin>>flat[q].area;

                    cout<<"PRICE: ";
                    cin>>flat[q].price;	

                    cin.get();
                    cout<<endl;
                }	
                prInf(flat, amount, nameOfFile);
                }
                break;

	    //Просмотр объектов
            case 3:
                {
                ifstream databank;
                databank.open(argv[3]);

		    //Проверка на открытие файла
                    if (!databank){
                        cout<<"Error! Cannot open file\n"<<endl;
                        }
                    else{
			//Проверка на содержание
                        if (databank.peek()==EOF){
                        cout<<"Empty file\n"<<endl;
                        }
                        else{
                            for(int i=0;i<(stoi(argv[2])+1)*2+1;i++){
                                getline(databank,str);
                                cout<<str<<endl;
                            }
                            databank.close();
                        }
                    }
                }
                break;
            default:
            {
            cout<<"Error! The second argument is invalid or missing. Please choose one of the following options:\n";
            cout<<"Help: ./realty -h\n";
            cout<<"Create: ./realty -c\n";
            cout<<"Read: ./realty -r\n"<<endl;    
            }
        }
    }
    return 0;
}

//Записывает информацию в файл
void prInf(const realty data[], int quantity, string nameOfFile){

    ofstream database;
    database.open(nameOfFile);
    database<<"______________________________________________________________________________\n";
    database<<"|    №"<<"|              ADRESS"<<"|LEVEL"<<"| SIDE"<<"|ROOM"<<"|AREA(sq.m.)"<<"|PRICE($ per 1 sq.m.)|\n";
	for (int i = 0; i<quantity; i++){
	    database<<"______________________________________________________________________________\n";
	    database<<"|"<<setw(5)<<(i+1)<<"|"<<setw(20)<<data[i].adress<<"|"<<setw(5)<<data[i].level<<"|"<<setw(5)<<data[i].side<<"|"<<setw(4)<<data[i].room<<"|"<<setw(11)<<data[i].area<<"|"<<setw(19)<<data[i].price<<"$|"<<endl;
	}
	database<<"______________________________________________________________________________\n";//Запись в файл
	database.close();
}
