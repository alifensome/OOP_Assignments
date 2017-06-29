/*Assignment 5
-a class for complex numbers
-Write a C++ class to store complex numbers, z = x + iy
-The data for each object should contain two doubles to represent the real and imaginary parts
-Your class should demonstrate usage of operator overloading for arithmetic operations(on complex numbers) and overload the insertion operator to insert complex numbers into an ostream, and an extraction operator from an istream
-The latst twp functions should be friends of the class
-The main program should demonstrate use of the class through declaring and using objects(or reading them from input!); for simplicity, please use a = 3 + 4i and b = 1−2i in all your tests.
-You should modify function parameters with const wherever appropriate
-Assignment deadline : Friday 10th March at 4 : 45pm

class must contain :
-Four member functions, each returning real part, imaginary part, modulus and argument[0.5 mark]
-Member function to return complex conjugate[0.5 marks]
-Functions that overload the + and - operators to perform addition and subtraction of 2 complex numbers[0.5 marks]
-Functions that overload the * and / operators to perform multiplication and division of 2 complex numbers[0.5 marks]
-Consistent use of const modifier in function declarations for two purposes : 1 - prevent parameters being modified; 
	2 - prevent member data being modified[1 marks]
-A non - member function to allow insertion of complex objects into an ostream
(must be a friend of the class and output should be appropriately formatted to handle complex numbers with negative imaginary parts)[0.5 marks]
-[Challenge] A non - member function to allow extraction of complex objects from an istream
(must be a friend of the class and should be able to handle complex numbers of the form a + ib and a−ib.Assume a and b to be specified even if zero)[0.5 marks]

you lose marks if :
-The code generates error messages on compilation[-1 mark]
-The code layout, presentation, comments, variable names are insufficient.[-1 marks]
-The code doesnot adequately demonstrate the use and implementation of the class[-1 marks]
-You don’t attend for feedback[-1 mark]
*/

// PHYS 30762 Programming in C++
// Assignment 5 - skeleton code

// Class for complex numbers
#include<iostream>
#include<cmath>
#include<string>
#include <sstream>      // std::stringstream
#include<vector>
//#include<stdafx.h>

using namespace std;

class complex
{
	// Make function to overload operator<< a friend
	friend ostream & operator<<(ostream &os, const complex &C);

private:
	double re, im;
public:
	// Constructors & destructor
	complex(){ re = im = 0; }
	complex(double r, double i){ re = r; im = i; }
	~complex(){ }

	// declear freind function for extracting numbers from iostream
	friend vector<double> Extract_Complex();

	// Access functions to get complex components
	double Get_Real() const { return re; } // Return real component
	double Get_Imaginary() const { return im; } // Return imaginary component
	// Function to print out the complex number
	void   Print() const { cout << "Complex number = (" << re << " + " << im << "*i)" << endl; }
	// Return the modulus of the complex number
	double Modulus(const complex &C) const // Return modulus
	{
		return (sqrt(pow(C.re,2) + pow(C.im,2) ));
	}
	// Return the argument of the complex number Argument = arctan(im/re)
	double Argument(const complex &C) const // Return argument
	{
		return (atan(C.im/C.re));
	}
	// Return complex conjugate
	double Conjugate(const complex &C) const // Return argument
	{
		double temp_im;
		temp_im = -C.im;
		if (temp_im >= 0){
			cout << "(" << C.re << " + " << temp_im << "i)" << endl;
		}
		if (temp_im < 0){
			cout << "(" << C.re << " " << temp_im << "i)" << endl;
		}
		return (re , -im );	 
	}
	// Function to overload + operator (addition of complex and imaginary parts separtely)
	complex operator+(const complex &C) const
	{
		complex temp(re + C.Get_Real(), im + C.Get_Imaginary());
		return temp;
	}
	// Another one for (right) adding a scalar
	complex operator+(const double scalar) const
	{
		complex temp(re + scalar, im );
		return temp;
	}
	void operator+=(const double scalar)
	{
		re += scalar; im ;
	}
	void operator+=(const complex &C)
	{
		re += C.re; im += C.im ;
	}


