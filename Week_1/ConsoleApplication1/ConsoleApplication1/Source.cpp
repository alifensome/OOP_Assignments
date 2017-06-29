/*			Alastair Fensome 
				9038778
			   30.01.2017

Assignment 1
- Program to calculate transition energy using simple Bohr formula
- Check thay values for Z,n_j,n_i make are positive integers 
- Out put energy in J or eV
*/

#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

// function declaration to compute the energy in eV
double Compute_photon_energy_function(int Z, int n_j, int n_i);

int main() {
	// Declare variables here
	bool reapeat_yn{ true }; // repeat parameter bool variable. Repeat process untill the answer is false.
	double E_eV; // energy 
	double e{ 1.60*pow(10, -19) }; // charge of an electron and hence number of J in 1 eV
	double E_joule; // define energy in joules 
	char response; // variable to contain a Y / N answer for whether to repeat or not
	char units_response; // variable to haold an answer to unit selection in it

	while (reapeat_yn) // repeat this procedure untill the bool is 0 
	{
		// Declear input variables, set all equal to 0 so they fail the first while loop to check for > 1.
		int Z{ 0 }; // atomic mass number 
		int n_j{ 0 }; // n_i,j are energy leves for the transition
		int n_i{ 0 };

		while (Z < 1) // check that z is less than 1 and continue to require input untill greater than 1 obtained. 
		{

			// Ask user to enter atomic number
			cout << "Enter the atomic mass number Z, must be positive integer \n";
			cin >> Z;
			// Check input is valid 
			while (cin.fail())
			{
				cout << "Sorry, your input was not valid, please enter a positive integer \n";
				// Clear fail bit and ignore bad input
				cin.clear(); cin.ignore(); cin >> Z;
			}
			cout << "The atomic mass number entered is " << Z << endl;
		}

		while (n_i < 1) // check that z is less than 1 and continue to require input untill greater than 1 obtained. 
		{
			// Ask user to enter initial and final quantum numbers
			cout << "Enter the initial quantum number \n";
			cin >> n_i;
			// Check input is valid 
			while (cin.fail())
			{
				cout << "Sorry, your input was not valid, please enter a positive integer initaial quantum number \n";
				// Clear fail bit and ignore bad input
				cin.clear(); cin.ignore(); cin >> n_i;
			}
			cout << "Your initial quantum number is " << n_i << endl;
		}

		while (n_j < 1) // check that z is less than 1 and continue to require input untill greater than 1 obtained. 
		{
			// ask for a final quantim number n_j
			cout << "Enter the final quantum number \n";
			cin >> n_j;
			// Check input is valid 
			while (cin.fail())
			{
				cout << "Sorry, your input was not valid, please enter a positive integer for your final quantum number \n";
				// Clear fail bit and ignore bad input
				cin.clear(); cin.ignore(); cin >> n_j;
			}
			cout << "Your final quantum number is " << n_j << endl;
		}

		// Compute photon energy, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
		// calling energy function to get energy in eV
		(double)E_eV = Compute_photon_energy_function(Z, n_j, n_i);
		E_joule = e*E_eV;

			// Output answer
			cout << "What units would you like your energy in? \nPress J/j for Joules, or any other character for eV \n" << endl;
			cin >> units_response;
			if (!(units_response != 'J' && units_response != 'j'))
			{
				cout << "Energy of photon =	" << E_joule << " J" << endl;
			}
			else
			{
				cout << "Energy of photon =	" << E_eV << " eV" << endl;
			}

			// continue yay or nay section
			cout << "Would you like to contnue? \nPress Y/y to continue or any other character to exit \n" << endl;
			cin >> response;			
			if (!(response != 'Y' && response != 'y'))
			{ 
				reapeat_yn = true;
			}
			else
			{ 
				reapeat_yn = false;
			}		

	}

	return 0;
}


// function to Compute photon energy, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
double Compute_photon_energy_function(int Z, int n_j, int n_i)  {
	// local variable declaration E for energy
	double E;
	E = (13.6*pow(Z, 2)*((1 / pow((double)n_j, 2)) - (1 / pow((double)n_i, 2))));
	return (double)E;
}