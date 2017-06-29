#ifndef _cube_HPP
#define _cube_HPP

#include<iostream>
#include<vector>
#include<string>
#include "_3D.hpp"

using namespace std;

// class for cube derived from 3D shapes
class cube : virtual public _3D
{
private:
	double area, volume;
public:
	// defult constructor
	cube() : area(0), volume(0) {}
	// parameterised constructor
	cube(double x) : area(6 * x*x), volume(x*x*x) {}
	~cube() { cout << "cube destructor called" << endl; }
	void info(){
		cout << "cube: area = " << area << endl;
		cout << "cube: volume = " << volume << endl;
	};
};

#endif 