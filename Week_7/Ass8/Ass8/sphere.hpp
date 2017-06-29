#ifndef _sphere_HPP
#define _sphere_HPP

#include<iostream>
#include<vector>
#include<string>
#include "_3D.hpp"

using namespace std;

// class for sphere derived from 3D shapes
class sphere : virtual public _3D
{
private:
	double area, volume;
public:
	// defult constructor
	sphere() : area(0), volume(0) {}
	// parameterised constructor
	sphere(double r) : area(4 * PI*r*r), volume((4.0/3)*PI*r*r*r) {}
	~sphere() { cout << "sphere destructor called" << endl; }
	void info(){
		cout << "sphere: area = " << area << endl;
		cout << "sphere: volume = " << volume << endl;
	};
};

#endif 