// Main interface for the program

/*
 * To compile in VS 2019
 * Open directory in developer command prompt
 * run "cl /EHsc .\sqlite\sqlite3.c *.cpp /Fe.\ChocAnDB.exe"
 */

#include <cctype>
#include <iostream>
#include <time.h>
#include <string>	// tsw- for easy string use
#include <cctype>	// tsw- to check if char is letter or digit (date format)
#include "Manager.h"
using namespace std;

int getUserID();		//seperating code into smaller functions for unit testing. functionality unchanged
int managerMenu(int ID);	//seperating code into smaller functions for unit testing. functionality unchanged
int providerMenu(int ID);	//seperating code into smaller functions for unit testing. functionality unchanged

int main()
{
	int ID;		       // User's ID number, report request ID number

	// Welcome the user
	cout << "\n\tWelcome to Chocaholics Anonymous.\n";
	ID = getUserID();

	if (ID <= MAX_MANAGER)
		managerMenu(ID);
	else 
		providerMenu(ID);

	return 0;
}

int getUserID() {
	int ID;
	string user_input;		// tsw- takes user's input before conv to other type (safer)

	// Obtain a valid ID number:
	ID = -1;
	while (ID < MIN_MANAGER || ID > MAX_PROVIDER) {
		cout << "\nPlease enter your nine digit I.D. number.\n";
		cout << "$";
		cin >> user_input;
		cin.ignore(INPUT_BUFFER, '\n');
		try {
			ID = stoi(user_input);
		}
		catch (const invalid_argument& e) {
			cout << "Input was invalid.\n";
			ID = -1;
		}
		catch (const out_of_range& e) {
			cout << "\nInput is out of int's range.\n";
			ID = -1;
		}
		if (ID < MIN_MANAGER || ID > MAX_PROVIDER)
			cout << "\nInput is not a valid ID number.\n";
	}
	return ID;
}

int managerMenu(int ID) {
	int repID;
	char choice;                // User's menu selection
	string user_input;
	Manager* CurrentManager = new Manager(ID);
	cout << "\nMANAGER TERMINAL: ACCESS GRANTED\n\n";
	do {
		cout << "You can:\n";
		cout << "\tGenerate a member report\t(Enter 'M')\n";
		cout << "\tGenerate a provider report\t(Enter 'P')\n";
		cout << "\tGenerate a summary report\t(Enter 'S')\n";
		cout << "\tEnter Interactive Mode\t\t(Enter 'I')\n";
		cout << "\tExit the terminal\t\t(Enter 'X')\n";
		cout << "$";

		do {
			//make sure its len = 1
			do {
				cin >> user_input;
				cin.ignore(INPUT_BUFFER, '\n');
				if (strlen(user_input.c_str()) != 1) {
					cout << "Input is not 1 char in length (and it should be)\n";
				}
			} while (strlen(user_input.c_str()) != 1);
			choice = toupper(user_input[0]);
			//make sure its one of the valid choices
			if (choice != 'M' && choice != 'P'
				&& choice != 'S' && choice != 'I' && choice != 'X') {
				cout << "Please select from the above options.\n";
			}
		} while (choice != 'M' && choice != 'P'
			&& choice != 'S' && choice != 'I' && choice != 'X');

		if (choice == 'M') {    // Member report
			// Obtain a valid member ID number:
			repID = -1;
			while (repID <= MAX_PROVIDER || ID > MAX_ID) {
				cout << "\nPlease enter the member's nine digit I.D. number.\n";
				cin >> user_input;
				cin.ignore(INPUT_BUFFER, '\n');
				try {
					repID = stoi(user_input);
				}
				catch (const invalid_argument& e) {
					cout << "Invalid input\n";
					repID = -1;
				}
				catch (const out_of_range& e) {
					cout << "\nInput is out of int's range.\n";
					repID = -1;
				}
				if (repID <= MAX_PROVIDER || ID > MAX_ID)
					cout << "\nInput is not a valid member ID number.\n";
			}
			Member* subject = new Member(repID);
			if (!subject->Write_Report(repID))
				cout << "\nFailed to generate member report\n";
			// todo output report to file
			delete[] subject;
		}
		if (choice == 'P') {    // Provider report
			// Obtain a valid provider ID number:
			repID = -1;
			while (repID <= MAX_MANAGER || ID > MAX_PROVIDER) {
				cout << "\nPlease enter the provider's nine digit I.D. number.\n";
				cin >> user_input;
				cin.ignore(INPUT_BUFFER, '\n');
				try {
					repID = stoi(user_input);
				}
				catch (const invalid_argument& e) {
					cout << "Invalid input\n";
					repID = -1;
				}
				catch (const out_of_range& e) {
					cout << "\nInput is out of int's range.\n";
					repID = -1;
				}
				if (repID <= MAX_MANAGER || ID > MAX_PROVIDER)
					cout << "\nInput is not a valid provider ID number.\n";
			}
			Provider* subject = new Provider(repID);
/*
			if (!(subject->Get_Report(repID)))
				cout << "\nFailed to generate provider report\n";
*/
			subject->Write_Report(repID);
			// todo output report to file
			delete[] subject;
		}
		if (choice == 'S') {    // Summary report
		    // todo get report
			CurrentManager->Write_Report(ID);
		}
		if (choice == 'I') {    // Interactive mode
			if (CurrentManager->EnterInteractiveMode() < 0)
				cout << "\nInteractive mode not available\n";
		}
	} while (choice != 'X');

	return 0;
}

