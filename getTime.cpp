#include <iostream>
#include <stdlib.h>
using namespace std;

class getTime{
	public:
		getTime(double n);
		double time;
};

getTime::getTime(double n){
	double x = (double)rand() / (RAND_MAX + 1.0);
	time = (-1) * (x / n);
}

int main(int argc, char** argv) {
	double n;
	
	cin >> n;
	
	cout << getTime(n).time;
	
	return 0;
}
