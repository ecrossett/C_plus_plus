#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

class Bond {
	double principal;
    double coupon;
    double timeToMaturity;

public:
	// constructor
	Bond(double principal,
		 double coupon,
		 double timeToMaturity) 
	{
		// Store input values
		this->principal = principal;
		this->coupon = coupon;
		this->timeToMaturity = timeToMaturity;
	}


	// add method
	double getPrice(double YTM) {
		//double principal = 1000;
        //double coupon = 100;
        //double YTM = 0.07;
        
		double price = 0;
		//double timeToMaturity = 5.0;
    	int T1(timeToMaturity);
    	if (timeToMaturity == T1) {
    	    T1 = T1 - 1;
    	}
		// an empty vector
		vector<double> T;		
		//cout << timeToMaturity << endl;
		//cout << T << endl;
		
	//	create vector of times in ascending order
	//	for(int i = T1 + 1; i > 0; i--){
	//    	T.push_back(timeToMaturity + 1 - i);
	//	}
		// create vector of time in descending order
		for(int i = 0; i <= T1; i++) {
		    T.push_back(timeToMaturity - i);
	    	
		}	
		for(int i = 0; i <= T1; i++){
			price += (coupon / pow((1 + YTM),T[i])); 
			//price += (coupon * exp(-YTM*T[i]));
			
			//cout << price << endl;
			
		}
	    price += (principal / (pow((1 + YTM),timeToMaturity)));
	    //price += (principal * exp(-YTM*timeToMaturity));
	    
		/*/ Toggle DEBUG
		for(int i = 0; i <= T1; i++) {
		
			cout << ' ' << T[i];
		}	
		cout << endl;
		cout << price << endl;
		//*/

		return price;
	}

	double YTM;
	double price;
	double f(double YTM) { return (this->price - getPrice(YTM)); }
	
	double getYTM(const double& price) {
		this->price = price;

		// define funct type, name, args
	
	double precision = .0001;
	double x0 = YTM; //x;						// define starting point
	double x1 = YTM + 0.05;					// define 2nd starting point
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
	cout << "Estimated YTM: " << x0 << endl;
	cout << "Value of f(YTM): " << f0 << endl;
	cout << "Iterations: "<< count << endl;
	return x0;	

	}


	double estimateModifiedDuration(double YTM) {

		double md = 100 * (getPrice(YTM) - getPrice(YTM + 0.01)) / getPrice(YTM);

		return md;
	}


	double estimateSimulatedPrice(double hazardRate, double r,
									int numSimulations)
	{
		// Initialize price and time vector for bond price simulation
		//double D;
		
		double D = 0;
		double Dsum = 0;
		int count = 0;
		double avgPrice = 0;
	
		//double timeToMaturity = 5.0;
    	int T1(timeToMaturity);
    	if (timeToMaturity == T1) {
    	    T1 = T1 - 1;
    	}
	

		// compute "mean" time: The time at which we expect a 50% probability
		// of default:
		//double T = log(2) / hazardRate;
		//double T = 1 / hazardRate;
		// Create Mersenne Twister pseudo-random number generator seeded by 
		// current time.
		
		mt19937 mt_rand(time(0));
		//mt19937 mt_rand(1234);

		// create a Poisson distribution with parameter T:
		//poisson_distribution<int> dis_poisson(T);

		// create an Exponential distribution with parameter h
		exponential_distribution<double> dis_exp(hazardRate);

		// store result of each of such number in variable D (default time)
		for (int i = 0; i < numSimulations; i++){
			
			D = dis_exp(mt_rand);
			// an empty vector
			vector<double> T;		
			
			Dsum += D;
		    //cout << "D: " << D << endl;
			//cout << "Dsum: " << Dsum << endl;
			    
		        // create vector of time in descending order
		        for(int i = 0; i <= T1; i++) {
		            T.push_back(timeToMaturity - i);
		            //cout << "Ti: " << T[i] << endl;
		        }
			        // calulate present value of bond price:
			        
			        // Remove time values greater than D:
			        T.erase(remove_if(T.begin(),T.end(),[D](const double& x) {
				        return x > D;
			        }), T.end());
			        
			        
		        
		        //cout << "Length T: " << T.size() << endl;
		        double price = 0;
				for(int i = 1; i <= T.size(); i++){
					//price += (coupon / pow((1 + YTM),T[i])); 
					price += (coupon * exp(-r*T[i]));
			
					//cout << price << endl;
				}
	    		//price += (principal / (pow((1 + YTM),timeToMaturity)));
	    		if (D < timeToMaturity) {
	    			price = price;
	    		} else {
	    			price += (principal * exp(-r*timeToMaturity));
	    		}
				/*/ Toggle DEBUG
				for(int i = 0; i <= T.size(); i++) {
		
				cout << ' ' << T[i];
				}	
				cout << endl;
				cout << "Length T: " << T.size() << endl;
				//cout << "T1: " << T1 << endl;
				cout << "price: " << price << endl;
				cout << "D: " << D << endl;
			    
				//*/
				
			avgPrice += price;
			//cout << D << endl;
		}
		cout << "Avg D: " << Dsum / numSimulations << endl;
		return avgPrice / numSimulations;	
			
			
			

			//cout << "Normally Distributed Stock Returns:\n" << endl;
			//cout << s << endl;
			//cout << "Lognormally Distributed Stock Prices at t = 1:\n" << endl;
			//cout << s1 << endl;
			
		
	}

};


int main()
{
	ofstream myfile;
	myfile.open("Assignment4Q1.txt");
	myfile << "bond,principal,coupon,timeToMaturity,price,ytm,modifiedDuration" << endl;

	{

		double principal = 1000;
		double coupon = 60;
		double timeToMaturity = 10;

		Bond b(principal, coupon, timeToMaturity);
		double P = b.getPrice(0.05);
		double YTM = b.getYTM(1007.0);
		double md = b.estimateModifiedDuration(0.06);

		myfile << "1," << principal << "," << coupon << "," << timeToMaturity << "," << P << "," << YTM << "," << md << endl;
	}

	{

		double principal = 100;
		double coupon = 7;
		double timeToMaturity = 5.15;

		Bond b(principal, coupon, timeToMaturity);
		double P = b.getPrice(0.05);
		double YTM = b.getYTM(98.5);
		double md = b.estimateModifiedDuration(0.05);

		myfile << "2," << principal << "," << coupon << "," << timeToMaturity << "," << P << "," << YTM << "," << md << endl;
	}


	{

		double principal = 100;
		double coupon = 10;
		double timeToMaturity = 7.65;

		Bond b(principal, coupon, timeToMaturity);
		double P = b.getPrice(0.08);
		double YTM = b.getYTM(104.0);
		double md = b.estimateModifiedDuration(0.1);

		myfile << "3," << principal << "," << coupon << "," << timeToMaturity << "," << P << "," << YTM << "," << md << endl;
	}

	myfile << endl << endl;


	{
		double principal = 100;
		double coupon = 6.2;
		double timeToMaturity = 15.23;
		double hazardRate = 0.05;
		double riskFreeRate = 0.01;

		Bond b(principal, coupon, timeToMaturity);

		int numSimulations = 100;
		double simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;


		numSimulations = 1000;
		simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;


		numSimulations = 10000;
		simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;

		numSimulations = 100000;
		simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;

		numSimulations = 1000000;
		simulatedPrice = b.estimateSimulatedPrice(hazardRate, riskFreeRate, numSimulations);
		myfile << "simulated price after " << numSimulations << " simulations: " << simulatedPrice << endl;
	}

	myfile.close();

	return 0;
}
