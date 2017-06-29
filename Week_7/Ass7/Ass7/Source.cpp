#include<iostream>
#include <string>
#include <vector>

using namespace std;
class Vector // class for generalised vector object will be base for other classes
{
protected:
	double *vec_data; // pointer to vay which will store the data
	int dimensions;
public:
	// Default constructor
	Vector(){ cout << "Vector default constructor called." << endl;  dimensions = 0; vec_data = 0;  }
	// Parametrized constructor
	Vector(int n_in){
		dimensions = n_in; vec_data = new double[dimensions]; // Allocate memory for vec_data 
		for (int i = 0; i<dimensions; i++) vec_data[i] = 0; // set each element equal to 0 until assigned 
	}
	~Vector(){ cout << "Vector destructor called" << endl;
	delete[] vec_data; // Free memory
	}
	// access functions
	int Get_Dim() const { return dimensions; }
	// friend functions
	friend ostream& operator<<(ostream&, const Vector&);
	// Copy constructor
	Vector(Vector&); // copy
	Vector(Vector&&); // Move constructor
	// Function overloading
	Vector& operator=(Vector&); //copy assignment
	Vector& operator=(Vector&&); //move assignment
	double Vector::Dot_Product(const Vector& v1, const Vector& v2);
	double& operator[](int i);
};

class Minkowski_4 : public Vector //second class for Minkowski 4-vectors that is a specialisation of the vector class
{
private:
	//string hubble_type;
	double ct, x, y, z;
public:
	// Default constructor
	Minkowski_4() : Vector(), ct(0) {cout << "Minkowski_4 default constructor called." << endl;}
	// 1st Parametrized constructor
	Minkowski_4(double ct_in, double x_in, double y_in, double z_in) : ct(ct_in), x(x_in), y(y_in), z(z_in) { }
	// 2nd Parametrized constructor
	Minkowski_4(Vector n_in, const double ct_in) : Vector(n_in), ct(ct_in){}
	// Destructor
	~Minkowski_4(){ cout << "Minkowski_4 destructor called" << endl; }
	friend ostream& operator<<(ostream&, const Minkowski_4&);
	double Minkowski_4::Dot_Product(const Minkowski_4& v1, const Minkowski_4& v2);
	// Copy constructor
	Minkowski_4(Minkowski_4&); // copy
	Minkowski_4(Minkowski_4&&); // Move constructor
	// Function overloading
	Minkowski_4& operator=(Minkowski_4&); //copy assignment
	Minkowski_4& operator=(Minkowski_4&&); //move assignment
	Minkowski_4 Minkowski_4::Lorentz_Transform(const Vector& B, const Minkowski_4& m);

};

//Create a third class (particle)that contains a 4 - vector for the current position, a double mass and 3 - vector β as a data members.
class particle : public Minkowski_4 , public Vector{
private:
	double mass;
public:
	// defult constructor
	particle() : Minkowski_4(), mass(0), Vector() { cout << "particle default constructor called." << endl;}
	// Parametrized constructor
	particle(int n_in, const double ct_in, const double mass_in, int dimensions_in) :
		Minkowski_4(n_in, ct_in), mass(mass_in), Vector(dimensions_in){}
	~particle(){ cout << "particle destructor called" << endl; }
	// access functions
	double Get_Mass() const { return mass; }
	friend ostream& operator<<(ostream&, const Minkowski_4&);
	
};

