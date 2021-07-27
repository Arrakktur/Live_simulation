#ifndef OBJECT_H
#define OBJECT_H

class Object{
private:
	static int allcount;

protected:
	int x;
	int y;

public:
	Object(int point);
	Object(int x, int y);
	Object(const Object &a);
	~Object();

	int getX() const;
	int getY() const;
	int getAllCount() const;
	void setX(int x);
	void setY(int y);
	void setPlace(int point);
};

#endif