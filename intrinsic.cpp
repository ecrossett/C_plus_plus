#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
using std::setw;

// This program performs four main tasks:
//		i) Takes a user input for a spot and strike value and returns the
// 			intrinsic value of the call and put, respectively.  
//		ii) Runs a loop to calculate the intrinsic values for a 100 call 
//			and put for a range of spot prices from 75 to 125. 
//		iii) Runs a loop to calculate the intrinsic values for a 111 call 
//			 and put for a range of spot prices from 75 to 125. 
//		iv) Performs the following conditional execution:
//			a) ask user for input 0 or 1
//			b) if 0: ask for spot price to return intrinsic value of a 100 put
//			c) if 1: ask for strike price to return intrinsic value of a 63.50
//				call.

//Define function to compute Call intrinsic value {max(S - K),0}
double calcCallExerciseValue(double spot, double strike)
{	
	if (spot < strike){
		// Print intrinsic value of put, conditional on formula above.
		  return 0.;//cout << "The intrinsic value of the " << strike << " call is: " <<
			//0 << endl;
	} else {
		
		 return spot - strike;//cout << "The intrinsic value of the " << strike << " call is: " <<
			//spot - strike << endl;
	}
	

}
//Define function to compute Call intrinsic value {max(K-S),0}
double calcPutExerciseValue(double spot, double strike)
{	// Print intrinsic value of put, conditional on formula above.
	if (spot > strike){
		
		  return 0.;//cout << "The intrinsic value of the " << strike << " put is: " <<
			//0 << "\n" << endl;
	} else {
		
		 return strike - spot;//cout << "The intrinsic value of the " << strike << " put is: " <<
			//strike - spot << "\n" << endl;
	}
	
}
// Define main function to run parts i to iv described above.
int main()								
// =========================== PART I ==========================================
{	//initialize variables
	double spot, strike;
	cout << "Enter spot price: ";		// promt user to enter spot
	cin >> spot;						// assign input to spot variable

	cout << "Enter strike price: ";		// promt user to enter strike
	cin >> strike;						// assign input to strike variable

	calcCallExerciseValue(spot, strike);	// call fct for Call intrinsic calc
	calcPutExerciseValue(spot, strike);		// call fct for Put intrinsic calc
	
// =========================== PART II =========================================
	spot = 0;
	strike = 100;							// initialize strike
	int i = 0;
	double x[] = {};
	double call[] = {};
	double put[] = {};
	
	cout << "element" << setw(13) << "spot" << setw(13) << "call" << setw(13) << "put" << endl;
	//for(i = 0; i < 51; i++){
		for (spot = 75; spot < 126; spot++){	// loop through spot vals
			//cout << "Spot: " << spot << endl;	// print each spot value
			//calcCallExerciseValue(spot,strike);	// calc Call intrinsic for each val
			//calcPutExerciseValue(spot,strike);	// calc Put intrinsic for each val
			
			x[i] =  spot;
			//cout << i << endl;
			//cout << x[i] << endl;
			call[i] =  calcCallExerciseValue(spot,strike);
			//cout << call[i] << endl;
			put[i] =  calcPutExerciseValue(spot,strike);
			//cout << put[i] << endl;
			cout << setw(7)<< i << setw(13) << x[i] << setw(13) << call[i] << setw(13) << put[i] <<endl;
			i += 1;	
		}
		
	
	
	//*
		
		//for (int j = 0; j < 51; j++){
			
		//cout << setw(7) << j << call[j] << endl;
		//cout << setw(7) << j << put[j] << endl;
	//*/
	
		
	//}//return x;


	
// =========================== PART III ========================================	
	strike = 111;							// initialize strike
	
	for (spot = 75; spot < 126; spot++){	// loop through spot vals
		cout << "Spot: " << spot << endl;	// print each spot value
		calcCallExerciseValue(spot,strike);	// calc Call intrinsic for each val
		calcPutExerciseValue(spot,strike);	// calc Put intrinsic for each val
	}
// =========================== PART IV =========================================
	int choose;								// initialize variable
	//double do/while loop to check inputs
	do{
		do{		// User input 0 or 1
			cout << "Enter 0 or 1 (spot or strike) or 3 to quit: " << endl;
			cin >> choose;
			// Return error and clear input if non-integer value input		
			if(cin.fail()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Error: Must enter 0, 1, or 3!  Try again..." << endl;
				break;
			// If 0: prompt to enter a spot price, store value, call Put
			// function to calculate intrinsic value
			} else if (choose == 0) {
					cout << "Enter a spot price for 100 put: " << endl;
					cin >> spot;
					strike = 100;
					calcPutExerciseValue(spot,strike);
			// If 1: prompt to enter a strike price, store value, call Call
			// function to calculate intrinsic value
			} else if (choose == 1) {
				cout << "Enter a call strike price for 63.50 spot: " << endl;
				cin >> strike;
				spot = 63.50;
				calcCallExerciseValue(spot,strike);
			// If 3: quit program	
			} else if (choose == 3){
				return 0;
			// Otherwise: return error message
			}else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Error: Must enter 0, 1, or 3.  Try again..." << endl;
				cin >> choose;
			}
		}while(choose !=3);
	}while(cin.fail() || choose !=3);

}
