#ifndef SHAPE_HPP
#define SHAPE_HPP

#include<iostream>
#include<vector>
#include<string>
using namespace std;

// Abstract base class as interface only
class shape
{
public:
	virtual ~shape(){ cout << "Destroying shape" << endl; } // VIRTUAL DESTRUCTOR
	virtual void info() = 0; // pure virtual function   
	const double PI{3.14159265359}; // value of pi
};

#endif 