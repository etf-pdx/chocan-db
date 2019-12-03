// Main interface for the program

/*
 * To compile in VS 2019
 * Open directory in developer command prompt
 * run "cl /EHsc .\sqlite\sqlite3.c *.cpp /Fe.\ChocAnDB.exe"
 */

#include <cctype>
#include <iostream>
#include <time.h>
#include "ChocAnDB.h"
using namespace std;

// These functions will call
int checkInMember();                // @ Provider terminal
int logService(int provID);         // @ Provider terminal
int validateMemberID(int memID);    // Return status of member ID
void displayProviderDirectory();    // Services, service codes and fees
bool yesorno();                     // Obtain valid response to yes/no question

int main()
{
    int ID;                     // User's ID number
    bool mgr = false;           // True if user is a manager
    char choice;                 // User's menu selection

    // Welcome the user
    cout << "\n\tWelcome to Chocaholics Anonymous.\n";

    // Obtain a valid ID number:
    cout << "\nPlease enter your nine digit I.D. number.\n";
    do {
        // TODO: Fix integer wraparound bug. Infinite loop occurs when ID > 2147483647
        cin >> ID;
        cin.ignore(100, '\n');
        if (ID < MIN_MANAGER || ID > MAX_PROVIDER)
            cout << "\nInvalid.\nPlease enter a valid nine digit I.D. number\n";
    } while (ID < MIN_MANAGER || ID > MAX_PROVIDER);

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
                if (!logService(ID)) continue;
            }
            if (choice == 'D') {    // Provider directory
                displayProviderDirectory();
            }
        } while (choice != 'X');
    }

    //  SIMULATE MANAGER TERMINAL   //
    else
    {
        //TODO: Make this shit work
        //Manager* CurrentManager = new Manager();
        cout <<"\nMANAGER TERMINAL: ACCESS GRANTED\n\n";
        do {
            cout << "You can:\n";
            cout << "\tGenerate a member report\t(Enter 'M')\n";
            cout << "\tGenerate a provider report\t(Enter 'P')\n";
            cout << "\tGenerate a summary report\t(Enter 'S')\n";
            cout << "\tEnter Interactive Mode\t\t(Enter 'I')\n";
            cout << "\tExit the terminal\t\t\t(Enter 'X')\n";

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
                //TODO: Make this shit work
                //if (!CurrentManager->InteractiveMode())
                    cout << "\nInteractive mode not available\n";
            }

        } while (choice != 'X');
    }

	return 0;
}

// Return the response to a yes or no question.
bool yesorno() {
    char response;

    cin >>response;
    cin.ignore(100, '\n');
    response = toupper(response);

    while (response != 'Y' && response != 'N') {
        cout <<"\nLooking for a 'Y' or 'N' here...\n";
        cin >>response;
        cin.ignore(100, '\n');
        response = toupper(response);
    }

    return response == 'Y';
}

// checkInMember() obtains a member ID via user input.
// It returns the valid member I.D. number.
// It returns 0 if the number is invalid
// or if the member is inactive or suspended,
// communicating member status to the user.
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
    memCheck = validateMemberID(memID);
// TODO: Implement int validateMemberID(int memID). Return: -1==invalid, 0==suspended, memberID==valid
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
    char* serviceDate = NULL;
    char* serviceName = NULL;
    char* comments = NULL;
    float fee = 0.0;

    memberID = checkInMember();
    if (!memberID)
        return 0;

// Get the service date:
    cout << "Please enter the date the service was provided (MM-DD-YYYY)\n";
    cin.get(serviceDate, 100, '\n');
    cin.ignore(100, '\n');

// Get the service code:
    do {
        cout << "\nPlease enter the six digit service code.\n";
        cin >> serviceCode;
        cin.ignore(100, '\n');

        // Verify the service code:
        while (serviceCode < 0 || serviceCode > MAX_SERVICE) {
            cout << "\nInvalid.\nPlease enter a valid six digit service code.\n";
            cin >> serviceCode;
            cin.ignore(100, '\n');
        }
        // TODO: Search provider directory for matching service name
        //Carl - I am not user search by name is required functionality.

        // Confirm the service is correct:
        cout << "\nYou entered " << serviceCode << ": " << serviceName << endl;
        cout << "\nIs that correct? Y/N\n";
    } while (!yesorno());

// Get comments:
    cout << "\nWould you like to record comments on this service? Y/N\n";
    if (yesorno()) {
        cout << "\nEnter your comments (" << MAX_COMMENT - 1 << " characters max)\n";
        cin.get(comments, MAX_COMMENT, '\n');
        cin.ignore(100, '\n');
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

int validateMemberID(int memID) {

    return 0;
// TODO: Implement int validateMemberID(int memID). Return: -1==invalid, 0==suspended, 1==valid
}

void displayProviderDirectory() {
// TODO: Implement provider directory: service names, service codes, fees
}

