#include "User.h"

// Implementation of User class
// Default User constructor
User::User(): Operator()
{
	My_Service = NULL;
}

User::User(int ID): Operator(ID)
{
    My_Service = NULL;
}

User::User(Service To_Add)
{
	My_Service = new Service(To_Add);
}

User::User(User& To_Add): Operator(To_Add)
{
	My_Service = new Service(To_Add.My_Service);
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

	return My_Service->display();
}

// Implementation of Provider class
// Default Provider constructor
Provider::Provider(): User()
{

}

Provider::Provider(int ID): User(ID)
{

}

Provider::Provider(Provider& To_Add): User(To_Add)
{
	My_Service = new Service(To_Add.My_Service);
}

Provider::Provider(ident& toAdd)
{
	ID.name = toAdd.name;
	ID.number = toAdd.number;
	ID.address = toAdd.address;
	ID.city = toAdd.city;
	ID.state = toAdd.state;
	ID.zip = toAdd.zip;
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

	displayID(ID);
	Display_Service(My_Service);
	return 0;
}

// Implementation of Member class
// Default Member constructor
Member::Member(): User()
{

}

Member::Member(int ID): User(ID)
{

}

Member::Member(Member& To_Add): User(To_Add)
{
	My_Service = new Service(To_Add.My_Service);
}

Member::Member(ident& toAdd)
{
	ID.name = toAdd.name;
	ID.number = toAdd.number;
	ID.address = toAdd.address;
	ID.city = toAdd.city;
	ID.state = toAdd.state;
	ID.zip = toAdd.zip;
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

	displayID(ID);
	Display_Service(My_Service);
	return 0;
}