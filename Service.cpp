#include "Service.h"

// Default Constructor
Service::Service()
{
	service_name = NULL;
	service_code = 0;
	provided_date = NULL;
	logged_date = NULL;
	memberID = 0;
	providerID = 0;
	service_fee = 0.0;
	comments = NULL;
}

// Copy Constructor
Service::Service(char* s_name, int code, char* p_date, char* l_date, int mID, int pID, float fee, char* s_comments)
{
	service_name = new char[MAX_NAME];
	strcpy(service_name, s_name);

	service_code = code;
	if (service_code < MAX_SERVICE)
		continue;

	provided_date = new char[MAX_DATE];
	strcpy(provided_date, p_date);
	/*
		Check date format here
	*/
	logged_date = new char[MAX_DATE];
	strcpy(logged_date, l_date);
	/*
		Check date format here
	*/

	memberID = mID;
	providerID = pID;
	if (memberID < MAX_ID && provider_ID < MAX_ID)
		continue;

	service_fee = fee;
	if (service_fee < MAX_FEE)
		continue;

	comments = new char[MAX_COMMENT];
	strcpy(comments, s_comments);
}

// Destructor
Service::~Service()
{
	if (service_name)
		delete [] service_name;
	if (provided_date)
		delete [] provided_date;
	if (logged_date)
		delete [] logged_date;
	if (comments)
		delete [] comments;
}

int Service::Display()
{
	cout << "Service Name: " << service_name << endl;
	cout << "Service ID: " << service_code << endl;
	cout << "Date Provided: " << provided_date << endl;
	cout << "Date Logged: " << logged_date << endl;
	cout << "Member ID: " << memberID << endl;
	cout << "Provider ID: " << providerID << endl;
	cout << "Fee: " << service_fee << endl;
	cout << "Comments: " << comments << endl;

	return 0;
}