	// Overload - operator for subtraction
	complex operator-(const complex &C) const
	{
		complex temp(re - C.Get_Real(), im - C.Get_Imaginary());
		return temp;
	}
	// Another one for (right) adding a scalar
	complex operator-(const double scalar) const
	{
		complex temp(re - scalar, im );
		return temp;
	}
	void operator-=(const double scalar)
	{
		re -= scalar; im ;
	}
	void operator-=(const complex &C)
	{
		re -= C.re; im -= C.im;
	}

	// Overload * operator for multiplication, z1*z2
	complex operator*(const complex &C) const
	{
		complex temp(re*C.Get_Real() - im*C.Get_Imaginary(), re*C.Get_Imaginary() + im*C.Get_Real());
		return temp;
	}
	// Another one for (right) adding a scalar
	complex operator*(const double scalar) const
	{
		complex temp(re*scalar, im*scalar);
		return temp;
	}

	// Overload / operator for division, z1/z2
	complex operator/(const complex &C) const
	{
		complex temp((re*C.Get_Real() + im*C.Get_Imaginary()) / (pow(C.re, 2) + pow(C.im, 2)), (im*C.Get_Real() - re*C.Get_Imaginary()) / (pow(C.re, 2) + pow(C.im, 2)));
		return temp;
	}
	// Another one for (right) adding a scalar
	complex operator/(const double scalar) const
	{
		complex temp(re/scalar, im/scalar);
		return temp;
	}


};

// Non-member function to overload ostream (e.g., cout) for vector3
ostream & operator<<(ostream &os, const complex &C)// Function to overload << operator for complex numbers
{
	if (C.im >= 0){
		os << "(" << C.re << " + " << C.im << "i)" << endl;
	}
	if (C.im < 0){
		os << "(" << C.re << " " << C.im << "i)" << endl;
	}
	return os;
}

//  non-member function to allow extraction of complex objects from an istream 
vector<double> Extract_Complex(){
	string input;
	vector<double> re_im_vec;// vector to hold the real and imaginary parts
	cout << "Please enter a complex number in the form a+ib or a−ib " << endl;
	getline(cin, input);
	stringstream ss{ input };
	double re, im;
	ss >> re >> im;
	cout << "re = " << re << endl;
	cout << "im = " << im << endl;
	re_im_vec.push_back(re);
	re_im_vec.push_back(im);
	return re_im_vec;
}

int main()
{
	cout.precision(3);

	// Create two complex numbers
	complex a(3, 4), b(1, -2);
	// Print out results, also demonstrating use of overloaded operator<<
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	// Get real and imaginary components, modulus and argument
	cout << "Real{a} = " << a.Get_Real() << endl;
	cout << "Real{b} = " << b.Get_Real() << endl;
	cout << "Im{a} = " << a.Get_Imaginary() << endl; 
	cout << "Im{b} = " << b.Get_Imaginary() << endl;
	cout << "Modulus{a} = " << a.Modulus(a) << endl;
	cout << "Modulus{b} = " << b.Modulus(b) << endl;
	cout << "Arg{a} = " << a.Argument(a) << endl;
	cout << "Arg{b} = " << b.Argument(b) << endl;
	// Get conjugates
	cout << "Conjugate{a} = "; a.Conjugate(a);
	cout << "Conjugates{b} = "; b.Conjugate(b);
	// Get sum, difference, product and quotient of a and b
	cout << "a+b = " << a + b << endl;
	cout << "a-b = " << a - b << endl;
	cout << "a*b = " << a*b << endl;
	cout << "a/b = " << a/b << endl;

	// Show results of overloading arithmetic operators
	cout << "a + 1 =" << a + 1 << endl;
	cout << "b + 1 =" << b + 1 << endl;

	vector<double> re_im_vec; // vector to hold the real and imaginary numbers input 
	re_im_vec = Extract_Complex();
	complex c(re_im_vec[0], re_im_vec[1]); // put input value into the object as c
	// output some values to show that c has been input correctly
	cout << "c = " << c << endl;
	cout << "Real{c} = " << c.Get_Real() << endl;
	cout << "Im{c} = " << c.Get_Imaginary() << endl;
	cout << "Modulus{c} = " << c.Modulus(c) << endl;
	cout << "Arg{c} = " << c.Argument(c) << endl;
	cout << "Conjugate{c} = "; c.Conjugate(c);

	// enter any character to exit
	cout << "Enter any character to exit" << endl;
	string exit_character;
	getline(cin, exit_character);
	return 0;
}