#ifndef OPERATOR_H
#define OPERATOR_H
// Header file for operator
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
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

//tsw- thinking that bc this is an input to an sql exec statement, it needs to stay as char*? maybe not but keeping to be safe for now
using Form = std::vector<char*>;

struct ident
{
    ident();
    ident(int ID);
    ident(std::string aName, int aNumber, std::string aAddress, std::string aCity, std::string aState, int aZip, bool aStatus);

	std::string name;
	int number;
	std::string address;
	std::string city;
	std::string state;
	int zip;
	bool status; //to Check if member is valid or invalid, true=active false=inactive
};

// The ServiceReport is a struct common to both Provider Reports and Member Reports.
// Both MemberReport and ProviderReport structs contain arrays of ServiceReports.
// The Summary report is a different thing and does not use a ServiceReport.

// IS THIS FIELD USED IN THE:  MemberReport // ProviderReport
struct ServiceReport {			//      ?       //      ?
    int serviceCode;			//      NO      //      YES
    std::string memberName;     //      NO      //      YES
    int memberNumber;			//      NO      //      YES
    std::string providerName;   //      YES     //      NO
    int providerNumber;			//      YES     //      NO
    std::string dateProvided;   //      YES     //      YES
    std::string dateLogged;     //      NO      //      YES
    float fee;					//      NO      //      YES
};
using ServRep = std::vector<ServiceReport*>;

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
	Operator(int id_num);
	Operator(std::string aName, int aNumber, std::string aAddress, std::string aCity, std::string aState, int aZip, bool aStatus);
	Operator(ident To_Add);
	Operator(Operator& To_Add);
	~Operator();

	//Get functions
	std::string getName();
	int displayID(int IDnumber);    // Used to be "Display_Member()". Renamed since it displays ID of mgr, prov etc.
	int GetIDnumber();
	std::string getAddress();
	std::string getCity();
	std::string getState();
	int getZip();

	// calls to the db
	int AddService();

protected:
	ident get_ident(int IDnumber);

	ident ID;
};

#endif
