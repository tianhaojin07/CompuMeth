#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
double f(double x)
{
	return atan(x) + 0.4 * x * sin(x / 2) + 0.601958;
}
double df(double x)
{
	return 1 / (1 + x * x) + 0.4 * sin(x / 2) + 0.2 * x * cos(x / 2);
}
pair<int, double> newton(double x0, double eps, int maxit)
{
	if (abs(f(x0)) < eps)
		return make_pair(0, x0);
	double x = x0;
	for (int i = 1; i <= maxit; i++)
	{
		double fx = f(x);
		double dfx = df(x);
		if (dfx == 0)
			return make_pair(-1, x);
		double x1 = x - fx / dfx;
		if (abs(f(x1)) < eps)
			return make_pair(i, x1);
		x = x1;
	}
	return make_pair(-1, x);
}
pair<int, double> steffensen(double x0, double eps, int maxit)
{
	if (abs(f(x0)) < eps)
		return make_pair(0, x0);
	double x = x0;
	for (int i = 1; i <= maxit; i++)
	{
		double fx = f(x);
		double de = f(x + fx) - fx;
		if (de == 0)
			return make_pair(-1, x);
		double x1 = x - fx * fx / de;
		if (abs(f(x1)) < eps)
			return make_pair(i, x1);
		x = x1;
	}
	return make_pair(-1, x);
}
int main()
{
	double x0[] = {-80, -70, -55, -36, -20, -5, -3.14, -1, 0, 1.1958, 3.14, 5, 10, 22, 33, 44, 51, 60, 80};
	ofstream fout("lab02.txt");
	fout << fixed << setprecision(6);
	cout << fixed << setprecision(6);
	for (double x : x0)
	{
		auto [it1, r1] = newton(x, 1e-8, 1e4);
		auto [it2, r2] = steffensen(x, 1e-8, 1e4);
		fout << "x0=" << x << "\n";
		cout << "x0=" << x << "\n";
		if (it1 >= 0 && abs(r1) <= 80)
		{
			fout << " Newton: it=" << it1 << " root=" << r1 << "\n";
			cout << " Newton: it=" << it1 << " root=" << r1 << "\n";
		}
		else
		{
			fout << " Newton: fail\n";
			cout << " Newton: fail\n";
		}
		if (it2 >= 0 && abs(r2) <= 80)
		{
			fout << " Steff: it=" << it2 << " root=" << r2 << "\n";
			cout << " Steff: it=" << it2 << " root=" << r2 << "\n";
		}
		else
		{
			fout << " Steff: fail\n";
			cout << " Steff: fail\n";
		}
	}
	fout.close();
	return 0;
}