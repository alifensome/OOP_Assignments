#ifndef _prism_HPP
#define _prism_HPP

#include<iostream>
#include<vector>
#include<string>
#include "_2D.hpp"

using namespace std;

// class for prism derived friend of _2D
class prism
{
private:
	double prism_area, prism_volume;
public:
	// defult constructor
	prism() : prism_area(0), prism_volume(0) {}
	// parameterised constructor
	prism(_2D*  base_class_pointer, double z) : prism_area(base_class_pointer->Get_Area()), prism_volume(prism_area*z) {}
	~prism() { cout << "prism destructor called" << endl; }
	void info(){
		cout << "2D shape area = " << prism_area << endl;
		cout << "prism: volume = " << prism_volume << endl;
	};
};
//_2D*  base_class_ponter,
#endif 