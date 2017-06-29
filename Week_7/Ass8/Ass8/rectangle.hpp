#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include<iostream>
#include<vector>
#include<string>
#include "_2D.hpp"

using namespace std;

// class for rectangles derived from 2D shapes
class rectangle : virtual public _2D
{
private:
	double length, width, area, volume;
public:
	// defult constructor
	rectangle() : area(0), volume(0) {}
	// parameterised constructor
	rectangle(double x, double y) : area(x*y), volume(0) {}
	~rectangle() { cout << "rectangle destructor called" << endl; }
	void info(){
		cout << "Rectangle: area = " << area << endl;
		cout << "Rectangle: volume = " << volume << endl;
	};
	double Get_Area(){ return area; }
};

#endif 