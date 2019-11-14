#include "User.h"

// Implementation of User class
// Default User constructor
User::User()
{
	My_Service = NULL;
}

User::User(Service To_add)
{
	My_Service = new Service;
	My_Service = To_Add;
}

// Destructor
User::~User()
{
	if (My_Service)
		delete My_Service;
}

int User::Display_Service(Service My_Service)
{
	if (!My_Service)
		return -1;

	return My_Service->display(My_Service);
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

int Provider::Get_Report(int ID)
{
	if (ID < 0)
		return 0;

	display_ID(ID);
	Display_Service(My_Service);
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

int Member::Get_Report(int ID)
{
	if (ID < 0)
		return 0;

	Display_Member(ID);
	Display_Service(My_Service);
}