// member function calc dot product
double Vector::Dot_Product(const Vector& v1, const Vector& v2){
	int dims(v1.Get_Dim());
	if (dims != v2.Get_Dim()){
		cerr << "Rows or column number too large for matrix.";
		return 0;
	}
	double dot_prod{ 0 };
	for (int i = 0; i < v1.Get_Dim(); i++){
		dot_prod += v1.vec_data[i] * v2.vec_data[i];
	}
	return dot_prod;
}
// lorentz transofrm 
Minkowski_4 Minkowski_4::Lorentz_Transform(const Vector& B ,const Minkowski_4& m){
	Minkowski_4 new_M;
	double gamma, sqr_mod_B{ 0 };
	 for (int i = 0; i < B.Get_Dim(); i++){
		sqr_mod_B += pow(vec_data[i],2) ;
	}
	 cout << sqr_mod_B;
	 gamma = 1 / (pow((1 - sqr_mod_B), 0.5));
	 new_M.ct = gamma*(ct - vec_data[0] * vec_data[0]);
	for (int i = 0; i < B.Get_Dim(); i++){
		cout << "\nLorentz_Transform " << i << " " << m.vec_data[i] + ((gamma - 1)*(vec_data[i] * m.vec_data[i]) / sqr_mod_B - gamma*ct)* vec_data[i] << endl;
	}	
	return new_M;
}
// member function minowski calc dot product
double Minkowski_4::Dot_Product(const Minkowski_4& v1, const Minkowski_4& v2){
	int dims(v1.Get_Dim());
	if (dims != v2.Get_Dim()){
		cerr << "Rows or column number too large for matrix.";
		return 0;
	}
	double dot_prod{ v1.ct * v2.ct };
	for (int i = 0; i < v1.Get_Dim(); i++){
		dot_prod -= v1.vec_data[i] * v2.vec_data[i];
	}
	return dot_prod;
}
// Overloaded element [] operator implementation
double & Vector::operator[](int i)
{
	if (i<0 || i >= dimensions)
	{
		cout << "Error: trying to access vay element out of bounds" << endl;
		exit(1);
	}
	return vec_data[i];
}


// Copy constructor for deep copying
Vector::Vector(Vector &v)
{
	// Copy size and declare new vay
	cout << "Deep copy constructor\n"<< endl;
	vec_data = 0; dimensions = v.Get_Dim();
	if (dimensions>0)
	{
		vec_data = new double[dimensions];
		// Copy values into new vec_data
		for (int i = 0; i<dimensions; i++) vec_data[i] = v[i];
	}
}
// Move constructor
Vector::Vector(Vector &&v)
{ // steal the data
	cout << "move constructor\n";
	dimensions = v.Get_Dim(); 
	vec_data = v.vec_data;
	v.dimensions = 0; 
	v.vec_data = 0;//nullptr;
}
// Assignment operator for deep copying
Vector & Vector::operator=(Vector &v){
	cout << "Deep copy assignment\n";
	if (&v == this) return *this; // no self assignment
	// First delete this object's vay
	delete[] vec_data; vec_data = 0; dimensions = 0;
	// Now copy rows, columns and declare new vay
	dimensions = v.Get_Dim();
	if (dimensions>0)
	{
		vec_data = new double[dimensions];
		// Copy values into new vay
		for (int i = 0; i<dimensions; i++) vec_data[i] = v[i];
	}
	return *this; // Special pointer!!!
}
// Move assignment operator
Vector & Vector::operator=(Vector&& v)
{
	cout << "move assignment\n";
	std::swap(dimensions, v.dimensions);
	std::swap(vec_data, v.vec_data);
	return *this; // Special pointer!!!
}

// Overload output stream for Vector class
ostream & operator<<(ostream &os, const Vector &v){
	int dim; // dimension number
	dim = v.Get_Dim();
	os << "(";
	for (int i = 0; i < dim; i++){
		os << v.vec_data[i] << ","; // print out element
	}
	os << ")" << endl;
	return os;
}

ostream& operator<<(ostream& o, const Minkowski_4& m){
	o << "Minkowski_4 (ct, x, y, z) = (" << m.ct << "," ;
	int dim; // dimension number
	dim = m.Get_Dim();
	if (dim > 0){
		for (int i = 0; i < dim; i++){
			o << m.vec_data[i] << ","; // print out element
		}
	} else { o << m.x << ", " << m.y << ", " << m.z; }
	o << ")" << endl;
	return o;
}

