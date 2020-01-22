// Lecture4_File1.cpp
#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;

const double Epsilon = 1e-10;
bool isZero(double x) {
    return fabs(x) < Epsilon;
}

double f(double x) {  return (x - 2.0) * (x +3.0); }

double f_prime(double x) { return 2.0*x + 1; }

double FindRootBisection(double a, double b)
{
    double f0 = f(a);

    double x0 = a;
    double x1 = b;
    if (f0 > 0) {
        x0 = b;
        x1 = a;
    }
    
    double f2 = 1;
    double x2 = 0;
    
    while (!isZero(f2)) {
        x2 = 0.5*(x0 + x1);
        f2 = f(x2);
        if (f2 < 0) {
            x0 = x2;
        } else {
            x1 = x2;
        }
    }
    return x2;
}

double FindRootNewton(double a)
{
    double f0 = f(a);

    double x0 = a;
    
    while (!isZero(f0)) {
		double fp = f_prime(x0);
		if (fabs(fp) > 1e-10) {
			x0 = x0 - f0/fp;
			f0 = f(x0);
		} else {
			break;
		}
    }
    return x0;
}


double FindRootSecant(double a)
{

    double x0 = a;
	double x1 = a + 0.01;
    double f0 = f(x0);
    double f1 = f(x1);
	
    while (!isZero(f0)) {
		double df = f0-f1;
		double dx = x0-x1;
		if (fabs(df) > 1e-10) {
			double x = x1 - f1*(dx/df);
			f0 = f1;
			x0 = x1;
			x1 = x;
			f1 = f(x1);
		} else {
			break;
		}
    }
    return x0;
}




int main() {
	cout << "root of (-10, 0) is " << FindRootSecant(-10) << endl;
	cout << "root of (0, 10) is " << FindRootSecant(1) << endl;
	return 0;
}
