#ifndef _ellipsoid_HPP
#define _ellipsoid_HPP

#include<iostream>
#include<vector>
#include<string>
#include "_3D.hpp"

using namespace std;

// class for ellipsoid derived from 3D shapes
class ellipsoid : virtual public _3D
{
private:
	double area, volume, x1,x2,x3;
public:
	// defult constructor
	ellipsoid() : area(0), volume(0) {}
	// parameterised constructor
	ellipsoid(double a, double b, double c) : x1(a), x2(b), x3(c), area(Area_Ellipsoid(a,b,c)), volume((4.0/3)* PI*a*b*c) {}
	~ellipsoid() { cout << "ellipsoid destructor called" << endl; }
	void info(){
		cout << "ellipsoid: area = " << area << endl;
		cout << "ellipsoid: volume = " << volume << endl;
	};
	double ellipsoid::Area_Ellipsoid(double x1, double x2, double x3);
};

// member function approximate surface area of ellipsode
double ellipsoid::Area_Ellipsoid(double x1, double x2, double x3){
	const double p{1.6075}; // value of power to approximate the surface area of an ellipsoid 
	double A;
	A = 4 * PI * pow(((pow(x1*x2, p) + pow(x2*x3, p) + pow(x1*x3, p)) / 3), (1/p));
	return A;
}
#endif 