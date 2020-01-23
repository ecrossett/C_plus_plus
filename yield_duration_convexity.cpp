//THIS C++ PROGRAM USES NEWTONS METHOD TO FIND THE YIELD, DURATION, AND CONVEXITY OF A BOND GIVEN THE BOND PRICE
#define _USE_MATH_DEFINES 
#include <cmath>
#include <iomanip>
#include <iostream> 
#include <sstream> 
#include <string> 

using namespace std;

double f(double t[], double cf[], double y); // B  -  C
double f_d1(double t[], double cf[], double y, double B); //f(x)
double f_d2(double t[], double cf[], double y, double B); //f’(x)
double Newton(double t[], double cf[],double B, double tol);
int main() 
//INPUTS FOR TIME PERIODS, CF PMTS, BOND PRICE, TOLERANCE, AND INITIAL GUESS FOR YIELD
{ 
	double t[] = {0.5,1.0,1.5,2,2.5,3.0};
	double cf[] = {2,2,2,2,2,102}; 
	Newton(t, cf, 101, 0.000001);
	cout<<"Duration: "<<f_d1(t, cf, 0.0361227, 101)<<endl;
	cout<<"Convexity: "<<f_d2(t, cf, 0.0361227, 101)<<endl;
}
//COMPUTE PRICE OF THE BOND
double f(double t[], double cf[], double y)
{
	double sum = 0;
	for (int i = 0; i < 6; i++)
	{sum = sum + cf[i]*exp((-1)*y*t[i]);}
	return sum;
}
//COMPUTE DURATION: f'(x)
double f_d1(double t[], double cf[], double y, double B)
{
	double sum = 0, duration;
	for (int i = 0; i < 6; i++)
	{sum = sum + t[i]*cf[i]*exp((-1)*y*t[i]);}
	duration = sum / B;
	return duration;
}
//COMPUTE CONVEXITY: f''(x)
double f_d2(double t[], double cf[], double y, double B)
{
	double sum = 0, convexity;
	for (int i = 0; i < 6; i++)
	{sum = sum + t[i]*t[i]*cf[i]*exp((-1)*y*t[i]);}
	convexity = sum / B;
	return convexity;
}
//ITERATIONS
double Newton(double t[], double cf[],double B, double tol)
{
	double x0 = 0.1;
	double x_new, x_old;
	x_new = x0;
	x_old =  x0 - 1;
	int count = 0;
	while (abs(x_new-x_old) > tol)
	{
		double sum_f = 0, sum_f_d = 0;
		x_old = x_new;
		x_new = x_old;
		for (int i = 0; i < 6; i++)
		{sum_f = sum_f + cf[i]*exp((-1)*x_old*t[i]);}
		for (int i = 0; i < 6; i++)
		{sum_f_d = sum_f_d + cf[i]*t[i]*exp((-1)*x_old*t[i]);}
		x_new = x_old + (sum_f - B) / sum_f_d;
		cout<<"y"<<count<<": "<<x_new<<endl;
		count++;
	}
	return x_new;
}

