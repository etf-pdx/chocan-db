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

        //trent- need to rm all "continues" that exist outside for/while loop
        // if service object already exists and we are copying it, do we need these checks?
        // or would the checks already have happened when the existing object set each if its own data mems
        // if we decide we need, then i think only way to catch failed copy constructor is to throw an exception
 
//	if (service_code < MAX_SERVICE)
//		continue;

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
//	if (memberID < MAX_ID && provider_ID < MAX_ID)
//		continue;

	service_fee = fee;
//	if (service_fee < MAX_FEE)
//		continue;

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
	std::cout << "Service Name: " << service_name << std::endl;
	std::cout << "Service ID: " << service_code << std::endl;
	std::cout << "Date Provided: " << provided_date << std::endl;
	std::cout << "Date Logged: " << logged_date << std::endl;
	std::cout << "Member ID: " << memberID << std::endl;
	std::cout << "Provider ID: " << providerID << std::endl;
	std::cout << "Fee: " << service_fee << std::endl;
	std::cout << "Comments: " << comments << std::endl;

	return 0;
}
