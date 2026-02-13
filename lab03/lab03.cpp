#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
double a[6005][6005], b[6005], x[6005], xs[6005], xn[6005];
void calc(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		b[i] = 0;
		xs[i] = 1;
		for (int j = 1; j <= n; ++j)
			b[i] += (a[i][j] = 1.0 / (i + j - 1) + ((i == j) ? 2 : 0));
	}
}
bool check(int n, double eps)
{
	double norm = 0;
	for (int i = 1; i <= n; ++i)
		norm += abs(x[i] - xs[i]);
	return norm < eps;
}
int jacobi(int n, double eps, int maxit)
{
	for (int i = 1; i <= n; ++i)
		x[i] = 0;
	if (check(n, eps))
		return 0;
	for (int it = 1; it <= maxit; ++it)
	{
		for (int i = 1; i <= n; ++i)
		{
			xn[i] = b[i];
			for (int j = 1; j <= n; ++j)
				if (i != j)
					xn[i] -= a[i][j] * x[j];
			xn[i] /= a[i][i];
		}
		for (int i = 1; i <= n; ++i)
			x[i] = xn[i];
		if (check(n, eps))
			return it;
	}
	return -1;
}
int gauss(int n, double eps, int maxit)
{
	for (int i = 1; i <= n; ++i)
		x[i] = 0;
	if (check(n, eps))
		return 0;
	for (int it = 1; it <= maxit; ++it)
	{
		for (int i = 1; i <= n; ++i)
		{
			xn[i] = b[i];
			for (int j = 1; j <= n; ++j)
				if (i != j)
					xn[i] -= a[i][j] * x[j];
			xn[i] /= a[i][i];
			x[i] = xn[i];
		}
		if (check(n, eps))
			return it;
	}
	return -1;
}
int main()
{
	int _n[] = {10, 20, 80, 200, 500, 2000, 6000};
	ofstream fout("lab03.txt");
	cout << fixed << setprecision(6);
	fout << fixed << setprecision(6);
	for (int i = 0; i < 7; ++i)
	{
		int n = _n[i];
		calc(n);
		int it = jacobi(n, 1e-5, 5e5);
		if (it < 0)
		{
			cout << "Jacobi: n=" << n << ", no convergence" << endl;
			fout << "Jacobi: n=" << n << ", no convergence" << endl;
		}
		else
		{
			double norm1 = 0, norm2 = 0;
			for (int j = 1; j <= n; ++j)
			{
				norm1 += abs(x[j] - xs[j]);
				norm2 += abs(x[j]);
			}
			cout << "Jacobi: n=" << n << ", it=" << it << ", norm1=" << norm1 << ", norm2=" << norm2 << endl;
			fout << "Jacobi: n=" << n << ", it=" << it << ", norm1=" << norm1 << ", norm2=" << norm2 << endl;
		}
		it = gauss(n, 1e-5, 5e5);
		if (it < 0)
		{
			cout << "Gauss: n=" << n << ", no convergence" << endl;
			fout << "Gauss: n=" << n << ", no convergence" << endl;
		}
		else
		{
			double norm1 = 0, norm2 = 0;
			for (int j = 1; j <= n; ++j)
			{
				norm1 += abs(x[j] - xs[j]);
				norm2 += abs(x[j]);
			}
			cout << "Gauss: n=" << n << ", it=" << it << ", norm1=" << norm1 << ", norm2=" << norm2 << endl;
			fout << "Gauss: n=" << n << ", it=" << it << ", norm1=" << norm1 << ", norm2=" << norm2 << endl;
		}
	}
	return 0;
}