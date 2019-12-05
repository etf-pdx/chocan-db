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
    // TODO: Write the provider report to a file, if DB doesn't do this already
    return 0;
}

int Provider::validateMemberID(int Member_ID) const
{
    // TODO: Query DB if Member_ID is invalid (return -1), active (return ID#) or inactive (return 0). Delete 'if (Member_ID)' statements.
    char m = 'm';
    int RetInt = 0;
    ChocAnDB * database = new ChocAnDB(RetInt);
    ident found = database->GetUser(m, Member_ID, RetInt);
    if (!found.status)
        return -1;
    return found.number;
}

void Provider::displayProviderDirectory() {
    int RetInt = 0;
    ChocAnDB * db = new ChocAnDB(RetInt);
    Form * directory = db->ProvDir(RetInt);
    std::cout << directory;
}

int Provider::Write_Report(int ID)
{
	std::ofstream out;

	out.open("ManagerReport.txt");
	out << ("Testing writing to filen\n");

	// Get Manager
	int RetInt = 0;
	ChocAnDB* database = new ChocAnDB(RetInt);
	ident provider = database->GetUser('p', ID, RetInt);

	// Output provider data to file
	out << "PROVIDER NAME: " << provider.name << std::endl;
	out << "ID: " << provider.number << std::endl;
	out << "ADDRESS: " << provider.address << std::endl;
	out << "CITY: " << provider.city << std::endl;
	out << "STATE: " << provider.state << std::endl;
	out << "ZIP: " << provider.zip << std::endl << std::endl;

	// Get service base on providerID
	ServRep* report;
	report = database->GetServRep('p', provider.number, RetInt);
	//ident member = database->GetUser('m', report member id, RetInt);

	// Get ALL Services for that provider
	/*
	 * SERVICE PROVIDED FOR: // member.name
	 * SERVICE SUMMARY: // service->getName();
	 * PROVIDED DATE: // service->getProvDate();
	 * LOGGED DATE: // service->getLogDate();
	 * FEE: // service->getFee();
	 * COMMENTS: // service->getComments();
	 */

	out.close();
	return 0;
}

// Implementation of Member class
// Default Member constructor
Member::Member(): User(){}

Member::Member(int ID): User(ID){}

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
Member::~Member(){}

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
	std::ofstream out;

	out.open("MemberReport.txt");
	out << ("Testing writing to filen\n");

	// Get Member
	int RetInt = 0;
	ChocAnDB* database = new ChocAnDB(RetInt);
	ident member = database->GetUser('m', ID, RetInt);

	// Output member data to file
	out << "PROVIDER NAME: " << member.name << std::endl;
	out << "ID: " << member.number << std::endl;
	out << "ADDRESS: " << member.address << std::endl;
	out << "CITY: " << member.city << std::endl;
	out << "STATE: " << member.state << std::endl;
	out << "ZIP: " << member.zip << std::endl << std::endl;

	// Get service base on providerID
	ServRep* report;
	report = database->GetServRep('p', member.number, RetInt);
	//ident member = database->GetUser('m', report member id, RetInt);

	// Get ALL Services for that provider
	/*
	 * SERVICE PROVIDED BY: // service->getProvID();
	 * SERVICE SUMMARY: // service->getName();
	 * PROVIDED DATE: // service->getProvDate();
	 * LOGGED DATE: // service->getLogDate();
	 * FEE: // service->getFee();
	 * COMMENTS: // service->getComments();
	 */

	out.close();
	return 0;
}