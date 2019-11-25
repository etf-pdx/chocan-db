// Main interface for the program

/*
 * To compile in VS 2019
 * Open directory in developer command prompt
 * run "cl /EHsc .\sqlite\sqlite3.c *.cpp"
 */


#include "ChocAnDB.h"
#include <iostream>
using namespace std;

// Manager ID#s begin with 1
// Provider ID#s begin with 2
// All other ID#s belong to members
// No ID # begins with 0.

const int LOW_MGR = 100000000;  // Lower bound for manager ID numbers
const int UPP_MGR = 199999999;  // Upper bound for manager ID numbers
const int UPP_PRV = 299999999;  // Upper bound for provider ID numbers

// We may want to consolidate constant definitions like these^^
// and the ones in Service.h into a "params.h" header file...

int checkInMember();    // @ Provider terminal
int logService();       // @ Provider terminal
bool yesorno();         // Obtain valid response to yes/no question

int main()
{
    int ID;                     // User's ID number
    bool mgr = false;           // True if user is a manager
    char choice;                 // User's menu selection

    // Welcome the user:
    cout << "\n\tWelcome to Chocaholics Anonymous.\n";
    cout << "\nPlease enter your nine digit I.D. number.\n";
    cin >> ID;
    cin.ignore(100, '\n');

    // Ensure valid ID number:
    while (ID < LOW_MGR || ID > UPP_PRV) {
        cout << "\nInvalid.\nPlease enter a valid nine digit I.D. number\n";
        cin >> ID;
        cin.ignore(100, '\n');
    }

    if (ID <= UPP_MGR)
        mgr = true;

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

            // Get the user's choice:
            cin >> choice;
            cin.ignore(100, '\n');
            choice = toupper(choice);

            // Validate the user's choice:
            while (choice != 'M' && choice != 'S'
                    && choice != 'D' && choice != 'X') {
                cout << "\nPlease select from the above options.\n";
                cin >> choice;
                cin.ignore(100, '\n');
                choice = toupper(choice);
            }

            // Call the appropriate function:
            if (choice == 'M') {    // Check in a member
                if (!checkInMember()) continue;
            }
            if (choice == 'S') {    // Log a service
                if (!logService()) continue;
            }
            if (choice == 'D') {    // Provider directory
            }

        } while (choice != 'X');
    }

    //  SIMULATE MANAGER TERMINAL   //
    else
    {
        cout <<"\nMANAGER TERMINAL: ACCESS GRANTED\n\n";
        do {
            cout << "You can:\n";
            cout << "\tGenerate a member report\t(Enter 'M')\n";
            cout << "\tGenerate a provider report\t(Enter 'P')\n";
            cout << "\tGenerate a summary report\t(Enter 'S')\n";
            cout << "\tEnter Interactive Mode\t\t(Enter 'I')\n";
            cout << "\tExit the terminal\t\t(Enter 'X')\n";

            cin >> choice;
            cin.ignore(100, '\n');
            choice = toupper(choice);

            while (choice != 'M' && choice != 'P' && choice != 'S'
                   && choice != 'I' && choice != 'X') {
                cout << "\nPlease select from the above options.\n";
                cin >> choice;
                cin.ignore(100, '\n');
                choice = toupper(choice);
            }

            if (choice == 'M') {    // Member report
            }
            if (choice == 'P') {    // Provider report
            }
            if (choice == 'S') {    // Summary report
            }
            if (choice == 'I') {    // Interactive mode
                //OPTIONS: add/edit/retrieve/remove/display
                // member/provider/service/manager
            }

        } while (choice != 'X');
    }

	return 0;
}

bool yesorno() {
    int response;

    cin >>response;
    cin.ignore(100, '\n');
    response = toupper(response);

    while (response != 'Y' && response != 'N') {
        cout <<"\nLooking for a 'Y' or 'N' here...\n";
        cin >>response;
        cin.ignore(100, '\n');
        response = toupper(response);
    }

    if (response == 'Y')
        return true;
    return false;
}

int checkInMember() {
    int memID, memCheck;

// Get the member's ID:
    do {
        cout << "\nEnter the ChocAn member's nine digit ID number:\n";
        cin >> memID;
        cin.ignore(100, '\n');
        cout << "\nYou entered " << memID << ". Is that correct? Y/N\n";
    } while (!yesorno());

// Validate the member's ID:
    cout << "\nContacting Chocaholics Anonymous...\n";
	memCheck = 1; // validateMemberID(memID);
// TODO: Implement int validateMemberID(int memID). Return: -1==invalid, 0==suspended, 1==valid
    if (memCheck < 0) {
        cout << "\nInvalid Member ID\n";
        return 0;
    }
    if (memCheck == 0) {
        cout << "\nMember suspended\n";
        return 0;
    }
    cout << "\nValidated\n";
    return 1;
}

int logService() {
    char serviceDate[MAX_DATE];
    int serviceCode;

    if (!checkInMember())
        return 0;

// Get the service date:
    cout << "Please enter the date the service was provided (MM-DD-YYYY)\n";
    cin.get(serviceDate, 100, '\n');
    cin.ignore(100, '\n');

// Get the service code:
    cout << "\nRetrieving provider directory...\n\n";
    //displayProviderDirectory();
// TODO: Implement provider directory
    cout << "\nPlease enter the six digit service code.\n";
    cin >> serviceCode;
    cin.ignore(100, '\n');

// Verify service code:
// Get comments:
// Record service:
// Display fee:

    return 1;
}
