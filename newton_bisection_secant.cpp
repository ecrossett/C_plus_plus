#include <iostream>						
#include <cstdlib>
#include <math.h>
#include <iomanip>
using std:: setw;
using namespace std;


double f(double x) {					// define function type, name, args
	return (x*x*x*x - 181*x*x + 8100);		// return f(x)
}

double fPrime(double x) {				// define function type, name, args
	return (4*x*x*x - 362*x);			// return f'(x)
}


// define funct type, name, args
double findRootNewton(double x, double precision) {	

	double f0 = f(x); 				// define f(x) variable
	double x0 = x;					// define x variable

	int count = 0;					// initialize counter
	// loop runs until |f(x)| < precision
	while (!(fabs(f0) < precision)){				   
		double fp = fPrime(x0);			// define f'(x) variable 
		if (fabs(fp) > 1e-10) {			// iterate to find new x0
			x0 = x0 - f0/fp;		// Newton-Raphson formula
			f0 = f(x0);			// new approximation of f(x)
			
			count += 1;			// add 1 to iteration count
	// break loop if |f'(x)| < 1e-10
		} else {
			break;									
		}
	}
	// return final root (x_n), final value of function, final iteration count
	cout << setw(40) << "Estimated root r: " << x0 << endl;
	cout << setw(40) << "Value of f(r): " << f0 << endl;
	cout << "Iterations: "<< endl;
	return count;				
}

// define funct type, name, args
double findRootSecant(double x, double precision){

	double x0 = x;						// define starting point
	double x1 = x + 0.25;					// define 2nd starting point
	double f0 = f(x0);					// define f(start)
	double f1 = f(x1);					// define f(2nd start)
	
	int count = 0;						// initialize counter
	// loop runs until |f(x)| < precision
	while (!(fabs(f0) < precision)){				   
		double df = f0 - f1;				// define change in f(x)
		double dx = x0 - x1;				// define change in x
		if (fabs(df) > 1e-10) {				// iterate to find x1
			double x = x1 - f1 * (dx / df);		// Secant formula

			f0 = f1;				// update new f(start)
			x0 = x1;				// update new starting point
			x1 = x;					// update 2nd starting point
			f1 = f(x1);				// update new f(2nd start)
			
			count += 1;				// add 1 to iteration count
		// break loop if |f'(x)| < 1e-10
		} else {
			break;								
		}
	}
	// return final root (x_n), final value of function, final iteration count
	cout << setw(40) << "Estimated root r: " << x0 << endl;		   
	cout << setw(40) <<"Value of f(r): " << f0 << endl;		 
	cout << "Iterations: " << endl;		 
	return count;				
}

// define funct type, name, args
double findRootBisection(double x, double precision) {

    double f0 = f(x);						// define f(x)
    double x0 = x;						// define 1st starting point
    double x1neg = -11;						// define 2nd sp (if f neg)
    double x1pos = 9.5;						// define 2nd sp (if f pos)
    double x1 = 0;						// initialize 2nd sp
    double f2 = 1;						// initialize f(midpoint)
    double x2 = 0;						// initialize midpoint

    int count = 0;						// initialize counter
	// switch x0, x1 depending on sign of f(x)
    if (f0 > 0) {								   
        x0 = x1pos;
        x1 = x;
    } else {
    	x0 = x;
    	x1 = x1neg;
    }

    // loop runs until |f(x)| < precision
    while (!(fabs(f2) < precision)) {	   

        x2 = 0.5 * (x0 + x1);					// calculate midpoint
        f2 = f(x2);						// calculate f(midpoint)
        // update new to x0 if func is neg here
        if (f2 < 0) {					 
            x0 = x2;
        // update new to x1 if func is pos here    
        } else {
            x1 = x2;					
        }
        count += 1;						// add 1 to iteration count
    }
    // return final root (x_n), final value of function, final iteration count 
    cout << setw(40) << "Estimated root r: " << x2 << endl;	
	cout << setw(40) << "Value of f(r): " << f2 << endl;		 
	cout << "Iterations: " << endl;		  
	return count;				
}
// function to call each root method and print results
int main() {
    double precision = 1e-6;
    //double precision = 1e-8;
    //double precision = 1e-10;
	cout << "With precision: " << precision << endl;
	cout << "===================== Newton: =========================\n" << endl;
	cout << "Starting at (-12, 0)...\n\n" << findRootNewton(-12, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (3.2, 0)...\n\n" << findRootNewton(3.2, precision) << endl;
    cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (-9.5, 0)...\n\n" << findRootNewton(-9.5, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (8, 0)...\n\n\n\n" << findRootNewton(8, precision) << endl;

	
	cout << "\n\n\n===================== Secant: =========================\n" << endl;
	cout << "Starting at (-12, 0) and (-11.75, 0)...\n\n" << findRootSecant(-12, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (3.2, 0) and (3.45, 0)...\n\n" << findRootSecant(3.2, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (-9.5, 0) and (-9.25, 0)...\n\n" << findRootSecant(-9.5, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (8, 0) and (8.25, 0)...\n" << findRootSecant(8, precision) << endl;
	
	
	cout << "\n\n\n==================== Bisection: ========================\n" << endl;
	cout << "Starting at (-12, 0) and (9.5, 0)...\n\n" << findRootBisection(-12, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (3.2, 0) and (9.5, 0)...\n\n" << findRootBisection(3.2, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (-9.5 0) and (-11, 0)...\n\n" << findRootBisection(-9.5, precision) << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "\nStarting at (8, 0) and (9.5, 0)...\n" << findRootBisection(8, precision) << endl;
	
	return 0;
}

