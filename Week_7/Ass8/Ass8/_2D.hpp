#ifndef _2D_HPP
#define _2D_HPP

#include<iostream>
#include<vector>
#include<string>
#include "shape.hpp"


using namespace std;

// Another abstract class for 2D shapes
class _2D : virtual public shape
{
	friend class prism;
private:
	double area, volume;
public:
	// defult constructor to set all to 0
	_2D() : area(0), volume(0) {}
	virtual ~_2D() { cout << "_2D destructor called" << endl; }
	virtual void info() = 0;
	virtual double Get_Area() = 0;
};

#endif 