int providerMenu(int ID) {
	char choice;                // User's menu selection
	string user_input;			// tsw- takes user's input before conv to other type (safer)
	int err;

	Provider* CurrentProvider = new Provider(ID);
	cout << "\nPROVIDER TERMINAL: ACCESS GRANTED\n\n";
	do {
		// Display the menu:
		cout << "You can:\n";
		cout << "\tCheck in a member\t\t\t(Enter 'M')\n";
		cout << "\tLog a service\t\t\t\t(Enter 'S')\n";
		cout << "\tView the provider directory\t\t(Enter 'D')\n";
		cout << "\tGenerate your report\t\t\t(Enter 'R')\n";
		cout << "\tExit the terminal\t\t\t(Enter 'X')\n";
		cout << "$";
		
		// Get the user's choice & Validate the user's choice:
		// tsw- sanitizing so inputs > 1 char len will be rejected 
		// and wont accept just first char as input
		do {
			//make sure its len = 1
			do {
				cin >> user_input;
				cin.ignore(INPUT_BUFFER, '\n');
				if (strlen(user_input.c_str()) != 1) {
					cout << "Input is not 1 char in length (and it should be)\n";
				}
			} while (strlen(user_input.c_str()) != 1);
			choice = toupper(user_input[0]);
			//make sure its one of the valid choices
			if (choice != 'M' && choice != 'S'
				&& choice != 'D' && choice != 'X' && choice != 'R') {
				cout << "Please select from the above options.\n";
				cout << "$";
			}
		} while (choice != 'M' && choice != 'S'
			&& choice != 'D' && choice != 'X');

		// Call the appropriate function:
		if (choice == 'M') {    // Check in a member
			err = CurrentProvider->memberID_Verify();
			//tsw- my error code. may deviate from pattern. in interest of time, goin with it  
			//becuase elsewhere wants the ret to be the ID
			if(err == -1){
			        cout << "Member is suspended or nonexistent" << endl;
			}else{
                		cout << "Member exists in database." << endl;
            		}
		}
		if (choice == 'S') {    // Log a service
			CurrentProvider->logService();
		}

		if (choice == 'R') {    // Log a service
			CurrentProvider->Write_Report(ID);
		}

		if (choice == 'D') {    // Provider directory
			CurrentProvider->displayProviderDirectory();
		}
	} while (choice != 'X');
	return 0;
}
