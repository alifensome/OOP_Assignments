/*Assignment 4
a class for galaxies
-Write a C++ class for describing galaxies
-A galaxy object should contain the following (private) data
-Hubble type: string or alternatively an enum. Allow for the simplied classification in terms of E0-7, S0, Sa,Sb, Sc, SBa, SBb, SBc and Irr
-Redshift: double z in the range [0,10]
-Total mass: double Mtot in the range [107,1012]M⊙
-A stellar mass fraction: double f∗=M∗/Mtot in the range [0,0.05]
-The class should also contain several member functions (detailed below)
-The main() function should demonstrate use of the class through declaring and using objects
-A mark will be deducted if your program produces any compilation warnings or errors

Core marks (3 marks):
Your class should include
-A default constructor; a parameterized constructor; a destructor; a member function (with definition outside the class) t print out an object’s data (total 1 mark)
-A member function to change the galaxy’s Hubble type
(0.5 mark)
-A member function to return the stellar mass M∗=f∗Mtot 
(0.5 mark)
-Your main() function should demonstrate the use of all of the above. It should use a vector to store at least 2 different objects and use an iterator to access these objects and print their content (1 mark)

Challenge mark (1 mark):
Galaxies contain satellites (e.g. Milky Way has large and small Magellanic Clouds). Modify your class so each galaxy object can have satellites
as follows:
Include a private vector object inside your class to store satellites (which are galaxy objects)
Add a new member function to add a satellite galaxy
Modify your print function to print the number of satellites and, if non-zero, print their properties as well
Again, you must demonstrate their use in your main program.
Assignment total: 4 marks
Negative marks for compilation errors; poor programming style and absense for marking (a maximum of 3!)
Assignment deadline: Friday 3 March at 4:45pm*/

// Example using structures
#include<iostream>
#include<string>
#include<cmath>
#include<vector>

using namespace std;
// Define data structure
class Galaxy
{
private:
	string hubble_type;
	double redshift, total_mass, stellar_mass_fraction, stellar_mass;
	vector<string> satellites; // vector for storing satellites
public:
	// Constructors
	Galaxy() : hubble_type("Defult"), redshift{ 0 }, total_mass{ 0 }, stellar_mass_fraction{ 0 }, stellar_mass{ 0 }, satellites{} {}
	// Parameterized constructor
	Galaxy(string phubble_type, double predshift, double ptotal_mass, double pstellar_mass_fraction) :
		hubble_type(phubble_type), redshift{ predshift }, total_mass{ ptotal_mass }, stellar_mass_fraction{ pstellar_mass_fraction },
		stellar_mass{ (stellar_mass_fraction*total_mass) }, satellites{}
	{}
	// Destructor
	~Galaxy(){ cout << "Destroying " << hubble_type << endl; }

	// Return stellar mass (M_* = f_* x M_tot)
	double Stellar_Mass() { return (stellar_mass_fraction*total_mass); }
	// Change galaxy's Hubble type
	void Change_Hubble_Type(Galaxy& G, string new_hubble_type){
		G.hubble_type = new_hubble_type;
	}
	// declare functions
	void Print_Data(); 
	void Add_Satellite_Galaxy(Galaxy& G);

};

	// function to Add satellite galaxy
	void Galaxy::Add_Satellite_Galaxy(Galaxy& G){
		string satellite; // strore the user input to insert into vector
		const string end_char("x"); // character which if entered terminates do loop
		// Gather list of galaxies from user
		bool not_finished(true);
		do // do...while loop checks its condition at the bottom of the loop.
		{
			cout << "Please type the name of a satellite galaxy and press enter (or x to finish):\n" << endl;
			getline(cin, satellite); // 

			if (satellite.compare(end_char) != 0){ // compare the srings if string = x the will return 0.
				G.satellites.push_back(satellite);
				cout << satellite << " has been saved to vector." << endl;
			}
			else{ // if x is entered break the loop.
				not_finished = false;
				cout << "Finished entering galaxies." << endl;
			}
		} while (not_finished);
	}

// function to print out an object's data. Member of Galaxy but decleared outside of class.
void Galaxy::Print_Data(){
	cout.precision(3); // 2 significant figures
	cout << "Galaxy: [type, Z, M_tot, F_ste, M_ste] \n= [" << hubble_type << "," << redshift
		<< "," << total_mass << "," << stellar_mass_fraction << "," << stellar_mass << "]" << endl;
	cout << "Number of satellites = " << satellites.size() << endl;
	// print out satellites vector 
	for (size_t i = 0; (i < satellites.size()); i++){
		cout << satellites[i] << endl;
	}
	
}

int main()
{
	// initalise a vector to hold class objects
	vector<Galaxy> Galaxy_list;

	// Set values for some galaxies into the class. (Allowed hubble types: E0-7, S0, Sa,Sb, Sc, SBa, SBb, SBc and Irr)
	Galaxy G1("E0-7", 1, 100, 0.1), G2("S0", 2 , 200, 0.2);
	// Pushback data into a vector
	Galaxy_list.push_back(G1);
	Galaxy_list.push_back(G2);

	// print out structure stored in vector using print function 
	for (size_t i = 0; (i < Galaxy_list.size()); i++){
		Galaxy_list[i].Print_Data();
	}

	// Calculate stellar mass using function (even though theyre already calculated automatically)
	cout.precision(2);
	cout << "Galaxy 1 has stellar mass = " << G1.Stellar_Mass() << endl;
	cout << "Galaxy 2 has stellar mass = " << G2.Stellar_Mass() << endl;

	// change hubble type
	G1.Change_Hubble_Type( G1, "I have been changed!");
	G2.Change_Hubble_Type(G2, "I have also been changed!");
	G1.Print_Data(); // print out G1 to show its been changed to what ever string 
	G2.Print_Data();

	// add satellites
	cout << "Add satellites to G1" << endl;
	G1.Add_Satellite_Galaxy(G1); 
	cout << "Add satellites to G2" << endl;
	G2.Add_Satellite_Galaxy(G2); 

	Galaxy_list.clear(); // clear vector to get rid of old values
	Galaxy_list.push_back(G1); // pushback new values with satellites 
	Galaxy_list.push_back(G2);
	// print out structure stored in vector using print function 
	for (size_t i = 0; (i < Galaxy_list.size()); i++){
		Galaxy_list[i].Print_Data();
	}


	// enter any character to exit
	cout << "\nEnter any character to exit." << endl;
	char exit_consol;
	cin >> exit_consol;
	return 0;
}