#include <iostream>
#include "animal.h"

Animal::Animal(int point): Object(point){
	this->count++;
}

Animal::Animal(int x, int y): Object(x, y){
	this->count++;
}

Animal::Animal(int x, int y, int hungry, int age, int childs): Object(x, y){
	this->hungry = hungry;
	this->age = age;
	this->childs = childs;
	this->count++;
}

Animal::Animal(const Animal &b): Object(b){
	this->hungry = b.getHungry();
	this->age = b.getAge();
	this->childs = b.getChilds();
	this->dead = b.getDead();
	this->count++;
}

Animal::~Animal(){
	this->count--;
}

int Animal::getAge() const{
	return this->age;
}

int Animal::getHungry() const{
	return this->hungry;
}

bool Animal::getDead() const{
	return this->dead;
}

int Animal::getChilds() const{
	return this->childs;
}

int Animal::getCount() const{
	return this->count;
}

void Animal::setHungry(int n){
	this->hungry = n;
}

void Animal::Move(){
	if(this->x < 2){
		this->x ++;
	}
	if(this->y < 2){
		this->y ++;
	}
	if(this->x > windowX-1){
		this->x --;
	}
	if(this->y > windowY-1){
		this->y --;
	}
	this->x += (rand() % 3) - 1;
	this->y += (rand() % 3) - 1;
		this->age++;
	this->hungry--;
		if (this->hungry < 0){
		this->dead = true;
	}
}

void Animal::Eat(){
	this->hungry += rand() % 100;
}

void Animal::reproduction(){
	this->hungry /= 2;
	this->childs++;
}