#include <iostream>						
#include <cstdlib>
#include <math.h>
#include <iomanip>
using std:: setw;
using namespace std;

//adjust f and fPrime here
double f(double x) {						// define function type, name, args
	return (x*x*x*x - 100*x*x + 1000);		// return f(x)
}

double fPrime(double x) {					// define function type, name, args
	return (100*x*x*x - 200*x);				// return f'(x)
}

//double precision = 1;						// initialize precision

//bool isZero(double x) {					// function for stopping the while loop
//	return fabs(x) < precision;			// returns T/F (true if arg = 0)
//}
// define funct type, name, args
double findRootNewton(double x, double precision) {	

	double f0 = f(x); 							// define f(x) variable
	double x0 = x;								// define x variable

	int count = 0;								// initialize counter

	while (!(fabs(f0) < precision)){				   // loop runs until |f(x)| < precision
		double fp = fPrime(x0);				// define f'(x) variable 
		if (fabs(fp) > 1e-10) {				// iterate to find x1
			x0 = x0 - f0/fp;					// Newton-Rahpson formula
			f0 = f(x0);							// new approximation of f(x)
			//cout << "f(x_0): " << f0 <<  endl;  	// print f(x) (each iter)
			//cout << "x_n: " << x0 << endl;		// print root (each iter)
			count += 1;							// add 1 to iteration count
		} else {
			break;								// break loop if |f'(x)| < 1e-10
		}
	}
	cout << setw(40) << "Estimated root r: " << x0 << endl;		  // return final root (x_n)	 
	cout << setw(40) << "Value of f(r): " << f0 << endl;		  // print final funct value
	cout << "Iterations: "<< endl;		  // print total iterations
	return count;				
}

// define funct type, name, args
double findRootSecant(double x, double precision){

	double x0 = x;									// define starting point
	double x1 = x + 0.25;							// define 2nd starting point
	double f0 = f(x0);								// define f(start)
	double f1 = f(x1);								// define f(2nd start)
	int count = 0;									// initialize counter

	while (!(fabs(f0) < precision)){				   // loop runs until |f(x)| < precision
		double df = f0 - f1;						// define change in f(x)
		double dx = x0 - x1;						// define change in x
		if (fabs(df) > 1e-10) {						// iterate to find x1
			double x = x1 - f1 * (dx / df);			// Secant formula

			f0 = f1;								// update new f(start)
			x0 = x1;								// update new starting point
			x1 = x;									// update 2nd starting point
			f1 = f(x1);								// update new f(2nd start)
/*
			cout << "f(x_0): " << f0 <<  endl;  	// print f(x) (each iter)
            cout << "x_n: " << x0 << endl;			// print (x) (each iter)
*/
			count += 1;								// add 1 to iteration count

		} else {
			break;								// break loop if |f'(x)| < 1e-10
		}
	}
	cout << setw(40) << "Estimated root r: " << x0 << endl;		  // return final root (x_n)	 
	cout << setw(40) <<"Value of f(r): " << f0 << endl;		  // print final funct value
	cout << "Iterations: " << endl;		  // print total iterations
	return count;				
}

// define funct type, name, args
double findRootBisection(double x, double precision) {

    double f0 = f(x);								// define f(x)
    double x0 = x;									// define 1st starting point
    double x1neg = -11;
    double x1pos = 9.5;	
    double x1 = 0;							// define 2nd starting point
    int count = 0;										// initialize counter

    if (f0 > 0) {								   // switch x0, x1 if f(x0) > 0
        x0 = x1pos;
        x1 = x;
    } else {
    	x0 = x;
    	x1 = x1neg;
    }
    
    double f2 = 1;									// initialize f(midpoint)
    double x2 = 0;									// initialize midpoint
    
    while (!(fabs(f2) < precision)) {				   // loop runs until |f(x)| < precision
        x2 = 0.5 * (x0 + x1);						// calculate midpoint
        f2 = f(x2);									// calculate f(midpoint)
       // cout << "f2: " << f2 <<  endl;  			// print f(mid) (each iter)
        //cout << "x2: " << x2 << endl;				// print x_mid (each iter)
        if (f2 < 0) {					 // update new to x0 if func is neg here
            x0 = x2;
        } else {
            x1 = x2;					 // update new to x1 if func is pos here
        }
       /* cout << "\n\nwhile?: " << (isZero(f0)) << endl;
		cout << "\nprecision: " << precision << endl;
		
		cout << "\nf(x0): " << f0 <<  endl;  	// print f(x) (each iter)
		cout << "\nx0: " << x0 << endl;		// print root (each iter)
//cout << "\nf(x1): " << f1 <<  endl;  	// print f(x) (each iter)
		cout << "\nx1: " << x1 << endl;		// print root (each iter)
        cout << "\nf(x2): " << f2 <<  endl;  	// print f(x) (each iter)
		cout << "\nx2: " << x2 << endl;		// print root (each iter)
*/
        count += 1;									// add 1 to iteration count
    }
    cout << setw(40) << "Estimated root r: " << x2 << endl;		  // return final root (x_n)	 
	cout << setw(40) << "Value of f(r): " << f2 << endl;		  // print final funct value
	cout << "Iterations: " << endl;		  // print total iterations
	return count;				
}
// function to call each root method
int main() {
    double precision = 1e-10;
	cout << "With precision: " << precision << endl;
	cout << "===================== Newton: =========================\n" << endl;
	cout << "Starting at (-12,0)...\n\n" << findRootNewton(-12, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (3.2,0)...\n\n" << findRootNewton(3.2, precision) << endl;
    cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (-9.5,0)...\n\n" << findRootNewton(-9.5, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (8,0)...\n\n\n\n" << findRootNewton(8, precision) << endl;

	
	cout << "\n\n\n===================== Secant: =========================\n" << endl;
	cout << "Starting at (-12,0)...\n\n" << findRootSecant(-12, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (3.2,0)...\n\n" << findRootSecant(3.2, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (-9.5,0)...\n\n" << findRootSecant(-9.5, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (8,0)...\n" << findRootSecant(8, precision) << endl;
	
	
	cout << "\n\n\n==================== Bisection: ========================\n" << endl;
	cout << "Starting at (-12,0)...\n\n" << findRootBisection(-12, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (3.2,0)...\n\n" << findRootBisection(3.2, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (-9.5,0)...\n\n" << findRootBisection(-9.5, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (8,0)...\n" << findRootBisection(8, precision) << endl;
	
	return 0;
}

