// Main interface for the program

/*
 * To compile in VS 2019
 * Open directory in developer command prompt
 * run "cl /EHsc .\sqlite\sqlite3.c *.cpp"
 */


#include "ChocAnDB.h"
//#include "Manager.h"
//#include "Operator.h"
//#include "Service.h"
#include <iostream>
using namespace std;

const int LOW_MGR = 100000000;  // Lower bound for manager ID numbers
const int UPP_MGR = 199999999;  // Upper bound for manager ID numbers

// We may want to consolidate constant definitions like these^^
// and the ones in Service.h into a "params.h" header file...



int main()
{
    int ID;
    bool mgr = false;   // True if user is a manager
    ChocAnDB database;

    cout <<"\n\tWelcome to Chocaholics Anonymous.\n";
    cout <<"\nPlease enter your nine digit I.D. number.\n";
    cin >>ID;
    cin.ignore(100, '\n');

    while (ID < LOW_MGR || ID > MAX_ID) {
        cout <<"\nInvalid I.D. number\n";
        cin >>ID;
        cin.ignore(100, '\n');
    }

    if (ID <= UPP_MGR)
        mgr = true;

    //  SIMULATE PROVIDER TERMINAL  //
    if (!mgr)
    {
        // OPTION: Check in a member
        // OPTION: Log a service
        // OPTION: Request provider directory
    }

    //  SIMULATE MANAGER TERMINAL   //
    else
    {
        // OPTION: request member report
        // OPTION: request provider report
        // OPTION: request summary report
        // if (!daytime) // (interactive mode)
            //OPTIONS: add/edit/retrieve/remove/display
                    // member/provider/service/manager
    }

	return 0;
}