#include <iostream>
#include <vector>

using namespace std;

class Eat{
	int static a;
public:
	Eat(){
		a++;
	}

	Eat(const Eat &b){
		a++;
	}

	~Eat(){
		a--;
	}

	int getA(){
		return this->a;
	}
};

int Eat::a = 0;

vector<Eat> eat;

int main(){
	eat.push_back(Eat());
	eat.push_back(Eat());
	eat.erase(eat.begin());
	cout << eat[0].getA() << endl;
	return 0;
}