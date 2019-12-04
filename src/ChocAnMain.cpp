// Main interface for the program

/*
 * To compile in VS 2019
 * Open directory in developer command prompt
 * run "cl /EHsc .\sqlite\sqlite3.c *.cpp /Fe.\ChocAnDB.exe"
 */

#include <cctype>
#include <iostream>
#include <time.h>
#include <string>					// tsw- for easy string use
#include <cctype>					// tsw- to check if char is letter or digit (date format)
 //#include "ChocAnDB.h"
#include "Manager.h"
using namespace std;

int checkInMember();                // @ Provider terminal
int logService(int provID);         // @ Provider terminal
//tsw- thinking this could be good functionality to reside in db class
int validateMemberID(int memID);    // Return status of member ID
void displayProviderDirectory();    // Services, service codes and fees
bool yesorno();                     // Obtain valid response to yes/no question
bool dateFormatCheck(string input_date); //make sure user inputs a well formatted date

int main()
{
	int ID;                     // User's ID number
	bool mgr = false;           // True if user is a manager
	char choice;                // User's menu selection
	string user_input;			// tsw- takes user's input before conv to other type (safer)
	//ChocAnDB db;				// tsw- the db obj 

	// Welcome the user
	cout << "\n\tWelcome to Chocaholics Anonymous.\n";

	// Obtain a valid ID number:
	ID = -1;
	while (ID < MIN_MANAGER || ID > MAX_PROVIDER) {
		cout << "\nPlease enter your nine digit I.D. number.\n";
		// tsw- int wraparound bug fixed
		cin >> user_input;
		// tsw- whats this do? ignore 100 chars of user input?
		cin.ignore(INPUT_BUFFER, '\n');
		try {
			ID = stoi(user_input);
		}
		catch (invalid_argument e) {
			cout << "Input was invalid.\n";
			ID = -1;
		}
		catch (out_of_range e) {
			cout << "\nInput is out of int's range.\n";
			ID = -1;
		}
		if (ID < MIN_MANAGER || ID > MAX_PROVIDER)
			cout << "\nInput is not a valid ID number.\n";
	}

	if (ID <= MAX_MANAGER) {
		mgr = true;
		//Manager current_manager;
	}

	//  SIMULATE PROVIDER TERMINAL  //
	if (!mgr)
	{
		cout << "\nPROVIDER TERMINAL: ACCESS GRANTED\n\n";
		do {
			// Display the menu:
			cout << "You can:\n";
			cout << "\tCheck in a member\t\t(Enter 'M')\n";
			cout << "\tLog a service\t\t\t(Enter 'S')\n";
			cout << "\tView the provider directory\t(Enter 'D')\n";
			cout << "\tExit the terminal\t\t(Enter 'X')\n";

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
					&& choice != 'D' && choice != 'X') {
					cout << "Please select from the above options.\n";
				}
			} while (choice != 'M' && choice != 'S'
				&& choice != 'D' && choice != 'X');

			// Call the appropriate function:
			if (choice == 'M') {    // Check in a member
				cout << "Placeholder.. M selected.\n";
				if (!checkInMember()) continue;
			}
			if (choice == 'S') {    // Log a service
				cout << "Placeholder.. S selected.\n";
				if (!logService(ID)) continue;
			}
			if (choice == 'D') {    // Provider directory
				cout << "Placeholder.. D selected.\n";
				displayProviderDirectory();
			}
		} while (choice != 'X');
	}
	//  SIMULATE MANAGER TERMINAL   //
	else
	{
		//TODO: Make this shit work
		Manager* CurrentManager = new Manager();
		cout << "\nMANAGER TERMINAL: ACCESS GRANTED\n\n";
		do {
			cout << "You can:\n";
			cout << "\tGenerate a member report\t(Enter 'M')\n";
			cout << "\tGenerate a provider report\t(Enter 'P')\n";
			cout << "\tGenerate a summary report\t(Enter 'S')\n";
			cout << "\tEnter Interactive Mode\t\t(Enter 'I')\n";
			cout << "\tExit the terminal\t\t\t(Enter 'X')\n";

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
					&& choice != 'S' && choice != 'I') {
					cout << "Please select from the above options.\n";
				}
			} while (choice != 'M' && choice != 'P'
				&& choice != 'S' && choice != 'I' && choice != 'X');

			if (choice == 'M') {    // Member report
			}
			if (choice == 'P') {    // Provider report
			}
			if (choice == 'S') {    // Summary report
			}
			if (choice == 'I') {    // Interactive mode
				//TODO: Make this shit work
				if (CurrentManager->EnterInteractiveMode() < 0)
					cout << "\nInteractive mode not available\n";
			}
		} while (choice != 'X');
	}
	return 0;
}

