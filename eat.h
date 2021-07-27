#ifndef EAT_H
#define EAT_H

#include "object.h"

class Eat : public Object{
public:
	Eat(int point);
	Eat(int x, int y);
	Eat(const Eat &b);
	~Eat();

	int getCount() const;

private:
	static int count;
};

#endif