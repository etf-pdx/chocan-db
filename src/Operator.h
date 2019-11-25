// Header file for operator
#include <iostream>

// ************************************************ //
//              RULES FOR I.D. NUMBERS              //
// ************************************************ //
//                                                  //
//  1. All I.D. numbers are 9 digits.               //
//  2. No I.D. number begins with 0.                //
//  3. Manager I.D. numbers begin with 1.           //
//  4. Provider I.D. numbers begin with 2.          //
//  5. All other I.D. numbers belong to members.    //
//                                                  //
// ************************************************ //

const int MIN_MANAGER = 100000000;  // Lower bound for manager ID numbers
const int MAX_MANAGER = 199999999;  // Upper bound for manager ID numbers
const int MAX_PROVIDER = 299999999;  // Upper bound for provider ID numbers

struct ident
{
	char *name;
	int number;
	char *address;
	char *city;
	char *state;
	int zip;
};

class Operator
{
public:
	Operator();
	~Operator();
	int displayID(int IDnumber);    // Used to be "Display_Member()". Renamed since it displays ID of mgr, prov etc.
	int GetIDnumber();
	int HashFormula(int IDnumber);

protected:
	ident get_ident(int IDnumber);

	ident ID;
};