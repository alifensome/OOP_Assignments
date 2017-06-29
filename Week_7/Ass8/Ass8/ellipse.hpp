#ifndef _ellipse_HPP
#define _ellipse_HPP

#include<iostream>
#include<vector>
#include<string>
#include "_2D.hpp"

using namespace std;

// class for ellipse derived from 2D shapes
class ellipse : virtual public _2D
{
private:
	double radius_1,radius_2, area, volume;
public:
	// defult constructor
	ellipse() : area(0), volume(0) {}
	// parameterised constructor
	ellipse(double r1, double r2) : area(PI*r1*r2), volume(0) {}
	~ellipse() { cout << "ellipse destructor called" << endl; }
	void info(){
		cout << "ellipse: area = " << area << endl;
		cout << "ellipse: volume = " << volume << endl;
	};
	double Get_Area(){ return area;}
};

#endif 