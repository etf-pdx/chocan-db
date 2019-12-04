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

int User::Get_Report(int ID)
{ 
	return 0;
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
	//Display_Service(My_Service);
    My_Service->display();
    if (!Write_Report(ID))
        return -1;
	return 0;
}

int Provider::Write_Report(int ID)
{
    // TODO: Write the provider report to a file. If DB does this, make sure it's called in Provider::Get_Report()
    return 0;
}

int Provider::validateMemberID(int Member_ID) const
{
    // TODO: Query DB if Member_ID is invalid (return -1), active (return ID#) or inactive (return 0). Delete 'if (Member_ID)' statements.
    if (Member_ID < 0)
        return -1;
    if (Member_ID)
        return Member_ID;
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
	//Display_Service(My_Service);
	My_Service->display();
	if (!Write_Report(ID))
	    return -1;
	return 0;
}

int Member::Write_Report(int ID)
{
    // TODO: Write the provider report to a file. If DB does this, make sure it's called in Provider::Get_Report()
    return 0;
}
