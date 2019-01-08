#include <iostream>
#include <stdlib.h>
using namespace std;

class getTime{
	public:
		getTime(double n);
		double time();
	
	private:
		double Time;
};

getTime::getTime(double n){
	double x = (double)rand() / (RAND_MAX + 1.0);
	Time = (-1) * (x / n);
}

double getTime::time(){
	return Time;
}
