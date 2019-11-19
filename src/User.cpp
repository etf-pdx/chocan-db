#include "User.h"

// Implementation of User class
// Default User constructor
User::User()
{
	My_Service = NULL;
}

User::User(Service To_add)
{
	My_Service = new Service(To_add);
}

// Destructor
User::~User()
{
	if (My_Service)
		delete My_Service;
}

int User::Display_Service(Service* My_Service)
{
	if (!My_Service)
		return -1;

	return My_Service->Display(My_Service);
}

// Implementation of Provider class
// Default Provider constructor
Provider::Provider()
{

}

Provider::Provider(Provider& To_Add)
{
	My_Service = new Service(To_Add.My_Service);
}

// Destructor
Provider::~Provider()
{

}

int Provider::Get_Report(int ID)
{
	// Return -1 for error
	if (ID < 0)
		return -1;

	Display_Member(ID);
	Display_Service(My_Service);
	return 0;
}

// Implementation of Member class
// Default Member constructor
Member::Member()
{

}

Member::Member(Member& To_Add)
{
	My_Service = new Service(To_Add.My_Service);
}

//Destructor
Member::~Member()
{

}

int Member::Get_Report(int ID)
{
	// Return -1 for error
	if (ID < 0)
		return -1;

	Display_Member(ID);
	Display_Service(My_Service);
	return 0;
}