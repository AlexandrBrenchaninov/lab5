#include <iostream>
#include <cmath>
using namespace std;
const double eps = 1e-4;
//Подынтегральная функция
double myFunction(double x) {
	return (pow(sin(x), 2)) /
		pow((1 + pow(x, 3)), 0.5);
}

//Формула трапеций
double trapeziumFormula(double a, double b, int n) {
	double h = (b - a) / n;
	double s = myFunction(a) + myFunction(b);

	for (int i = 1; i < n; i++) {
		s += 2 * myFunction(a + i * h);
	}

	return (h / 2) * s;
}
//Формула Симпсона
double simpsonFormula(double a, double b, int n) {
	double h = (b - a) / n;
	double s = myFunction(a) + myFunction(b);

	for (int i = 1; i < n; i++) {
		if (i % 2 == 0) {
			s += myFunction(a + i * h) * 2;
		}
		else {
			s += myFunction(a + i * h) * 4;
		}
	}
	return (h / 3) * s;
}

double myFunction(double x, double y) {//Подынтегральная функция для кубатурного метода
	return 4 - x * x - y * y;
}

double cubatureMethod(double a, double b, double c, double d, int m, int n)//Кубатурный метод
{
	double dx = (b - a) / (2 * n);
	double dy = (d - c) / (2 * m);
	double sum = 0;
	double res = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			sum += myFunction(a + (2 * i * dx), c + (2 * j * dy));
			sum += 4 * myFunction(a + ((2 * i + 1) * dx), c + (2 * j * dy));
			sum += myFunction(a + ((2 * i + 2) * dx), c + (2 * j * dy));
			sum += 4 * myFunction(a + (2 * i * dx), c + ((2 * j + 1) * dy));
			sum += 16 * myFunction(a + ((2 * i + 1) * dx), c + ((2 * j + 1) * dy));
			sum += 4 * myFunction(a + ((2 * i + 2) * dx), c + ((2 * j + 1) * dy));
			sum += myFunction(a + (2 * i * dx), c + ((2 * j + 2) * dy));
			sum += 4 * myFunction(a + ((2 * i + 1) * dx), c + ((2 * j + 2) * dy));
			sum += myFunction(a + ((2 * i + 2) * dx), c + ((2 * j + 2) * dy));
		}
	}
	res = sum * (dx * dy / 9);
	return res;
}



int main()
{
	double a = 0;
	double b = 1.234;

	int nForTrapezium = 1;
	double previousForTrapezium = trapeziumFormula(a, b, nForTrapezium);
	double currentForTrapezium = trapeziumFormula(a, b, nForTrapezium *= 2);

	while ((currentForTrapezium - previousForTrapezium) > 3 * eps) {
		nForTrapezium *= 2;
		previousForTrapezium = currentForTrapezium;
		currentForTrapezium = trapeziumFormula(a, b, nForTrapezium);
	}

	cout << "Formula trapezium = " << currentForTrapezium << endl;
	cout << "Number of steps = " << nForTrapezium << endl;

	int nForSimpson = 1;
	double previousForSimpson = simpsonFormula(a, b, nForSimpson);
	double currentForSimpson = simpsonFormula(a, b, nForSimpson *= 2);

	while ((currentForSimpson - previousForSimpson) > 15 * eps) {
		nForSimpson *= 2;
		previousForSimpson = currentForSimpson;
		currentForSimpson = simpsonFormula(a, b, nForSimpson);
	}

	cout << "Formula simpson = " << currentForSimpson << endl;
	cout << "Number of steps = " << nForSimpson << endl;

	double integralCubatureMethod = cubatureMethod(-1, 1, -1, 1, 10, 20);

	cout << "Cubature formula simpsona = " << integralCubatureMethod << endl;
}

