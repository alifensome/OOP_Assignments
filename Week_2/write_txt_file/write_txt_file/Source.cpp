// Write a .txt file
#include<iostream>
#include<fstream>


using namespace std;

int main()
{

	ofstream outfile("Text_File.txt");

	outfile << "Hello world!" << endl;

	outfile.close();
	
	return 0;
}
