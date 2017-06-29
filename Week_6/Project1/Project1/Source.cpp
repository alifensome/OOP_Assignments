// PHYS 30762 Programming in C++
// Assignment 6
#include<stdlib.h> // for c style exit
#include<string>
#include<iostream>

using namespace std;

class matrix
{
	// Friends
	friend ostream & operator<<(ostream &os, const matrix &mat);
	friend istream & operator>>(istream &input, const matrix &mat);

private:
	double *mdata;
	int rows, columns;
public:
	// Default constructor
	matrix(){ cout << "Default constructor called." << endl; mdata = 0; rows = columns = 0; }
	// Parameterized constructor
	matrix( int m, int n){ rows = m; columns = n; 
	// Allocate memory for data 
	mdata = new double[rows*columns]; // data now points to an array of size row*columns.
	for (int i = 0; i<rows*columns; i++) mdata[i] = 0;
	}
	// Destructor
	~matrix(){
		cout << "Destructor called" << endl;	
		// Free memory
		delete[] mdata;
	}
	// Copy constructor
	matrix(matrix&); // copy
	matrix(matrix&&); // Move constructor
	// Function overloading
	matrix& operator=(matrix&); //copy assignment
	matrix& operator=(matrix&&); //move assignment
	matrix operator+(const matrix& mat);
	matrix operator-(const matrix& mat);
	matrix operator*(const matrix& mat);
	matrix matrix::Delete_Row_Col(const matrix& mat);

	double& operator[](int i);
	int Number_of_Elements() const { return rows*columns; }
	// Access functions
	int Get_Rows() const { return rows; } // Return number of rows
	int Get_Cols() const { return columns; } // Return number of columns
	double & operator()(int m, int n) { return mdata[Index(m, n)]; }
	int Index(int m, int n) const // Return position in array of element (m,n)
	{
		if (m>(-1) && m <= rows && n>(-1) && n <= columns) return (n) + (m)*columns;
		else { cout << "Error: out of range." << endl; exit(1); }
	}
};

	// Copy constructor for deep copying
	matrix::matrix(matrix &arr)
	{
		// Copy size and declare new array
		cout << "Deep copy constructor\n";
		mdata = 0; rows = arr.Get_Rows(); columns = arr.Get_Cols();
		if (rows>0 || columns>0)
		{
			mdata = new double[arr.Number_of_Elements()];
			// Copy values into new mdata
			for (int i = 0; i<arr.Number_of_Elements(); i++) mdata[i] = arr[i];
		}
	}
	// Move constructor
	matrix::matrix(matrix &&arr)
	{ // steal the data
		cout << "move constructor\n";
		rows = arr.Get_Rows(); columns = arr.Get_Cols();
		mdata = arr.mdata;
		arr.rows = 0; arr.columns = 0;
		arr.mdata = 0;//nullptr;
	}
	// Assignment operator for deep copying
	matrix & matrix::operator=(matrix &arr){
		cout << "Deep copy assignment\n";
		if (&arr == this) return *this; // no self assignment
		// First delete this object's array
		delete[] mdata; mdata = 0; rows = 0; columns = 0;
		// Now copy rows, columns and declare new array
		rows = arr.Get_Rows(); columns = arr.Get_Cols();
		if (rows>0 || columns>0)
		{
			mdata = new double[rows*columns];
			// Copy values into new array
			for (int i = 0; i<rows*columns; i++) mdata[i] = arr[i];
		}
		return *this; // Special pointer!!!
	}
	// Move assignment operator
	matrix & matrix::operator=(matrix&& arr)
	{
		cout << "move assignment\n";
		std::swap(rows, arr.rows);
		std::swap(columns, arr.columns);
		std::swap(mdata, arr.mdata);
		return *this; // Special pointer!!!
	}

	// Overloaded element [] operator implementation
	double & matrix::operator[](int i)
	{
		if (i<0 || i >= rows*columns)
		{
			cout << "Error: trying to access array element out of bounds" << endl;
			exit(1);
		}
		return mdata[i];
	}

	// member function to delete a column and row
	matrix matrix::Delete_Row_Col(const matrix& mat){
		int del_row, del_col;
		cout << "Enter a row to delete (0 being the first row, 1 being second ...):";
		cin >> del_row;
		cout << "Enter a column to delete (0 being the first row, 1 being second ...):";
		cin >> del_col;
		if (del_col > mat.rows || del_row > mat.columns){
			cerr << "Rows or column number too large for matrix.";
			return (*this);
		}
		matrix new_mat(mat.Get_Rows()-1, mat.Get_Cols()-1);
		int l = 0;
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < mat.Get_Cols(); j++){
				if (i != del_row && j!=del_col){
					new_mat.mdata[l] = mat.mdata[Index(i, j)];
					l++;
				}
			}
		}
		return new_mat;
	}

	// Addition, subtraction and multiplication
	matrix matrix::operator+(const matrix& mat){

		// first, make sure matrices can be added. if not, return original matrix
		if (rows != mat.rows || columns != mat.columns){
			cerr << "Matrix sizes do not match.";
			return (*this);
		}
		cout << "Adding matricies." << endl;
		matrix new_mat(mat.Get_Rows(), mat.Get_Cols());
		for (int i = 0; i < mat.Get_Rows(); i++){
			for (int j = 0; j < mat.Get_Cols(); j++){
				new_mat.mdata[(j)+(i)*mat.Get_Cols()] = mdata[(j)+(i)*columns] + mat.mdata[(j)+(i)*mat.Get_Cols()];
			}
		}
		return new_mat;
	}

	// Addition, subtraction and multiplication
	matrix matrix::operator-(const matrix& mat){
		
		// first, make sure matrices can be added. if not, return original matrix
		if (rows != mat.Get_Rows() || columns != mat.Get_Cols()){
			cerr << "Matrix sizes do not match.";
			return (*this);
		}
		cout << "subtracting matricies." << endl;
		matrix new_mat(mat.Get_Rows(), mat.Get_Cols());
		for (int i = 0; i < mat.Get_Rows(); i++){
			for (int j = 0; j < mat.Get_Cols(); j++){
				new_mat.mdata[(j)+(i)*mat.Get_Cols()] = mdata[(j)+(i)*columns] - mat.mdata[(j)+(i)*mat.Get_Cols()];
			}
		}
		return new_mat;
	}

	// Addition, subtraction and multiplication
	matrix matrix::operator*(const matrix& mat){
		cout << "Multiplying matricies." << endl;
		if (columns != mat.rows || rows != mat.columns){
			cerr << "Matrix sizes do not match.";
			return (*this);
		}
		matrix new_mat(mat.Get_Rows(), mat.Get_Cols());
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < mat.Get_Cols(); j++){
					for (int k = 0; k < columns; ++k)
					{
						new_mat.mdata[Index(i, j)] += mdata[Index(i,k)]*mat.mdata[Index(k,j)];
					}

			}
		}
		return new_mat;
	}

