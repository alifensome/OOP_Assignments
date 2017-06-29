#include<iostream>
#include <stdlib.h>  
#include<string>
using namespace std;
//dynamic array
class dynarr
{
private:
	int size;
	double *array;
public:
	dynarr(){ cout << "Default constructor called" << endl; size = 0; array = 0; }
	dynarr(int s); // parametrised
	dynarr(dynarr&); // copy
	dynarr(dynarr&&); //move
	~dynarr(){ cout << "Destructor called" << endl; }
	dynarr& operator=(dynarr&); //copy assignment
	dynarr& operator=(dynarr&&); //move assignment
	int length() const { return size; }
	double & operator[](int i);
};
// Copy constructor for deep copying
dynarr::dynarr(dynarr &arr)
{
	// Copy size and declare new array
	cout << "copy constructor\n";
	array = 0; size = arr.length();
	if (size>0)
	{
		array = new double[size];
		// Copy values into new array
		for (int i = 0; i<size; i++) array[i] = arr[i];
	}
}
// Move constructor
dynarr::dynarr(dynarr &&arr)
{ // steal the data
	cout << "move constructor\n";
	size = arr.size;
	array = arr.array;
	arr.size = 0;
	arr.array = 0;//nullptr;
}
// Assignment operator for deep copying
dynarr & dynarr::operator=(dynarr &arr)
{
	cout << "copy assignment\n";
	if (&arr == this) return *this; // no self assignment
	// First delete this object's array
	delete[] array; array = 0; size = 0;
	// Now copy size and declare new array
	size = arr.length();
	if (size>0)
	{
		array = new double[size];
		// Copy values into new array
		for (int i = 0; i<size; i++) array[i] = arr[i];
	}
	return *this; // Special pointer!!!
}
// Move assignment operator
dynarr & dynarr::operator=(dynarr&& arr)
{
	cout << "move assignment\n";
	std::swap(size, arr.size);
	std::swap(array, arr.array);
	return *this; // Special pointer!!!
}
// Parameterized constructor implementation
dynarr::dynarr(int s)
{
	cout << "Parameterized constructor called" << endl;
	if (s<1)
	{
		cout << "Error: trying to declare an array with size < 1" << endl;
		exit(1);
	}
	size = s;
	array = new double[size];
	for (int i = 0; i<size; i++) array[i] = 0;
}

// Overloaded element [] operator implementation
double & dynarr::operator[](int i)
{
	if (i<0 || i >= size)
	{
		cout << "Error: trying to access array element out of bounds" << endl;
		exit(1);
	}
	return array[i];
}
int main()
{
	cout << "Declaring array a1 with parameterized constructor" << endl;
	dynarr a1(2);
	cout << "Length of a1 = " << a1.length() << endl;
	a1[0] = 0.5;
	a1[1] = 1.0;
	cout << "a1[0] = " << a1[0] << endl;
	cout << "a1[1] = " << a1[1] << endl;
	cout << endl;

	cout << "Declaring array a2 with default constructor" << endl;
	dynarr a2;
	cout << "Length of a2 = " << a2.length() << endl;
	cout << "Now copy values from a1 by assignment" << endl;
	a2 = a1;
	cout << "Length of a2 = " << a2.length() << " and of a1 =" << a1.length() << endl;
	cout << "a2[0] = " << a2[0] << endl;
	cout << "a2[1] = " << a2[1] << endl;
	cout << endl;

	cout << "Declaring array a3 with parameterized constructor" << endl;
	dynarr a3(2);
	cout << "Length of a3 = " << a3.length() << endl;
	a3[0] = 0.5;
	a3[1] = 1.0;
	cout << "a3[0] = " << a3[0] << endl;
	cout << "a3[1] = " << a3[1] << endl;
	cout << endl;
	cout << "Now move values from a1 by assignment" << endl;
	dynarr a4;
	a4 = move(a3);
	cout << "Length of a4 = " << a4.length() << " and of a3 =" << a3.length() << endl;
	cout << "a4[0] = " << a4[0] << endl;
	cout << "a4[1] = " << a4[1] << endl;
	cout << endl;



	// enter any character to exit
	cout << "Enter any character to exit" << endl;
	string exit_character;
	getline(cin, exit_character);
	return 0;
}