ostream& operator<<(ostream& o, const particle& p){
	o << "Mass = " << p.Get_Mass() << endl;
	//o << "vec_data = " << p.Get_Dim() << endl;
	return o;
}
// Minowski move / copy functions 
// Copy constructor for deep copying
Minkowski_4::Minkowski_4(Minkowski_4 &v)
{
	// Copy size and declare new vay
	cout << "Deep copy constructor\n" << endl;
	vec_data = 0; dimensions = v.Get_Dim();
	ct = v.ct;
	if (dimensions>0)
	{
		vec_data = new double[dimensions];
		// Copy values into new vec_data
		for (int i = 0; i<dimensions; i++) vec_data[i] = v[i];
	}
}
// Move constructor
Minkowski_4::Minkowski_4(Minkowski_4 &&v)
{ // steal the data
	cout << "move constructor\n";
	dimensions = v.Get_Dim();
	vec_data = v.vec_data;
	v.dimensions = 0;
	v.vec_data = 0;//nullptr;
	ct = v.ct;
}
// Assignment operator for deep copying
Minkowski_4 & Minkowski_4::operator=(Minkowski_4 &v){
	cout << "Deep copy assignment\n";
	ct = v.ct;
	if (&v == this) return *this; // no self assignment
	// First delete this object's vay
	delete[] vec_data; vec_data = 0; dimensions = 0;
	// Now copy rows, columns and declare new vay
	dimensions = v.Get_Dim();
	if (dimensions>0)
	{
		vec_data = new double[dimensions];
		// Copy values into new vay
		for (int i = 0; i<dimensions; i++) vec_data[i] = v[i];
	}
	return *this; // Special pointer!!!
}
// Move assignment operator
Minkowski_4 & Minkowski_4::operator=(Minkowski_4&& v){
	cout << "move assignment\n";
	ct = v.ct;
	std::swap(ct, v.ct);
	std::swap(vec_data, v.vec_data);
	return *this; // Special pointer!!!
}


int main()
{
	Vector A(4);
	Vector A1(3);
	Vector A2(3);
	Vector A3(3);
	A3[1] = 2; A3[2] = 4;
	
	// Set values for a2 here and then print out some
	for (int i = 0; i < A2.Get_Dim(); i++)
	{
		A1[i] = 1;
		A2[i] = i;
	}
	cout << "A = " << A << endl;
	A = A2;
	cout << "A1 = " << A1 << endl;
	cout << "A2 = " << A2 << endl;
	cout << "A = A2 " << A << endl;
	cout << "A3 = " << A3 << endl;
	cout << "Dot product(A1,A2) = " << A1.Dot_Product(A1, A2) << endl;
	cout << "A2[1] = " << A2[1] << endl;

	Minkowski_4 M(A1,10);
	cout << "M = " << M << endl;
	Minkowski_4 M2(A2, 0);
	cout << "M2 = " << M2 << endl;
	Minkowski_4 M3(1, 2, 3,4);
	cout << "M3 = " << M3 << endl;	
	Minkowski_4 M4(0,0);
	M4 = M;
	cout << "M4 = M = " << M4 << endl;
	M4 = move(M2);
	cout << "M4 = move(M2) = " << M4 << endl;
	cout << "Minkowski_4 Dot product(M,M2) = " << M.Dot_Product(M, M2) << endl;
	Vector A5(3);
	for (int i = 0; i < A5.Get_Dim(); i++)
	{
		A5[i] = 1+10*i;
	} 
	cout << "A5 = " << A5 << endl;
	Minkowski_4 M5(A5, 0);
	cout << "M4.Lorentz_Transform(A5)" << M5.Lorentz_Transform(A2,M5) << endl;

	particle P(4, 911.0, 33.0, 5);
	cout << "P = " << P << endl;

	// enter any character to exit
	char exit_character{ 'y' };
	while (exit_character != 'x'){
		cout << "Enter 'x' to exit" << endl;
		cin >> exit_character;
	}
	return 0;
}