// Return the response to a yes or no question.
bool yesorno() {
	char choice;
	string user_input;

	do {
		//make sure its len = 1
		do {
			cin >> user_input;
			cin.ignore(INPUT_BUFFER, '\n');
			if (strlen(user_input.c_str()) != 1) {
				cout << "\nLooking for a 'Y' or 'N' here...\n";
			}
		} while (strlen(user_input.c_str()) != 1);
		choice = toupper(user_input[0]);
		//make sure its one of the valid choices
		if (choice != 'Y' && choice != 'N') {
			cout << "\nLooking for a 'Y' or 'N' here...\n";
		}
	} while (choice != 'Y' && choice != 'N');

	return choice == 'Y';
}

// checkInMember() obtains a member ID via user input.
// It returns the valid member I.D. number.
// It returns 0 if the number is invalid
// or if the member is inactive or suspended,
// communicating member status to the user.
int checkInMember() {
	int ID, memCheck;
	string user_input;

	// Get the member's ID:
	do {
		ID = -1;
		//tsw- not sure on what the correct mem id range is. will circle back.
		while (ID < 0 || ID > MAX_ID) {
			cout << "\nPlease enter the ChocAn member's nine digit ID number:\n";
			// tsw- protecting against bad input like mgr/prvdr ID input above
			// (not checking for a mem id that doesn't exist in db. thats below/later)
			cin >> user_input;
			cin.ignore(INPUT_BUFFER, '\n');
			try {
				ID = stoi(user_input);
			}
			catch (invalid_argument e) {
				cout << "Input is not a number.\n";
				ID = -1;
			}
			catch (out_of_range e) {
				cout << "\nInput is out of int's range.\n";
				ID = -1;
			}
			if (ID < 0 || ID > MAX_ID) {
				cout << "\nInput is not a valid ID number.\n";
			}
			else {
				//valid input
				cout << "\nYou entered " << ID << ". Is that correct? Y/N\n";
			}
		}
	} while (!yesorno());
	// Validate the member's ID:
	cout << "\nContacting Chocaholics Anonymous...\n";
	memCheck = validateMemberID(ID);

	// TODO: Implement int validateMemberID(int memID). Return: -1==invalid, 0==suspended, memberID==valid
		//tsw- possibly something like- db.verifyMemberExists(ID);
	if (memCheck < 0) {
		cout << "\nInvalid Member ID\n";
		return 0;
	}
	if (memCheck == 0) {
		cout << "\nMember suspended\n";
		return 0;
	}
	cout << "\nValidated\n";
	return memCheck;
}

