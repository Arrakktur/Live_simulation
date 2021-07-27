#include "object.h"

Object::Object(int point){
	this->allcount++;
	this->x = point;
	this->y = point;
}

Object::Object(int x, int y){
	this->allcount++;
	this->x = x;
	this->y = y;
}

Object::Object(const Object &b){
	this->x = b.getX();
	this->y = b.getY();
	this->allcount++;
}

Object::~Object(){
	this->allcount--;
}

int Object::getX() const{
	return this->x;
}

int Object::getY() const{
	return this->y;
}

int Object::getAllCount() const{
	return this->allcount;
}

void Object::setX(int x){
	this->x = x;
}

void Object::setY(int y){
	this->y = y;
}

void Object::setPlace(int point){
	this->x = point;
	this->y = point;
}