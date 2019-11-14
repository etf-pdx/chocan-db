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

// Copy Constructor
Service::Service(const Service& To_Add)
{
	service_name = new char[MAX_NAME];
	strcpy(service_name, To_Add.service_name);

	service_code = To_Add.service_code;
	if (service_code < MAX_SERVICE)
		continue;

	provided_date = new char[MAX_DATE];
	strcpy(provided_date, To_Add.provided_date);
	/*
		Check date format here
	*/
	logged_date = new char[MAX_DATE];
	strcpy(logged_date, To_Add.logged_date);
	/*
		Check date format here
	*/

	memberID = To_Add.memberID;
	providerID = To_Add.providerID;
	if (memberID < MAX_ID && provider_ID < MAX_ID)
		continue;

	service_fee = To_Add.service_fee;
	if (service_fee < MAX_FEE)
		continue;

	comments = new char[MAX_COMMENT];
	strcpy(comments, To_Add.comments);
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

// Display all services in the list
/*
 * If you wanna return the service to the surface first before
 * displaying, change type to Service and return it to a static
 * object
 */
int Service::Display(Service* current)
{
	if (!current)
		return 0;

	cout << "Service Name: " << current->service_name << endl;
	cout << "Service ID: " << current->service_code << endl;
	cout << "Date Provided: " << current->provided_date << endl;
	cout << "Date Logged: " << current->logged_date << endl;
	cout << "Member ID: " << current->memberID << endl;
	cout << "Provider ID: " << current->providerID << endl;
	cout << "Fee: " << current->service_fee << endl;
	cout << "Comments: " << current->comments << endl << endl;

	Display(current->next);

	return 0;
}
