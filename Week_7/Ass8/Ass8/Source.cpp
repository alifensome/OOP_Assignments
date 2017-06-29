#include<iostream>
#include<vector>
#include<string>
// include 2D shapes .hpp files
#include "shape.hpp"
#include "_2D.hpp"
#include "_3D.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "circle.hpp"
#include "ellipse.hpp"
// include 3D shapes .hpp files
#include "ellipsoid.hpp"
#include "cube.hpp"
#include "cuboid.hpp"
#include "sphere.hpp"
// include prism .hpp files
#include "prism.hpp"

using namespace std;

int main()
{
	// Vectors of base class pointers in 2D and 3D 
	vector<_2D*> shape_vector_2D;
	vector<_3D*> shape_vector_3D;
	shape_vector_2D.push_back(new rectangle(1, 2));
	shape_vector_2D.push_back(new square(1));
	shape_vector_2D.push_back(new circle(1));
	shape_vector_2D.push_back(new ellipse(1, 2));
	shape_vector_3D.push_back(new cuboid(1, 2, 3));
	shape_vector_3D.push_back(new cube(1));
	shape_vector_3D.push_back(new sphere(1));
	shape_vector_3D.push_back(new ellipsoid(1, 2, 3));

	// print out info for the shapes in a loop
	cout << "*** 2D shapes ***" << endl;
	for (size_t i{ 0 }; i < shape_vector_2D.size(); i++){
		shape_vector_2D[i]->info(); 
	} 
	// print out info for the shapes in a loop
	cout << "*** 3D shapes ***" << endl;
	for (size_t i{ 0 }; i < shape_vector_3D.size(); i++){
		shape_vector_3D[i]->info();
	}
	
	// print out info for the shapes in a loop
	cout << "*** Prism from 2D shapes ***" << endl;
	for (size_t i{ 0 }; i < shape_vector_2D.size(); i++){
		prism(shape_vector_2D[i],2).info();
	}

	// deleat 2d shapes and clear vector
	cout << "*** Delete 2D shapes ***" << endl;
	for (auto shape_vectorit = shape_vector_2D.begin();
		shape_vectorit<shape_vector_2D.end();
		++shape_vectorit) 
		delete *shape_vectorit;
	shape_vector_2D.clear();

	// deleat 3d shapes and clear vector
	cout << "*** Delete 3D shapes ***" << endl;
	for (auto shape_vectorit = shape_vector_3D.begin();
		shape_vectorit<shape_vector_3D.end();
		++shape_vectorit)
		delete *shape_vectorit;
	shape_vector_3D.clear();

	cin.ignore();
	return 0;
}