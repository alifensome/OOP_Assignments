#ifndef _cuboid_HPP
#define _cuboid_HPP

#include<iostream>
#include<vector>
#include<string>
#include "_3D.hpp"

using namespace std;

// class for cuboid derived from 3D shapes
class cuboid : virtual public _3D
{
private:
	double area, volume;
public:
	// defult constructor
	cuboid() : area(0), volume(0) {}
	// parameterised constructor
	cuboid(double x, double y, double z) : area(2*x*y + 2*y*z +2*x*z), volume(x*y*z) {}
	~cuboid() { cout << "cuboid destructor called" << endl; }
	void info(){
		cout << "cuboid: area = " << area << endl;
		cout << "cuboid: volume = " << volume << endl;
	};
};

#endif 