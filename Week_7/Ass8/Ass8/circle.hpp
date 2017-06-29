#ifndef _circle_HPP
#define _circle_HPP

#include<iostream>
#include<vector>
#include<string>
#include "_2D.hpp"

using namespace std;

// class for circles derived from 2D shapes
class circle : virtual public _2D
{
private:
	double radius, area, volume;
public:
	// defult constructor
	circle() : area(0), volume(0) {}
	// parameterised constructor
	circle(double r) : area(PI*r*r), volume(0) {}
	~circle() { cout << "circle destructor called" << endl; }
	void info(){
		cout << "circle: area = " << area << endl;
		cout << "circle: volume = " << volume << endl;
	};
	double Get_Area(){ return area; }
};

#endif 