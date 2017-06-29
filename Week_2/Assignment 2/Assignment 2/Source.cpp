// PHYS 30762 Programming in C++
// Assignment 2 
//	06.02.2017

// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include <string>
#include <ctype.h>
#include <algorithm>
#include<istream>
#include <stdlib.h>     // need for strtod function


using namespace std;

// Declear functions to compute mean and standard deviation
double Mean_function(double array[], int size );
double Std_function(double array[], double mean , int size);

// Main function
int main()
{
	// declear variables here


	// Ask user to enter number of data points - determin the number of points

	// Ask user to enter filename

	// Open file and check if successful
	fstream myfile;
	myfile.open("millika8.txt"); // file name which we will open
	if (!myfile.good()){
		// if the file is not good error message
		cout << "Error: The file could not open correctly, file is not good." << endl;
		return(0); // exit (returning nothing) if the file doesnt open properly
	}
	else { // file sussesfully opens so lets get the data out!

		// Find out how many lines are in the file!
		int line_number{ 0 }; // initiate a variable 
		string line; // line variable to hold string that is each line in file
		while (!myfile.eof()) {     //if not at end of file so continue reading numbers
			getline(myfile, line);
			line_number++;
		}
		cout << "Number of lines in file is " << line_number << " .\n" << endl;

		// Allocate memory for data 
		double * charge_data; // pointer to the charge data for electron. Pointer must be a double as charge_data is a double.
		charge_data = new double[line_number]; // charge_data now points to an array of size line_number.

		// Read data from file, ignoring any additional bad data
		myfile.clear(); // clear the end of file marker ( and other things)
		myfile.seekg(0, ios::beg); // seek the beguining of the file
		int i{ 0 };
		int number_of_errors{ 0 };
		while (!myfile.eof()) {     //if not at end of file so continue reading numbers			
			//getline(myfile, line);
			myfile >> line;

			remove_if(line.begin(), line.end(), isspace); // remove spaces from string so first charactor can be assigned
			line.erase(remove(line.begin(), line.end(), '\n'), line.end()); // remove new line from string

			char character = line.at(0);
			cout << "Character checked by isdigit function = '" << character << "'" << endl;

			if (isdigit(character)){
				// if the line is made of digits add to the array and put array number to next point along
				*(charge_data + i) = strtod(line.c_str(), NULL); // read data into the array pointer converting from string to character array then to double
				cout << i << "	" << *(charge_data + i) << "\n" << endl;    //print number to screen of each element in array as its assigned
				i++; // next element please!
			}
			else { // if there is an error in the line the print the line number, and do not add to the array
				cout << "Error found in line: " << (i) << endl;
				number_of_errors++;
				myfile.ignore(10000, '\n'); // ignore falty line until \n

			}

		}
		int Max_element_number = i ; // The element number of doubles in the array 
		cout << "Max element number = " << Max_element_number << endl;
		cout << "Number of errors = " << number_of_errors << endl;
		

		// Compute mean
		double mean = Mean_function(charge_data, Max_element_number);
		cout << "Mean = " << mean << endl;
		// Compute standard deviation
		double std = Std_function(charge_data, mean, Max_element_number);
		cout << "std = " << std << endl;
		// compute standard error on mean 
		double std_error = mean / sqrt(Max_element_number);
		cout << "Standard error = " << std_error << endl;


		// Compute standard error of mean

		// Free memory
		delete[] charge_data;

	}
	// Close file
	myfile.close();

	if (!myfile.is_open()) {
		cout << "File closed sucessfully." << endl;
	}
	else {
		cout << "Error: The file has not been closed properly." << endl;
	}

	char terminate_comand;
	cout << "Enter any charactor to exit." << endl;
	cin >> terminate_comand;
	return 0;
}

// functions!
// function to compute mean
double Mean_function(double array[], int size ){
	double sum{ 0 };
	double mean;
	
	cout << "size of array = " << size << endl;
	for (int i = 0; i < (size ); i++) // loop untill size of array is meet
	{
		sum = sum + array[i];
	}
	mean = sum / (size) ;
	return mean;
}
// function to compute standard deviation (std)
double Std_function(double array[], double mean, int size ){
	double sum{ 0 };
	double std; // standard deviation
	for (int i = 0; i < size; i++) // loop untill size of array is meet
	{
		sum = sum + pow((array[i] - mean), 2);
	}
	std = sqrt(sum / (size - 1));
	return std;
}