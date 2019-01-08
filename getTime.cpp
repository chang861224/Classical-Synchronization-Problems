#include <iostream>
#include <stdlib.h>
using namespace std;

double getTime(double n);

int main(int argc, char** argv) {
	double n;
	
	cin >> n;
	cout << getTime(n);
	
	return 0;
}

double
getTime(double n){
	double x = (double)rand() / (RAND_MAX + 1.0);
	
	return (-1) * (x / n);
}
