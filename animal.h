#ifndef ANIMAL_H
#define ANIMAL_H

#include "object.h"

extern int windowX;
extern int windowY;

class Animal : public Object{
public:
	Animal(int point);
	Animal(int x, int y);
	Animal(int x, int y, int hungry, int age, int childs);
	Animal(const Animal &b);
	~Animal();

	int getAge() const;
	int getHungry() const;
	int getChilds() const;
	int getCount() const;
	bool getDead() const;

	void setHungry(int n);

	void Move();
	void Eat();
	void reproduction();

private:
	int hungry = rand() % 100;
	int age = 0;
	bool dead = false;
	int childs = 0;
	static int count;
};

#endif