#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

	double getExerciseValue(double spot, double t, string type) {
		//double intrinsic = 0;
		double T = 1;
		//double spot = 50;
		double strike = 90;
		//string type = "EC";
		
		// European Call
		if (type == "EC") {
		    if (spot > strike && t == T) {
			    return spot - strike;
		    } else {
			    return 0;
		    }
		    //*//
		} else if (type == "EP") {
		// European Put
			if (spot < strike && t == T) {
				return strike - spot;
			} else {
				return 0;
			}
		} else if (type == "AC") {
		// American Call
			if (spot > strike) {
				return spot - strike;
			} else {
				return 0;
			}
		} else if (type == "AP") {
		// American Put
			if (spot < strike) {
				return strike - spot;
			} else {
				return 0;
			}
		} else {
		    return 0;
		}
		
		//cout << "Exercise Value: " << intrinsic << endl;
		//return intrinsic;
		//*///
	}
    
// method to get binomial tree value
	double getBinomialTreeValue(double s, int N, string type) {
		// initialize input parameters
		double strike = 90;
		double sigma = 0.275;
		double r = 0.15;
		double T = 1;
		
		double spot;
		double dt = T / N; 
		double exercise;
		// define magnitude of up move and down move (based on assumed sigma)
		double u = exp(sigma*sqrt(dt));
		double d = exp(-sigma*sqrt(dt));
		// define 'probability' of up move (p) and down move (q)
		double p = (u - exp(-r * dt)) / (u * u - 1);
		double q = exp(-r * dt) - p;

		// initialize vector of length N+1 to store prices at each node in tree
		// for a single time step
		vector<double> Tree;

		// create vector of nodes (N+1)...to be overwritten at each step
		for(int i = 0; i <= N; i++) {
		    Tree.push_back(i);
	    	
		}
		
		// populate vector with intrinsic values (aka: exercise values)
		for(int i = 0; i <= N; i++) {
			// compute vale of spot for each node
			spot = s * pow(u,(2 * i - N));
			Tree[i] = spot;
			// overwrite with exercise value by calling function
			// conditional on option type (ie: EC, EP, AC, AP)
			Tree[i] = getExerciseValue(spot, T, type);
		}
	
		double t = T;
		// move backwards along tree, repeating steps above for each time step 
		// increment
		for (int j = N - 1; j >= 0; j--) {
			t = t - dt;
			for (int i = 0; i <= j; i++) {
				spot = s * pow(u, (2 * i - j));
				exercise = getExerciseValue(spot, t, type);
				// pStar times spot up plus qStar times spot down
				Tree[i] = p * Tree[i + 1] + q * Tree[i];		// binomial value
				// check to see if early exercise makes sense
				// if so, then replace current price with exercise price
				// this will not matter for european options
				if (Tree[i] < exercise) {
					Tree[i] = exercise;
				}
			}
		}
		// return final value
		return Tree[0];
	}


int main() {
   
    double x = getBinomialTreeValue(100, 10000, "EC"); 
      
    cout << x << endl;
    return x;
}
