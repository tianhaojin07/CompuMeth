#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;
double f(double x)
{
	return exp(-x) * sin(x);
}
double F(double x)
{
	return -exp(-x) * (sin(x) + cos(x)) / 2;
}
double simpson(double a, double b, int n)
{
	double h = (b - a) / n;
	double sum = f(a) + f(b);
	for (int i = 1; i < n; i++)
	{
		double x = a + i * h;
		if (i % 2 == 0)
			sum += 2 * f(x);
		else
			sum += 4 * f(x);
	}
	return sum * h / 3;
}
double trapezoidal(double a, double b, int n)
{
	double h = (b - a) / n;
	double sum = f(a) + f(b);
	for (int i = 1; i < n; i++)
	{
		double x = a + i * h;
		sum += 2 * f(x);
	}
	return sum * h / 2;
}
int main()
{
	ofstream fout("lab05.txt");

	double exact = F(2) - F(0);
	double pre_simpson_e = 0.0, pre_trapezoidal_e = 0.0;

	cout << left << setw(10) << "n"
		 << setw(20) << "Simpson Error"
		 << setw(20) << "Trapezoidal Error"
		 << setw(18) << "Simpson Order"
		 << setw(18) << "Trapez. Order" << endl;
	cout << string(86, '-') << endl;

	fout << left << setw(10) << "n"
		 << setw(20) << "Simpson Error"
		 << setw(20) << "Trapezoidal Error"
		 << setw(18) << "Simpson Order"
		 << setw(18) << "Trapez. Order" << endl;
	fout << string(86, '-') << endl;

	for (int k = 0; k < 11; k++)
	{
		int n = 1 << k;
		double simpson_result = simpson(0, 2, n);
		double trapezoidal_result = trapezoidal(0, 2, n);
		double cur_simpson_e = abs(simpson_result - exact);
		double cur_trapezoidal_e = abs(trapezoidal_result - exact);

		cout << left << setw(10) << n
			 << scientific << setprecision(6) << setw(20) << cur_simpson_e
			 << setw(20) << cur_trapezoidal_e;

		fout << left << setw(10) << n
			 << scientific << setprecision(6) << setw(20) << cur_simpson_e
			 << setw(20) << cur_trapezoidal_e;

		if (k == 0)
		{
			pre_simpson_e = cur_simpson_e;
			pre_trapezoidal_e = cur_trapezoidal_e;
			cout << setw(18) << "-" << setw(18) << "-" << endl;
			fout << setw(18) << "-" << setw(18) << "-" << endl;
		}
		else
		{
			double simpson_order = log2(pre_simpson_e / cur_simpson_e);
			double trapezoidal_order = log2(pre_trapezoidal_e / cur_trapezoidal_e);

			cout << fixed << setprecision(5) << setw(18) << simpson_order
				 << setw(18) << trapezoidal_order << endl;

			fout << fixed << setprecision(5) << setw(18) << simpson_order
				 << setw(18) << trapezoidal_order << endl;

			pre_simpson_e = cur_simpson_e;
			pre_trapezoidal_e = cur_trapezoidal_e;
		}
	}

	fout.close();
	return 0;
}