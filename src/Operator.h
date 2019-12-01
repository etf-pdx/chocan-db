// Header file for operator
#include <iostream>
#include <cstring>
#include "Service.h"
#include <vector>

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


using Form = std::vector<char*>;

struct ident
{
    ident();
    ident(char* aName, int aNumber, char* aAddress, char* aCity, char* aState, int aZip, bool aStatus);

	char *name;
	int number;
	char *address;
	char *city;
	char *state;
	int zip;
	bool status; //to Check if member is valid or invalid, true=active false=inactive
};

// The ServiceReport is a struct common to both Provider Reports and Member Reports.
// Both MemberReport and ProviderReport structs contain arrays of ServiceReports.
// The Summary report is a different thing and does not use a ServiceReport.

// IS THIS FIELD USED IN THE:  MemberReport // ProviderReport
struct ServiceReport {      //      ?       //      ?
    int serviceCode;        //      NO      //      YES
    char* memberName;       //      NO      //      YES
    int memberNumber;       //      NO      //      YES
    char* providerName;     //      YES     //      NO
    int providerNumber;     //      YES     //      NO
    char* dateProvided;     //      YES     //      YES
    char* dateLogged;       //      NO      //      YES
    float fee;              //      NO      //      YES
};

struct MemberReport {
    ident memberID;
    ServiceReport* servicesReceived;    // Array of services member received that week
};

struct ProviderReport {
    ident providerID;
    ServiceReport* servicesProvided;    // Array of services provider logged that week
    int numServices;
    float totalFee;
};

// The SummaryReport contains an array of ProviderReports. When displayed, it will
// use this array to access the provider names, number of services and fees owed.
struct SummaryReport {
    ProviderReport* perProviderData;    // Array of providers owed for the week
    int number_of_services;
    int number_of_providers;
    int total_fee;
};


class Operator
{
public:
	Operator();
	Operator(char* aName, int aNumber, char* aAddress, char* aCity, char* aState, int aZip, bool aStatus);
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

	int AddService();

protected:
	ident get_ident(int IDnumber);

	ident ID;
};