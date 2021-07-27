#include "eat.h"

Eat::Eat(int point): Object(point){
	this->count++;
}

Eat::Eat(int x, int y): Object(x, y){
	this->count++;
}

Eat::Eat(const Eat &b): Object(b){
	this->count++;
}

Eat::~Eat(){
	this->count--;
}

int Eat::getCount() const{
	return this->count;
}