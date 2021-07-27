#include "location.h"

Location::Location(){
	this->step = 0;
}

int Location::getStep(){
	return this->step;
}

void Location::setStep(int step){
	this->step = step;
}

void Location::upStep(){
	this->step++;
}