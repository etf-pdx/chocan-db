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

// Constructor w/ Args
Service::Service(char* s_name, int code, char* p_date, char* l_date, int mID, int pID, float fee, char* s_comments)
{
	// Check bounds of numerical arguments:
	if (mID > MAX_ID || mID < 0
	|| pID > MAX_ID || pID < 0
	|| fee > MAX_FEE || fee < 0
	|| code > MAX_SERVICE || code < 0) {
            return;
            // throw exception
        }
    
            //trent- need to rm all "continues" that exist outside for/while loop   //alex - done
            // if service object already exists and we are copying it, do we need these checks?
            // or would the checks already have happened when the existing object set each if its own data mems
            // if we decide we need, then i think only way to catch failed copy constructor is to throw an exception
    
            //alex- with a constructor like this, we're putting in
            // raw values as arguments so we'll need to check them.
            // A true copy constructor will take as an argument
            // a reference to a preexisting Service object:
            //
            //      Service::Service(const Service & existingService) { }
            //
            // I think this kind of constructor can assume values are within bounds
            // and just check for a non-null source reference. See implementation below.

	// Copy numerical values:
	service_code = code;
	memberID = mID;
	providerID = pID;
	service_fee = fee;
    
	// Copy string values:
	service_name = new char[strlen(s_name) + 1];
	strcpy(service_name, s_name);
    
	provided_date = new char[strlen(p_date) + 1];
	strcpy(provided_date, p_date);
        /*
            Check date format here
        */
	logged_date = new char[strlen(l_date) + 1];
	strcpy(logged_date, l_date);
        /*
	    Check date format here
	*/
    
	comments = new char[strlen(s_comments) + 1];
	strcpy(comments, s_comments);
}

// Copy Constructor
Service::Service(const Service & source)
{
	/*
        if (!source) {	// can't do this w/ a reference... check source some other way
        	return;
        	// throw exception
	}
        */
	
	// Copy numerical values:
	service_code = source.service_code;
	memberID = source.memberID;
	providerID = source.providerID;
	service_fee = source.service_fee;
        
	// Copy string values:
	service_name = new char[strlen(source.service_name) + 1];
	strcpy(service_name, source.service_name);
       
	provided_date = new char[strlen(source.logged_date) + 1];
	strcpy(provided_date, source.provided_date);
        
	logged_date = new char[strlen(source.logged_date) + 1];
	strcpy(logged_date, source.logged_date);
        
	comments = new char[strlen(source.comments) + 1];
	strcpy(comments, source.comments);
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
