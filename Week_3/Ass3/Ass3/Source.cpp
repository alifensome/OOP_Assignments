// Simple code to store courses using vectors and strings
/*
Assignment 3
physics course database
Write a C++ program to store and print physics courses
Allow the user to enter an arbitrary number of courses
Ask the user to provide a course code (as an integer, e.g. 30762) and title (as a string, e.g. Object-Oriented Programming in C++), both on a single line
Use a string stream to create a string containing the full course title, e.g.
PHYS 30762 Object-Oriented Programming in C++
Each of these strings should be stored in a vector
Print out full course list using an iterator

Assignment 3
physics course database
Your program should correctly use
a vector of strings to store course data (0.5 mark)
a string stream to combine the integer course code and title (0.5 mark)
an iterator to print out information for each course (1 mark)
Your code should also be able to print out a list of courses for a particular year, as identified by the first digit of the course code (1 mark)
It should be possible to sort the list of courses by title or course code (1 mark)
Negative marks:
NEW: If program does not compile without errors (-1 mark)
For poor layout or poor choice of variables (-1 mark)
If not present for marking or code poorly presented (-1 mark)
Assignment deadline: Friday 24th February at 4.45; Marked before 5pm
*/

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include <algorithm>    // to use the sort algorithm 

using namespace std;

// comparison function for use in sort which returns ​true if the first argument is less than the second.
bool Alphabetical_Order(string i, string j) { 
	// manipulate i string untill it is only the name of the course without course code or number
	string i_sub = i.substr(5, i.length());
	int i_space_pos = i_sub.find(' ');
	i_sub = i_sub.substr(i_space_pos);
	// manipulate j string untill it is only the name of the course without course code or number
	string j_sub = j.substr(5, j.length());
	int j_space_pos = j_sub.find(' ');
	j_sub = j_sub.substr(j_space_pos);

	return (i_sub<j_sub); // return logically true if first argument is less than second
}

int main(void)
{
	// decleare variables and constants
	const string degreeCode("PHYS"); // course code for physics
	const string end_char("x"); // character which if entered terminates do loop
	vector < string > course_list; // vector for storage
	vector <int> course_number_vec; // vector to hold course numbers as an integer, used later to order the courses
	string input_string; // the string input into cin
	string code_number_name; // a string containing the correctly formatted information in order of course code, number, name
	int course_number; // the number of the course which the user enters
	string course_name; // the name of the course which the user enters
	string year_choice; // variable for which year to print out 
	char sort_option; // string to hold the choise of how to sort.
	vector <string> course_list_chosen_year;

	// Gather list of courses and their codes from user,
	bool not_finished(true);
	do // do...while loop checks its condition at the bottom of the loop.
	{
		cout << "Please enter a course number and name on the same line (or x to finish):\n" << endl;
		getline(cin, input_string); // 

		cout << "You have entered: " << input_string << endl;

		if (input_string.compare(end_char) != 0){ // compare the srings if mystring = x the will return 0.
			stringstream user_input(input_string); // string stream to hold what the user has entered untill it can be split up
			cout << "input string = " << input_string << endl;
			user_input >> course_number; // split up the ss into an integer leave the string
			getline(user_input, course_name); // extract string from ss usig getline puting it into course_name
			cout << "Course name: " << course_name << endl;
			cout << "Course number: " << course_number << endl;
			code_number_name = degreeCode + " " + to_string(course_number) + " " + course_name;
			// push back string or complete course title and integer of course number into two differnt vectors
			course_list.push_back(code_number_name);
			course_number_vec.push_back(course_number);
			cout << "Course: " << code_number_name << " has been saved." << endl;
		}

		else{ // if x is entered break the loop.
			not_finished = false;
			cout << "Finished entering course detrails." << endl;
		}	
	
	} while (not_finished);

	//// Print out full list of courses
	cout << "List of courses:" << endl;
	for (auto i = course_list.begin(); i != course_list.end(); ++i){
		cout << *i << ' ' << endl;
	}

	//// Extract courses belonging to a certain year
	cout << "Please enter year: ";
	cin >> year_choice;
	int element_number{ 0 };
	for (auto i = course_number_vec.begin(); i != course_number_vec.end(); ++i){
		string course_year = to_string(*i);
		course_year = course_year[0];
		if (course_year == year_choice){
			course_list_chosen_year.push_back(course_list[element_number]); // save the year specific courses to a new vector
			cout << element_number << ' ' << course_list[element_number] << endl;
		}
		element_number++;
	}

	// choose whether to sort by name of course or by course code then output list appropriately
	cout << "Sort by code or name. Enter 'n' for name or 'c' for code: ";
	cin >> sort_option;
	if (sort_option == 'c'){ // sort by code!
		cout << "Sorting by code:" << endl;
		// sort using the sort algorithm 
		sort(course_list_chosen_year.begin(), course_list_chosen_year.end());
		cout << "\nSorted list of courses:" << endl;
		for (auto i = course_list_chosen_year.begin(); i != course_list_chosen_year.end(); ++i){
			cout << *i << ' ' << endl; // print list thats sorted

		}
	}
	if (sort_option == 'n'){ // sort by name!
		cout << "Sorting by name:" << endl;
		// again sort using the sort algorithm 
		sort(course_list_chosen_year.begin(), course_list_chosen_year.end(), Alphabetical_Order);
		cout << "\nSorted list of courses:" << endl;
		for (auto i = course_list_chosen_year.begin(); i != course_list_chosen_year.end(); ++i){
			cout << *i << ' ' << endl; // print list thats sorted
		}
	}


	cout << "\nEnter any character to exit." << endl;
	char close_command_window; 
	cin >> close_command_window; // enter something before the window closes!
	return 0;
}