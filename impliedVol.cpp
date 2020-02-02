//THIS C++ PROGRAM USES NEWTONS METHOD TO FIND THE IMPLIED VOL FOR A GIVEN OPTION PRICE. CAN BE USED TO CALIBRATE BS MODEL PRICE TO MKT PRICE
#define _USE_MATH_DEFINES 
#include <cmath>
#include <iomanip> 
#include <iostream> 
#include <sstream> 
#include <string>

using namespace std;
double cum_dist_normal(double t);
double Call(double S, double K, double r, double q, double vol, double T);
double Vega(double S, double K, double r, double q, double vol, double T);
double Newton(double S, double K, double r, double q, double vol, double T, double C, double tol);

int main() 
//INPUTS FOR CALL PRICE USING BLACK SCHOLES PARAMETERS
    {cout<<Newton(30, 30, 0.03, .01, 0.5, 0.5, 2.50, 0.000001);}
 
//CDF APPROXIMATION
double cum_dist_normal(double t)
{
    double z = abs(t); 
    double nn;
    double y = 1.0 / (1 + 0.2316419 * z); 
    double a1 = 0.319381530, a2 = -0.356563782, a3 = 1.781477937, a4 = -1.821255978, a5 = 1.330274429;
    double m =1 -exp(-t*t*0.5)*(a1 * pow(y,1) + a2*pow(y,2) + a3*pow(y,3) + a4*pow(y,4) + a5*pow(y,5)) / sqrt(2*M_PI);
 
       if (t>0) 
            {nn=m;}
       else (nn=1-m);
       return nn;
}
//CALL PRICE CALCULATION: f(x)
double Call(double S, double K, double r, double q, double vol, double T)
{
    double d1 = (log(S / K) + (r - q + (vol * vol) * 0.5) * T) / (vol * sqrt(T));
    double d2 = (log(S / K) + (r - q - (vol * vol) * 0.5) * T) / (vol * sqrt(T));
    return (S * exp(-q * T) * cum_dist_normal(d1)) - (K * exp(-r * T) * cum_dist_normal(d2));
}

//VEGA CALCULATION: f’(x)
double Vega(double S, double K, double r, double q, double vol, double T)
{
    double d1 = (log(S / K) + (r - q + (vol * vol) * 0.5) * T) / (vol * sqrt(T));
    double d2 = (log(S / K) + (r - q - (vol * vol) * 0.5) * T) / (vol * sqrt(T));
    return 1/(sqrt(2*M_PI))*S*exp(-q*T)*sqrt(T)*exp((-0.5)*d1*d1);
}
 
//NEWTONS METHOD TO FIND IMPLIED VOL 
double Newton(double S, double K, double r, double q, double vol, double T, double C, double tol)
{
       double x0 = vol;
       double x_new, x_old;
            x_new = x0;
            x_old = x0-1;
       int count = 0;
      
       while (abs(x_new-x_old) > tol)
{
        x_old = x_new;
        x_new = x_old - (Call(S, K, r, q, x_new, T) - C ) / Vega(S, K, r, q, x_new, T);
        cout<<"vol "<<count<<":  "<<x_new<<endl;
        count++;
}
       return x_new;
}


