#include <iostream>
#include <cmath>
using namespace std;

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

double myFunction(double x, double y) {
	return 4 - x * x - y * y;
}

double cubatureMethod(double a, double b, double c, double d, int n) {
	double h1 = (b - a) / n;
	double h2 = (d - c) / n;

	double sum = 0.0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			double xi = a + i * h1;
			double yj = c + j * h2;
			sum += myFunction(xi + h1 / 2, yj + h2 / 2);
		}
	}

	return h1 * h2 * sum;
}

int main()
{

	double eps = 1e-4;
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

	double aForKub = -1.0;
	double bForKub = 1.0;
	double cForKub = -1.0;
	double dForKub = 1.0;

	int nForSimpsonKub = 1;
	double previousForSimpsonKub = cubatureMethod(aForKub, bForKub, cForKub, dForKub,nForSimpsonKub);
	double currentForSimpsonKub = cubatureMethod(aForKub, bForKub, cForKub, dForKub, nForSimpsonKub);

	while ((currentForSimpsonKub - previousForSimpsonKub) > 3 * eps) {
		nForSimpson *= 2;
		previousForSimpsonKub = currentForSimpsonKub;
		currentForSimpsonKub = cubatureMethod(aForKub, bForKub, cForKub, dForKub, nForSimpsonKub);
	}

	cout << "Formula simpson kub = " << currentForSimpsonKub << endl;
	cout << "Number of steps = " << nForSimpsonKub << endl;

}

