#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>
#include <ctime>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "location.h"
#include "object.h"
#include "animal.h"
#include "eat.h"

using namespace std;

//Глобальные переменные
int windowX = 20;
int windowY = 20;
int countAnimal = 15;
int countEat = 10;
int maxage = 0;
int maxchild = 0;
bool closeProgram = false;

//Массивы всех объектов
vector<Animal> anim;
vector<Eat> eat;
Location world;

//Инициализация статических переменных клас ов
int Eat::count = 0;
int Animal::count = 0;
int Object::allcount = 0;

//Перечисление команд для файла сохранения
enum Command{
	COMMAND_END = 0,
	COMMAND_STEP = 1,
	COMMAND_WINDOWX = 2,
	COMMAND_WINDOWY = 3,
	COMMAND_COUNTANIMAL = 4,
	COMMAND_COUNTEAT = 5,
	COMMAND_COUNTANIMALINFO = 6,
	COMMAND_COUNTEATINFO = 7,
	COMMAND_MAXAGE = 8,
	COMMAND_MAXCHILD = 9
};

//Задаем начальные параметры
void setUp();

//Загружаем параметры из файла
void resetUp();

//Отрисовка
void Draw();

//Функция одного шага жизни
void Life();

//Функция сохранения
void Save();

//Функция проверки конца моделирования
void revizor();

//Главная функция
int main(int argc, char *argv[]){
	srand(time(NULL));
	switch(argc){
		case 1:
			int answer;
			cout << "New Simulation - 1" << endl;
			cout << "Continue simulation - 2" << endl;
			cout << "Answer: ";
			do{
				cin >> answer;
				switch(answer){
					case 1: 
						setUp();
						break;
					case 2:
						resetUp();
						break;
					default:
						cout << "Error answer!" << endl;
				}
			}while(answer < 1 || answer > 2);
			break;
		case 2:
			if(!strcmp(argv[1], "new")){
				setUp();
			}else if(!strcmp(argv[1], "reset")){
				resetUp();
			}else{
				cout << "Error" << endl;
				exit(1);
			}
			break;
	}
	while(!closeProgram){
		Life();
		revizor();
		system("clear");
		Draw();
		Save();
		sleep(1);
	}
	cout << endl;
	return 0;
}

//Задаем начальные параметры
void setUp(){
	for (register int i = 0; i < countAnimal; i++){
		Animal a((rand() % windowX-2)+1,(rand() % windowY-2)+1);
		anim.push_back(a);
	}

	for (register int i = 0; i < countEat; i++){
		Eat e((rand() % windowX-2)+1,(rand() % windowY-2)+1);
		eat.push_back(e);
	}
}

//Загружаем параметры из файла
void resetUp(){

	ifstream file;
	file.open("save.txt");
	string buff_name;
	string buff_count;

	Command com;
	map<string, int> mapping;

	mapping["step"] = COMMAND_STEP;
	mapping["windowX"] = COMMAND_WINDOWX;
	mapping["windowY"] = COMMAND_WINDOWY;
	mapping["countAnimal"] = COMMAND_COUNTANIMAL;
	mapping["countEat"] = COMMAND_COUNTEAT;
	mapping["countAnimalinfo"] = COMMAND_COUNTANIMALINFO;
	mapping["countEatinfo"] = COMMAND_COUNTEATINFO;
	mapping["maxage"] = COMMAND_MAXAGE;
	mapping["maxchild"] = COMMAND_MAXCHILD;

	while(buff_name != "end"){
		file >> buff_name;
		switch (mapping[buff_name]){
			case COMMAND_STEP:
				file >> buff_count;
				world.setStep(atoi(buff_count.c_str()));
				break;
			case COMMAND_WINDOWX:
				file >> buff_count;
				windowX = atoi(buff_count.c_str());
				break;
			case COMMAND_WINDOWY:
				file >> buff_count;
				windowY = atoi(buff_count.c_str());
				break;
			case COMMAND_COUNTANIMAL:
				file >> buff_count;
				countAnimal = atoi(buff_count.c_str());
				break;
			case COMMAND_COUNTEAT:
				file >> buff_count;
				countEat = atoi(buff_count.c_str());
				break;
			case COMMAND_MAXAGE:
				file >> buff_count;
				maxage = atoi(buff_count.c_str());
				break;
			case COMMAND_MAXCHILD:
				file >> buff_count;
				maxchild = atoi(buff_count.c_str());
				break;
			case COMMAND_COUNTANIMALINFO:
				int x_anim;
				int y_anim;
				int hungry;
				int age;
				int child;
				for (register int i = 0; i < countAnimal; i++){
					file >> buff_name;
					file >> buff_count;
					x_anim = atoi(buff_count.c_str());
					file >> buff_name;
					file >> buff_count;
					y_anim = atoi(buff_count.c_str());
					file >> buff_name;
					file >> buff_count;
					hungry = atoi(buff_count.c_str());
					file >> buff_name;
					file >> buff_count;
					age = atoi(buff_count.c_str());
					file >> buff_name;
					file >> buff_count;
					child = atoi(buff_count.c_str());
					Animal a(x_anim, y_anim, hungry, age, child);
					anim.push_back(a);
					}
				break;
			case COMMAND_COUNTEATINFO:
				int x_eat;
				int y_eat;
				for(register int i = 0; i < countEat; i++){
					file >> buff_name;
					file >> buff_count;
					x_eat = atoi(buff_count.c_str());
					file >> buff_name;
					file >> buff_count;
					y_eat = atoi(buff_count.c_str());
					file >> buff_name;
					file >> buff_count;
					Eat e(x_eat, y_eat);
					eat.push_back(e);
				}
				break;
		}
	}

	file.close();

	cout << "Loading..." << endl;
}

