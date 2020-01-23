#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;


class Option {

protected:

	// define input parameters
	double strike;
	double T;
	double sigma;
	double riskFreeRate;

public:

	// constructor
	Option(double strike,
		 double T,
		 double sigma,
		 double riskFreeRate)  
	{
		// Store input values
		this->strike = strike;
		this->T = T;
		this->sigma = sigma
		this->riskFreeRate = riskFreeRate;
	}

	// method to get exercise value
	virtual double getExerciseValue(double spot, double t, string type) {
		double T = 0.5;
		double strike = 55;
		
		
		// European Call
		if (type == "EC") {
		    if (spot > strike && t == T) {
			    return spot - strike;
		    } else {
			    return 0;
		    }
		    
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
	}
    

	// method to get B-S value
	virtual double getBlackScholesValue(double s) {
		// initialize input parameters
		double spot = 100;
        double strike = 90;
        double riskFreeRate = 0.15;
        double sigma = 0.275;
        double T = 1;
        double t = 0;
        double dt = T - t;
        double r = riskFreeRate;
        
		double bsCall;
		double bsPut;
		double q = 0; 
		
		// calculate values for d1, d2, -d1, -d2
		double d1 = (log(s / strike) + (r - q + (sigma * sigma * 0.5)) * dt) / (sigma * sqrt(dt));
		double d2 = (log(s / strike) + (r - q - (sigma * sigma * 0.5)) * dt) / (sigma * sqrt(dt));
		double d1_ = (log(strike / s) - (r - q + (sigma * sigma * 0.5)) * dt) / (sigma * sqrt(dt));
		double d2_ = (log(strike / s) - (r - q - (sigma * sigma * 0.5)) * dt) / (sigma * sqrt(dt));
		
		// compute Gaussian (Normal) CDF
		double N_d1 = erfc(-d1 / sqrt(2)) / 2;
		double N_d2 = erfc(-d2 / sqrt(2)) / 2;
		double N_d1_ = erfc(-d1_ / sqrt(2)) / 2;
		double N_d2_ = erfc(-d2_ / sqrt(2)) / 2;

		// BS Call Price assuming no dividends (ie: q = 0)
		bsCall = s * exp(-q * dt) * N_d1 - strike * exp(-r * dt) * N_d2;

		// BS Put Price assuming no dividends
		bsPut = strike * exp(-r * dt) * N_d2_ - s * exp(-q * dt) * N_d1_;

		cout << "Black-Scholes Value (Call): " << bsCall << endl;
		cout << "Black-Scholes Value (Put): " << bsPut << endl;
//*/
		if (type == EuropeanCall || type == AmericanCall) {
			return bsCall;
		} else if (type == EuropeanPut || type == AmericanPut) {
			return bsPut;
		} else {
			return 0;
		}

	}
//*///
    
}
	// method to get binomial tree value
	double getBinomialTreeValue(double s, int N) {
		// initialize input parameters
		double strike = 55;
		double sigma = 0.30;
		double r = 0.10;
		double T = 0.5;
		
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

	// method to return option value
	virtual double getValue(double s) {
		EuropeanCall.getBlackScholesValue(double s)
		AmericanCall.getBinomialTreeValue(double s)
		EuropeanPut.getBlackScholesValue(double s)
		AmericanPut.getBinomialTreeValue(double s)
		return 0;

};

class European: public Option {
	double strike;
	double T;
	double sigma;
	double riskFreeRate;

};

class EuropeanPut: public European {

	double strike;
	double T;
	double sigma;
	double riskFreeRate;

	virtual getValue(spot) {
		return 0;
	}

	virtual getBlackScholesValue(spot) {
		return bsPut;
	}

	virtual getBinomialTreeValue(spot, N) {
		return Tree[0];
	}

	
};

class EuropeanCall: public European {
	double strike;
	double T;
	double sigma;
	double riskFreeRate;

	virtual getValue(spot) {
		return 0;
	}

	virtual getBlackScholesValue(spot) {
		return bsCall;
	}

	virtual getBinomialTreeValue(spot, N) {
		return Tree[0];
	}


};


class American: public Option {
	double strike;
	double T;
	double sigma;
	double riskFreeRate;

};

class AmericanPut: public American {
	double strike;
	double T;
	double sigma;
	double riskFreeRate;

	virtual getValue(spot) {
		return 0;
	}

	virtual getBlackScholesValue(spot) {
		return bsPut;
	}

	virtual getBinomialTreeValue(spot, N) {
		return Tree[0];
	}


}:

class AmericanCall: public American {
	double strike;
	double T;
	double sigma;
	double riskFreeRate;


	virtual getValue(spot) {
		return 0;
	}

	virtual getBlackScholesValue(spot) {
		return bsCall;
	}

	virtual getBinomialTreeValue(spot, N) {
		return Tree[0];
	}

};