// Overload insertion to output stream for matrices
ostream & operator<<(ostream &os, const matrix &mat)
{
	int max_r, max_c; // max column and row numbers
	max_r = mat.Get_Rows();
	max_c = mat.Get_Cols();

	for (int i = 0; i < max_r; i++) // for each row
	{
		for (int j = 0; j < max_c; j++) // for each column of each row
		{
			os << mat.mdata[(j ) + (i)*max_c] << ","; // print out element
			//cout << i << j << " ";
		}
		os << endl; // carage return at the end of a row.
	}
	return os;
}

// Overload insertion to input matrices
istream & operator>>(istream &input, const matrix &mat)
{
	int max_r, max_c; // max column and row numbers
	max_r = mat.Get_Rows();
	max_c = mat.Get_Cols();
	for (int i = 0; i < max_r; i++) // for each row
	{
		for (int j = 0; j < max_c; j++) // for each column of each row
		{
			input >> mat.mdata[(j)+(i)*max_c];
		}
	}
	return input;
}

int main()
{

	// Demonstrate default constructor
	matrix a1;
	cout << "a1 = \n" << a1 <<endl;

	// Parameterized constructor
	const int m(2), n(2);
	matrix a2(m, n);
	cout << "a2 = \n" << a2;

	// Set values for a2 here and then print out some
	for (int i = 0; i < a2.Get_Rows()*a2.Get_Cols(); i++)
	{
		a2[i] = i;
	}
	a1 = a2;
	cout << "a1 = a2 = \n" << a1;
	cout << "a2 = \n" << a2;
	cout << "a2[0] = " << a2[0] << endl;
	cout << "a2[1] = " << a2[1] << endl;

	// Deep copy by assignment: define new matrix a3 then copy from a2 to a3
	matrix a3(m, n);
	cout << "a3 = \n" << a3 << endl;
	a3 = a2;
	cout  << "a3 = a2 = \n" << a3 << endl;
	// Modify contents of original matrix and show assigned matrix is unchanged here
	// Set values for a2 here and then print out some
	for (int i = 0; i < a2.Get_Rows()*a2.Get_Cols(); i++)
	{
		a2[i] = 10*i;
	}
	cout << "a2 = \n" << a2;
	cout << "a3 = \n" << a3;

	// Deep copy using copy constructor 
	matrix a4(a2);
	cout << "a4(a2) = \n" << a4;
	// Modify contents of original matrix and show copied matrix is unchanged here
	cout << "a2 = \n" << a2;
	cout << "a4 = \n" << a4;

	// Move copy construction demonstration
	matrix a9(a2);
	cout << "Now move values by assignment." << endl;
	a9 = move(a3);

	// show >> operator overloading 
	matrix a5(m, n);
	cout << "Enter values for insersion into a5." << endl;
	cin >> a5;
	cout << "a5 = \n" << a5 << endl;

	matrix a6(m, n);
		a6 = a5 + a2;
		cout << "a6 = \n" << a6 << endl;
	
	matrix a7(m, n);
		a7 = a5 - a2;
		cout << "a7 = \n" << a7 << endl;
	matrix a8(m, n);
		a8 = a5*a1;
		cout << "a8 = a5*a1 = \n" << a8 << endl;

	matrix a10(m, n);
	matrix a11(m, n+1);
	matrix a12;
	cout << "Multiply two different sized matries:" << endl;
		a12 = a10*a11;
		matrix a13;


	matrix a14(3, 3);
	cout << "Enter values for insersion into a14." << endl;
	cin >> a14;
	cout << "a14 = \n" << a14 << endl;
		a13 = a14.Delete_Row_Col(a14);
		cout << "a13 = \n" << a13 << endl;

	// enter any character to exit
	char exit_character{'y'};
	while (exit_character != 'x'){
		cout << "Enter 'x' to exit" << endl;
		cin >> exit_character;
	}
	return 0;
}