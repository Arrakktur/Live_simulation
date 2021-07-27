#ifndef LOCATION_H
#define LOCATION_H

class Location{
private:
	int step;

public:
	Location();

	int getStep();

	void setStep(int step);

	void upStep();

};

#endif