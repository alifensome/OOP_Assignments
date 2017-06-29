#ifndef _3D_HPP
#define _3D_HPP

#include<iostream>
#include<vector>
#include<string>
#include "shape.hpp"

using namespace std;

// Another abstract class for 3D shapes
class _3D : virtual public shape
{
private:
	double area, volume;
public:
	// defult constructor to set all variables to 0
	_3D() : area(0), volume(0) {}
	virtual ~_3D() { cout << "3D destructor called" << endl; }
	virtual void info() = 0;
};

#endif 