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
#include "Manager.h"
using namespace std;

int checkInMember(const Provider & currProv);   // @ Provider terminal
int logService(Provider & currProv);            // @ Provider terminal
void displayProviderDirectory();                // Services, service codes and fees
bool yesorno();                                 // Obtain valid response to yes/no question
bool dateFormatCheck(string input_date);        //make sure user inputs a well formatted date
int getUserID();								//seperating code into smaller functions for unit testing. functionality unchanged
int managerMenu(int ID);						//seperating code into smaller functions for unit testing. functionality unchanged
int providerMenu(int ID);						//seperating code into smaller functions for unit testing. functionality unchanged

int main()
{
	int ID;		                // User's ID number, report request ID number

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
	string user_input;			// tsw- takes user's input before conv to other type (safer)

	// Obtain a valid ID number:
	ID = -1;
	while (ID < MIN_MANAGER || ID > MAX_PROVIDER) {
		cout << "\nPlease enter your nine digit I.D. number.\n";
		cin >> user_input;
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
				catch (invalid_argument e) {
					cout << "Invalid input\n";
					repID = -1;
				}
				catch (out_of_range e) {
					cout << "\nInput is out of int's range.\n";
					repID = -1;
				}
				if (repID <= MAX_PROVIDER || ID > MAX_ID)
					cout << "\nInput is not a valid member ID number.\n";
			}
			Member* subject = new Member(repID);
			if (!subject->Get_Report(repID))
				cout << "\nFailed to generate member report\n";
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
				catch (invalid_argument e) {
					cout << "Invalid input\n";
					repID = -1;
				}
				catch (out_of_range e) {
					cout << "\nInput is out of int's range.\n";
					repID = -1;
				}
				if (repID <= MAX_MANAGER || ID > MAX_PROVIDER)
					cout << "\nInput is not a valid provider ID number.\n";
			}
			Provider* subject = new Provider(repID);
			if (!subject->Get_Report(repID))
				cout << "\nFailed to generate provider report\n";
		}
		if (choice == 'S') {    // Summary report
			// TODO: Fetch, display, write summary report
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

	Provider* CurrentProvider = new Provider(ID);
	cout << "\nPROVIDER TERMINAL: ACCESS GRANTED\n\n";
	do {
		// Display the menu:
		cout << "You can:\n";
		cout << "\tCheck in a member\t\t\t(Enter 'M')\n";
		cout << "\tLog a service\t\t\t\t(Enter 'S')\n";
		cout << "\tView the provider directory\t(Enter 'D')\n";
		cout << "\tExit the terminal\t\t\t(Enter 'X')\n";

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
			if (!checkInMember(*CurrentProvider)) continue;
		}
		if (choice == 'S') {    // Log a service
			cout << "Placeholder.. S selected.\n";
			if (!logService(*CurrentProvider)) continue;
		}
		if (choice == 'D') {    // Provider directory
			cout << "Placeholder.. D selected.\n";
			CurrentProvider->displayProviderDirectory();
		}
	} while (choice != 'X');
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
int checkInMember(const Provider & currProv) {
	int ID, memCheck;
	string user_input;

	// Get the member's ID:
	do {
		ID = -1;
		//tsw- not sure on what the correct mem id range is. will circle back.
		// AS - Member IDs are 300000000 - 999999999. See Definition.h, Operator.h
		while (ID <= MAX_PROVIDER || ID > MAX_ID) {     // MAX_PROVIDER == 299999999; MAX_ID == 999999999
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
			if (ID <= MAX_PROVIDER || ID > MAX_ID) {
				cout << "\nInput is not a valid member ID number.\n";
			}
			else {
				//valid input
				cout << "\nYou entered " << ID << ". Is that correct? Y/N\n";
			}
		}
	} while (!yesorno());
	// Validate the member's ID:
	cout << "\nContacting Chocaholics Anonymous...\n";
	memCheck = currProv.validateMemberID(ID);

	// TODO: Implement int Provider::validateMemberID(int memID) in User.cpp
		//tsw- possibly something like- db.verifyMemberExists(ID);
		// AS- Hoping to insulate main from db. Thinking provider.validateMID(int ID), which calls db.verifyMID(ID)
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
int logService(Provider & currProv) {
	int memberID = 0;
	int serviceCode = 0;
	string serviceDate, user_input;
	char* serviceName = NULL;
	string comments;
	float fee = 0.0;

	memberID = checkInMember(currProv);
	if (memberID <= 0)
		return 0;

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
                // TODO: Search provider directory for matching service name
                //Carl - I am not user search by name is required functionality.
                // AS - I meant search by number and get a name returned

				//tsw-name commented out until functionality is active
				//otherwise it will throw an exception
				cout << "\nYou entered " << serviceCode << ": " << /*serviceName << */ endl;
				cout << "\nIs that correct? Y/N\n";
			}
		}
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
//int validateMemberID(int memID) {

	//return 0;
	// TODO: Implement int validateMemberID(int memID). Return: -1==invalid, 0==suspended, 1==valid
//}

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