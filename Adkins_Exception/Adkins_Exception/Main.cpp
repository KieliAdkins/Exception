/*
	This file includes all the information to check for viable usernames inserted into a system.
*/

// Including standard libraries
#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <fstream>

using namespace std; 

// My Personalized Exception
struct myException : public exception
{
	const char * what() const throw ()
	{
		// Printing the information
		return "Error: Invalid entry. Please choose a different username.";
	}
};

// Main Function
int main() {

	// Declaring the Variables
	string userName;
	string realName;
	char inputAgain;
	int userLength = 0;
	int i = 0;
	int v = 0;
	const int MAX_WORDS = 15;
	vector<string> userList;
	vector<string> nameList;
	vector<string> nonUsables;

	// Opening file
	ifstream infile("nonusables.txt");
	string inStr[MAX_WORDS];

	for (i = 0; i < MAX_WORDS; i++)
	{
		if (!infile.eof()) {
			infile >> inStr[i];
			nonUsables.push_back(inStr[i]);
		}
	}

	// Real Name Input
	cout << "Please enter your last name: " << endl;
	cin >> realName;
	nameList.push_back(realName);

	// Do While Loop
	do
	{
		// Username Input
		cout << endl << "Your username must be shorter than 15 characters." << endl;
		cout << "Please enter a username: " << endl;
		cin >> userName;
		system("pause");

		// Try Block
		try
		{
			for (i = 0; i < nameList.size(); i++)
			{
				// If Username uses person's real name
				if (nameList[i] == userName)
				{
					throw "Error: Last name cannot be used as username.";
				}

				// If the username has more than 15 characters
				if (userName.size() >= 15)
				{
					throw length_error("Username incorrect length. Please enter a new username.");
				}

				// If the username is set as "username"
				if (userName == "username")
				{
					throw invalid_argument("Error: Username is not acceptable. Please enter a new username."); 
				}

				// If the username is already present on the userlist
				if (nonUsables[i] == userName)
				{
					throw myException();
				}

				else
				{
					userList.push_back(userName);
					cout << "Congratulations! " << realName << ", Username " << userName << " accepted." << endl;
				}
			}
		}

		// Catch block for a throw message
		catch (const char* msg) 
		{
			cerr << msg << endl;
		}

		// Catch block for a length error
		catch (length_error& le)
		{
			cerr << le.what() << endl;
		}

		// Catch block for an invalid argument
		catch (invalid_argument& ia)
		{
			cerr << ia.what() << endl;
		}

		// Catch block for a personalized exception
		catch (myException& e)
		{
		cout << e.what() << endl;
		}

		// Printing the play again information
		cout << endl << "Would you like to input a new username? (y/n)" << endl;
		cin >> inputAgain; 
		
	} while (inputAgain != 'n');

	// Closing the opened file
	infile.close();

	system("pause");
	return 0;
}
