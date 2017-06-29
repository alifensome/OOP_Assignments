#ifndef _SQUARE_HPP
#define _SQUARE_HPP
	
#include<iostream>
#include<vector>
#include<string>
#include "_2D.hpp"

using namespace std;

// class for rectangles derived from 2D shapes
class square : virtual public _2D
{
private:
	double length, area, volume;
public:
	// defult constructor
	square() : area(0), volume(0) {}
	// parameterised constructor
	square(double x) : area(x*x), volume(0) {}
	~square() { cout << "square destructor called" << endl; }
	void info(){
		cout << "square: area = " << area << endl;
		cout << "square: volume = " << volume << endl;
	};
	double Get_Area(){ return area; }
};

#endif 