//Отрисовка
void Draw(){
	bool animal_is = false;
	bool mutation_is = false;
	bool eat_is = false;
	for(register int row = 0; row <= windowY+1; row++){
		for(register int col = 0; col <= windowX+1; col++){
			if(row == 0 || col== 0 || row == windowY+1 || col == windowX+1){
				cout << " # ";
			}
			else{
				for(register int k = 0; k < anim.size(); k++){
					if(row == anim[k].getY() && col == anim[k].getX()){
						animal_is = true;
						break;
					}
				}
				for(register int k = 0; k < eat.size(); k++){
					if(row == eat[k].getY() && col == eat[k].getX()){
						eat_is = true;
						break;
					}
				}
				if(animal_is){
					cout << "\x1b[32m 0 \x1b[0m";
					animal_is = false;
				}else if (eat_is){
					cout << "\x1b[33m + \x1b[0m";
					eat_is = false;
				}
				else{
					cout << "   ";
				}
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "Step: " << world.getStep();
	cout << " | Count animals: " << anim.size();
	cout << " | Count eat: " << eat.size();
	cout << endl;
	cout << "Count all static: " << eat[0].getAllCount();
	cout << endl;
	cout << "Maxage: " << maxage;
	cout << " | Maxchild: " << maxchild;
	cout << endl << endl;
	cout << "Animal information:" << endl;
	for(register int i = 0; i < anim.size(); i++){
		cout << i+1 << ")\t";
		cout << "age: " << anim[i].getAge() << "\t";
		cout << "hungry: " << anim[i].getHungry() << "\t";
		cout << "childs: " << anim[i].getChilds() << "\t";
		cout << "place: (x:" << anim[i].getX() << ", y:" << anim[i].getY() << ")\t"; 
		cout << endl;
	}
	cout << endl;
	cout << "Eat information:" << endl;
	for(register int i = 0; i < eat.size(); i++){
		cout << i+1 << ")\t";
		cout << "place: (x:" << eat[i].getX() << ", y:" << eat[i].getY() << ")\t"; 
		cout << endl;
	}
	cout << endl;
}

//Функция одного шага жизни
void Life(){
	//Animal
	for(register int i = 0; i < anim.size(); i++){
		anim[i].Move();
		if(anim[i].getAge() > maxage){
			maxage = anim[i].getAge();
		}
		if(anim[i].getChilds() > maxchild){
			maxchild = anim[i].getChilds();
		}
		for(register int j = 0; j < eat.size(); j++){
			if(anim[i].getX() == eat[j].getX() && anim[i].getY() == eat[j].getY()){
				anim[i].Eat();
				eat.erase(eat.begin()+j);
			}
		}
		if(anim[i].getDead()){
			anim.erase(anim.begin()+i);
		}
		if(anim[i].getHungry() > 100){
			anim[i].reproduction();
			Animal a(anim[i].getX(), anim[i].getY());
			anim.push_back(a);
		}
	}

	//Eat
	Eat e((rand() % (windowX-2))+1,(rand() % (windowY-2))+1);
	if (rand() % 2 == 0 ){
		eat.push_back(e);
	}
	world.upStep();
}

//Функция сохранения
void Save(){
	ofstream file;
	file.open("save.txt");
	file << "step " << world.getStep() << endl;
	file << "windowX " << windowX << endl;
	file << "windowY " << windowY << endl;
	file << "countAnimal " << anim.size() << endl;
	file << "countEat " << eat.size() << endl;
	file << "maxage " << maxage << endl;
	file << "maxchild " << maxchild << endl;
	file << "countAnimalinfo" << endl;
	for(register int i = 0; i < anim.size(); i++){
		file << endl;
		file << "\tx " << anim[i].getX() << endl;
		file << "\ty " << anim[i].getY() << endl;
		file << "\thungry " << anim[i].getHungry() << endl;
		file << "\tage " << anim[i].getAge() << endl;
		file << "\tchild " << anim[i].getChilds() << endl;
	}
	file << "countEatinfo" << endl;
	for(register int i = 0; i < eat.size(); i++){
		file << endl;
		file << "\tx " << eat[i].getX() << endl;
		file << "\ty " << eat[i].getY() << endl;
	}
	file << "end";
	file.close();
}

//Функция проверки конца моделирования
void revizor(){
	if(eat.size() == 0){
		closeProgram = true;
	}
}