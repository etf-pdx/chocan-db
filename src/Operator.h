// Header file for operator
#include <iostream>
#include "Definition.h"

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



struct ident
{
	char *name;
	int number;
	char *address;
	char *city;
	char *state;
	int zip;
	bool status; //to Check if memeber is valid or invalid, true=active false=inactive
};

class Operator
{
public:
	Operator();
	Operator(char* aName, int aNumber, char* aAddress, char* aCity, char* aState, int aZip);
	Operator(ident To_Add);
	Operator(Operator& To_Add);
	~Operator();

	//Get functions
	char* getName();
	int displayID(int IDnumber);    // Used to be "Display_Member()". Renamed since it displays ID of mgr, prov etc.
	int GetIDnumber();
	char* getAddress();
	char* getCity();
	char* getState();
	int getZip();

	
	int AddUser(Operator*& root, Operator* To_Add);

protected:
	ident get_ident(int IDnumber);

	ident ID;
};