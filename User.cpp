#include "User.h"

// Implementation of User class
// Default User constructor
User::User()
{
	service_name = NULL;
	information = NULL;
}

// Destructor
User::~User()
{
	if (service_name)
	{
		delete service_name;
	}
	if (information)
	{
		delete information;
	}
}

// Implementation of Provider class
// Default Provider constructor
Provider::Provider()
{

}

// Destructor
Provider::~Provider()
{

}

// Implementation of Member class
// Default Member constructor
Member::Member()
{

}

//Destructor
Member::~Member()
{

}