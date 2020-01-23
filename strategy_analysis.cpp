#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <ctime>    // can seed with current time using time(0)
using namespace std;


class StrategyAnalyzer {
public:
    // properties
    int numSimulations;
    double mu;
    double sigma;
    double r;
    double K_call;
    double P_call;
    double K_put;
    double P_put;
    
    double* BuyAndHold;
    double* Buy_Write;
    double* Put_Write;
    
    // add constructor to store properties
    StrategyAnalyzer(int a, double b, double c, double d,
                     double e, double f, double g, double h) {
        numSimulations = a;
        mu = b;
        sigma = c;
        r = d;
        K_call = e;
        P_call = f;
        K_put = g;
        P_put = f;
        
        // method to create arrays
        BuyAndHold = new double[numSimulations];
        Buy_Write = new double[numSimulations];
        Put_Write = new double[numSimulations];
    
    
    //====================== SIMULATE STOCK RETURNS ================================

    // constructor to calculate s (stock returns)
    //StrategyAnalyzer() {
        // properties
        double s0 = 100;
        double Z;
        double s;
        double s1;

        
        // Buy and Hold Initializations
        //double BuyAndHold[numSimulations];
        double V = 0;
        
        // Buy-Write Initializations
        //double Buy_Write[numSimulations];
        double vc1 = 0;
        double vc2 = 0;
        double Vc = 0;
        
        // Put-Write Initializations
        //double Put_Write[numSimulations];
        double vp1 = 0;
        double vp2 = 0;
        double Vp = 0;
        
        // Create Mersenne Twister pseudo-random number generator seeded by
        // current time.
        
        //mt19937 mt_rand(time(0));
        mt19937 mt_rand(1234);
        
        // create a Gaussian normal distribution with mu, sigma;
        normal_distribution<double> dis_normal(0.0,1.0);
        
        // store result of each of such number in variable Z
        for (int i = 0; i < numSimulations; i++){
            Z = dis_normal(mt_rand);
            
            // calulate value of s (stock return)
            s = (mu - 0.5*sigma*sigma) + sigma*Z;
            
            // calculate value of s1 (stock price at time 1yr)
            s1 = s0*exp(s);
            
            //cout << "Normally Distributed Stock Returns:\n" << endl;
            //cout << s << endl;
            //cout << "Lognormally Distributed Stock Prices at t = 1:\n" << endl;
            //cout << s1 << endl;
            //return s1;
        //}
    //}
    //==================== CALCULATE STRATEGY RETURNS ==============================
    // constructor
    //StrategyAnalyzer() {
        

        
            // Buy and Hold Strategy Return Calculation
            V = (s1 - s0) / s0;                    // percentage return
            
            BuyAndHold[i] = V;                    // populate return in array
            
            // Buy-Write Strategy Return Calculation
            
            // Value of call
            if (s1 > K_call) {
                vc2 = s1 - K_call;
            } else {
                vc2 = 0;
            }
            vc1 = (1+r)*P_call + s1;            // value of premium and stock
            Vc = vc1 - vc2;                        // value of above minus call
            Vc = (Vc - (P_call + s0)) / (P_call + s0);    // final return value
            
            Buy_Write[i] = Vc;                    // populate return in array
            
            // Put-Write Strategy Return Calculation
            
            // Value of put
            if (K_put > s1) {
                vp2 = K_put - s1;
            } else {
                vp2 = 0;
            }
            vp1 = (1+r)*(P_put + s0);            // value of premium and stock
            Vp = vp1 - vp2;                        // value of above minus put
            Vp = (Vp - (P_put + s0)) / (P_put + s0);    // final return value
            
            Put_Write[i] = Vp;                    // populate return in array
        }

    }
/*/============= Toggle output to console ======================================
     
     cout << "\n\nBuy and Hold Returns\n" << endl;
     for (int j = 0; j < numSimulations; j++){
     cout << BuyAndHold[j] << endl;
     }
     
     cout << "\n\nBuy-Write Returns\n" << endl;
     for (int j = 0; j < numSimulations; j++){
     cout << Buy_Write[j] << endl;
     }
     
     cout << "\n\nPut-Write Returns\n" << endl;
     for (int j = 0; j < numSimulations; j++){
     cout << Put_Write[j] << endl;
     }
//*///==========================================================================


    // iii) In StrategyAnalyzer, create a public virtual destructor:

