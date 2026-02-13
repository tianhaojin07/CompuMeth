#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
const double pi = 3.1415926535897932;

double sinu(double u)
{
	return (1 - 29593 * u * u / 207636
			+ 34911 * u * u * u * u / 7613320
			- 479249 * u * u * u * u * u * u / 11511339840)
		/ (1 + 1671 * u * u / 69212
			+ 97 * u * u * u * u / 351384
			+ 2623 * u * u * u * u * u * u / 1644477120)
		* u;
}

double sin_formula(double x)
{
	if (abs(x) < 1e-8)
		return x;
	if (abs(x) > pi / 6) {
		double t = sinu(x / 3);
		return (3 - 4 * t * t) * t;
	}
	return sinu(x);
}

double sin_taylor(double x)
{
	return x
		- x * x * x / 6
		+ x * x * x * x * x / 120
		- x * x * x * x * x * x * x / 5040;
}

int main()
{
	int a[] = {2025, 100, 10, 6, 5, 4, 3};
	ofstream fout("q3.txt");

	cout.setf(ios::scientific, ios::floatfield);
	cout.precision(9);
	fout.setf(ios::scientific, ios::floatfield);
	fout.precision(9);

	for (int i = 0; i < 7; i++) {
		double x = pi / a[i];
		double formula_val = sin_formula(x);
		double taylor_val = sin_taylor(x);
		cout << x << ' ' << formula_val << ' ' << taylor_val << endl;
		fout << x << ' ' << formula_val << ' ' << taylor_val << endl;
	}

	fout.close();
	return 0;
}