// logService() obtains the necessary info to
// log a service from the provider terminal.
// It returns 0 on failure, 1 on success.
// TODO: Implement the provider directory to finish this function!
int logService(int provID) {
	int memberID = 0;
	int serviceCode = 0;
	string serviceDate, user_input;
	char* serviceName = NULL;
	string comments;
	float fee = 0.0;

	/* tsw- commented out just until checkInMember works so we can
	   get past this and test the rest of the func
	memberID = checkInMember();
	if (!memberID)
		return 0;
	*/
	// Get the service date:
	do {
		cout << "Please enter the date the service was provided (MM-DD-YYYY)\n";
		cin >> serviceDate;
		cin.ignore(INPUT_BUFFER, '\n');
		if (!dateFormatCheck(serviceDate)) {
			cout << "Input is not in correct format. \n";
		}
	} while (!dateFormatCheck(serviceDate));

	// Get the service code:
	do {
		serviceCode = -1;
		while (serviceCode < 0 || serviceCode > MAX_SERVICE) {
			cout << "\nPlease enter the six digit service code.\n";
			cin >> user_input;
			cin.ignore(INPUT_BUFFER, '\n');
			try {
				serviceCode = stoi(user_input);
			}
			catch (invalid_argument e) {
				cout << "Input is not a number.\n";
				serviceCode = -1;
			}
			catch (out_of_range e) {
				cout << "\nInput is out of int's range.\n";
				serviceCode = -1;
			}
			if (serviceCode < 0 || serviceCode > MAX_SERVICE) {
				cout << "\nInvalid.\nPlease enter a valid six digit service code.\n";
			}
			else {
				// Confirm the service is correct:
				//tsw-name commented out until functionality is active
				//otherwise it will throw an exception
				cout << "\nYou entered " << serviceCode << ": " << /*serviceName << */ endl;
				cout << "\nIs that correct? Y/N\n";
			}
		}
		// TODO: Search provider directory for matching service name
		//Carl - I am not user search by name is required functionality.
	} while (!yesorno());

	// Get comments:
	cout << "\nWould you like to record comments on this service? Y/N\n";
	if (yesorno()) {
		do {
			cout << "\nEnter your comments (" << MAX_COMMENT - 1 << " characters max)\n";
			cin >> comments;
			cin.ignore(INPUT_BUFFER, '\n');
			if (strlen(comments.c_str()) > MAX_COMMENT - 1) {
				cout << "Comment too long.\n";
			}
		} while (strlen(comments.c_str()) > MAX_COMMENT - 1);
	}

	// Record service:
	char* logDate = NULL;
	//getdate(logDate);   // test this...
/*
	Service consultation = new Service(serviceName, serviceCode, serviceDate,
									  logDate, memberID, provID, fee, comments);
*/

// Display fee (from provider directory):

	return 1;
}

//tsw- thinking this could be good functionality to belong inside db class
int validateMemberID(int memID) {

	return 0;
	// TODO: Implement int validateMemberID(int memID). Return: -1==invalid, 0==suspended, 1==valid
}

void displayProviderDirectory() {
	// TODO: Implement provider directory: service names, service codes, fees
}

//tsw- make sure user inputs a well formatted date
//edge cases left unchecked- wont prevent 31 days in jan for example
bool dateFormatCheck(string input_date) {
	//month check
	if (strlen(input_date.c_str()) != 10)	return false;
	if (!isdigit(input_date[0]))			return false;
	if (!isdigit(input_date[1]))			return false;
	if (stoi(input_date.substr(0, 2)) < 1 ||
		stoi(input_date.substr(0, 2)) > 12)return false;
	if (input_date[2] != '-')				return false;
	//day check
	if (!isdigit(input_date[3]))			return false;
	if (!isdigit(input_date[4]))			return false;
	if (stoi(input_date.substr(3, 2)) < 1 ||
		stoi(input_date.substr(3, 2)) > 31)return false;
	if (input_date[5] != '-')				return false;
	//year check
	if (!isdigit(input_date[6]))			return false;
	if (!isdigit(input_date[7]))			return false;
	if (!isdigit(input_date[8]))			return false;
	if (!isdigit(input_date[9]))			return false;
	if (stoi(input_date.substr(6, 4)) < 1 ||
		stoi(input_date.substr(6, 4)) > 2019)return false;

	return true;
}