    //virtual ~StrategyAnalyzer() that deallocates the arrays you allocated
    //          in the constructor.

    // deconstructor
    virtual ~StrategyAnalyzer() {
        // clean up
        delete[] BuyAndHold;
        delete[] Buy_Write;
        delete[] Put_Write;
    }

    //================= Write simulation results to a CSV file =====================

    // iv) In StrategyAnalyzer, create a public method:

    // void writeResults(const std::string& fileName)

    //     which writes the simulation results as a CSV file with the following header:

    // BuyAndHold, Buy-Write, Put-Write

    // For example, assume our numSimulations is 100, then writeResults() will
    // create a file with 101 lines: 1 line for the header and 100 lines of
    // simulation results.
    // Refer to the final slides of Lecture 6 for an example of writing a CSV file
    // (with header X,Y,Z).


    // add method
    void writeResults(const std::string& fileName){
        
        // output
        ofstream outfile;
        
        // open the file
        outfile.open("strategy.csv");
        
        // write a header
        outfile << "BuyAndHold,Buy-Write,Put-Write\n";
        
        // write the values to the file
        for (int i = 0; i < numSimulations; i++) {
            double x = BuyAndHold[i];
            double y = Buy_Write[i];
            double z = Put_Write[i];
            outfile << x << "," << y << "," << z << endl;
        }
        
        // close the file
        outfile.close();
        
    }

    // ======================= compute standard deviation ==========================

    class StandardDeviation {
public:
    double sd;
    double xbar;
    double sharpe;
    //double N = numSimulations;
};
    StandardDeviation StdBuyAndHold;
    StandardDeviation StdBuy_Write;
    StandardDeviation StdPut_Write;
    StandardDeviation calcStdDev(double* arr, int arrLen) {
        
        StandardDeviation std;

        // first compute the mean
        for (int i = 0; i < arrLen; i++) {
            std.xbar += arr[i];
        }
        std.xbar = std.xbar / arrLen;
        
        // proceed with sd calc
        for (int i = 0; i < arrLen; i++) {
            std.sd += (arr[i] - std.xbar)*(arr[i] - std.xbar);
        }
        std.sd = sqrt((1/(arrLen-1))*std.sd);
        
        // proceed with sharp calc
        std.sharpe = (std.xbar - r) / std.sd;
        
        return std;
        
    }


    //============ print results for E[X], sd, and sharpe to the console ===========

    //method
    void analyzeReturns() {
        
        // Buy and Hold Results
        cout << "Buy and Hold: \n" << endl;
        cout << "Expected Return: " << StdBuyAndHold.xbar << endl;
        cout << "Volatility (S.D.): " << StdBuyAndHold.sd << endl;
        cout << "Sharpe Ratio: " << (StdBuyAndHold.xbar - r) / StdBuyAndHold.sd << endl;
        cout << "\n-----------------------------------------------------------" << endl;
        // Buy-Write Results
        cout << "Buy-Write: \n" << endl;
        cout << "Expected Return: " << StdBuy_Write.xbar << endl;
        cout << "Volatility (S.D.): " << StdBuy_Write.sd << endl;
        cout << "Sharpe Ratio: " << (StdBuy_Write.xbar - r) / StdBuy_Write.sd << endl;
        cout << "\n-----------------------------------------------------------" << endl;
        // Put-Write Results
        cout << "Put-Write: \n" << endl;
        cout << "Expected Return: " << StdPut_Write.xbar << endl;
        cout << "Volatility (S.D.): " << StdPut_Write.sd << endl;
        cout << "Sharpe Ratio: " << (StdPut_Write.xbar - r) / StdPut_Write.sd << endl;
        
        //return 0;
    }
};


int main()
{
    
    StrategyAnalyzer sa1(10000, 0.076961,
                         0.14842, 0.025,
                         105, 5.32, 105, 7.728);
    sa1.StdBuyAndHold = sa1.calcStdDev(sa1.BuyAndHold, sa1.numSimulations);
    sa1.StdBuy_Write = sa1.calcStdDev(sa1.Buy_Write, sa1.numSimulations);
    sa1.StdPut_Write = sa1.calcStdDev(sa1.Put_Write, sa1.numSimulations);
    sa1.analyzeReturns();
    
    
    StrategyAnalyzer sa2(10000, 0.076961,
                         0.14842, 0.025,
                         105, 5.32, 105, 7.728);
 
    sa2.writeResults("strategy.csv");

}

