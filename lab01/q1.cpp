#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

float f(float x) {
	return (float)sqrt(x * x + 36.0f) - 6.0f;
}

float g(float x) {
	return x * x / ((float)sqrt(x * x + 36.0f) + 6.0f);
}

int main() {
	float x = 1.0f;
	ofstream fout("q1.txt");
	cout.setf(ios::scientific, ios::floatfield);
	cout.precision(12);
	fout.setf(ios::scientific, ios::floatfield);
	fout.precision(12);
	for (int i = 1; i <= 11; i++) {
		x /= 4.0f;
		cout << "x=" << x << "\tf(x)=" << f(x) << "\tg(x)=" << g(x) << endl;
		fout << "x=" << x << "\tf(x)=" << f(x) << "\tg(x)=" << g(x) << endl;
	}
	fout.close();
	return 0;
}