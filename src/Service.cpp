#include <cstring>
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
	next = NULL;
}

// Constructor w/ Args
Service::Service(char* s_name, int code, char* p_date, char* l_date, int mID, int pID, float fee, char* s_comments) {
	service_name = new char[MAX_NAME];
    strcpy(service_name, s_name);

    if (code > MAX_SERVICE || code <= 0) {
        // Throw exception
        service_code = 0;
    } else service_code = code;

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

    if (mID > MAX_ID || mID <= 0) {
        // Throw exception
        memberID = 0;
    } else memberID = mID;

    if (pID > MAX_ID || pID <= 0) {
        // Throw exception
        providerID = 0;
    } else providerID = pID;

    if (fee > MAX_FEE || fee <= 0) {
        //Throw exception
        service_fee = 0.0;
    }
	else service_fee = fee;

	comments = new char[MAX_COMMENT];
	strcpy(comments, s_comments);

	next = NULL;
}

// Copy Constructor
Service::Service(const Service* To_Add)
{
	if (!To_Add)
		return;

	service_name = new char[MAX_NAME];
	strcpy(service_name, To_Add->service_name);

	service_code = To_Add->service_code;

	provided_date = new char[MAX_DATE];
	strcpy(provided_date, To_Add->provided_date);
	/*
		Check date format here
	*/
	logged_date = new char[MAX_DATE];
	strcpy(logged_date, To_Add->logged_date);
	/*
		Check date format here
	*/

	memberID = To_Add->memberID;
	providerID = To_Add->providerID;
	service_fee = To_Add->service_fee;

	comments = new char[MAX_COMMENT];
	strcpy(comments, To_Add->comments);

	next = NULL;
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
int Service::DisplayAll(Service* current)
{
	if (!current)
		return -1;

	current->Display();
	
	return current->DisplayAll(next);
}

int Service::Display()
{
	if (!this)
		return -1;

	std::cout << "Service Name: " << this->service_name << std::endl;
	std::cout << "Service ID: " << this->service_code << std::endl;
	std::cout << "Date Provided: " << this->provided_date << std::endl;
	std::cout << "Date Logged: " << this->logged_date << std::endl;
	std::cout << "Member ID: " << this->memberID << std::endl;
	std::cout << "Provider ID: " << this->providerID << std::endl;
	std::cout << "Fee: " << this->service_fee << std::endl;
	std::cout << "Comments: " << this->comments << std::endl << std::endl;

	return 0;
}

int Service::FindService(int sID)
{
	if (sID <= 0 || sID > MAX_SERVICE)
		return -1;

	Service* holder = FindService(this, sID);
	holder->Display();
}

Service* Service::FindService(Service* current, int sID)
{
	if (!current)
		return NULL;

	if (current->service_code == sID)
		return current;

	return current->FindService(next, sID);
}

Service * Service::getNext() {
    return next;
}
int Service::setNext(const Service * toSet) {
    next = new Service(toSet);
	if (!next)
		return -1;

	return 0;
}
