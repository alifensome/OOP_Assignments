// Example of program using dynamic memory allocation
#include<iostream>
using namespace std;

// notes
/* pointer: variable that contains memory adress for value.
&variable memory adress of var
pointer will refer to this memory adress and may alter the contence of the adress
*/

int main()
{
	int N(0);
	// Get number of values
	cout << "Enter the number of values to enter: ";
	cin >> N;
	cout << "You would like to enter " << N << " values" << endl;
	// allocate memory for array of values
	double *mydata = new double[N];
	cout << "Allocated memory for " << N << " doubles" << endl;
	cout << "Enter " << N << " doubles" << endl;
	for (int i(0); i<N; i++)
	{
		cin >> mydata[i];
	}
	cout << "Here are your values: ";
	for (int i(0); i<N; i++) cout << mydata[i] << " ";
	cout << endl;
	// Free memory
	delete[] mydata;
	cout << "Freed memory" << endl;
	return 0;
}