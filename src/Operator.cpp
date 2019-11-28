// Implementation of Operator class

#include "Operator.h"

ident::ident()
{
    name = NULL;
    number = 0;
    address = NULL;
    city = NULL;
    state = NULL;
    zip = 0;
    status = false;
}

ident::ident(char* aName, int aNumber, char* aAddress, char* aCity, char* aState, int aZip, bool aStatus)
{
    name = new char[strlen(aName) + 1];
    strcpy(name, aName);

    address = new char[strlen(aAddress) + 1];
    strcpy(address, aAddress);

    city = new char[strlen(aCity) + 1];
    strcpy(city, aCity);

    state = new char[strlen(aState) + 1];
    strcpy(state, aState);

    ID.number = aNumber;
    zip = aZip;
    status = aStatus;
}

Operator::Operator()
{
	ID.name = NULL;
	ID.number = 0;
	ID.address = NULL;
	ID.city = NULL;
	ID.state = NULL;
	ID.zip = 0;
	
	next = NULL;
}

Operator::Operator(char* aName, int aNumber, char* aAddress, char* aCity, char* aState, int aZip)
{

	ID(aName, aNumber, aAddress, aCity, aState, aZip, aStatus);
	
}

Operator::Operator(ident To_Add)
{
	ID.name = new char [strlen(To_Add.name) + 1];
	strcpy(ID.name, To_Add.name);
	ID.number = To_Add.number;
	ID.address = new char [strlen(To_Add.address) + 1];
	strcpy(ID.address, To_Add.address);
	ID.city = new char [strlen(To_Add.city) + 1];
	strcpy(ID.city, To_Add.city);
	ID.state = new char [strlen(To_Add.state) + 1];
	strcpy(ID.state, To_Add.state);
	ID.zip = To_Add.zip;
}

Operator::Operator(Operator& To_Add)
{
	ID.name = To_Add.getName();
	ID.number = To_Add.GetIDnumber();
	ID.address = To_Add.getAddress();
	ID.city = To_Add.getCity();
	ID.state = To_Add.getState();
	ID.zip = To_Add.getZip();
}

Operator::~Operator()
{
	if (ID.name)
		delete[] ID.name;
	if (ID.address)
		delete[] ID.address;
	if (ID.city)
		delete[] ID.city;
	if (ID.state)
		delete[] ID.state;
}

int Operator::displayID(int IDnumber)
{
	if (IDnumber < MIN_MANAGER)
		return -1;

	ident current_ID = get_ident(IDnumber);

	// Alex: changed these bounds--see Operator.h
	if (IDnumber < MAX_MANAGER)
		std::cout << "Manager Name: ";
	else if (IDnumber < MAX_PROVIDER)
		std::cout << "Provider Name: ";
	else
		std::cout << "Member Name: ";

	std::cout << current_ID.name << std::endl;
	std::cout << "Address: " << current_ID.address << std::endl;
	std::cout << "State: " << current_ID.state << std::endl;
	std::cout << "City: " << current_ID.city << std::endl;
	std::cout << "Zip Code: " << current_ID.zip << std::endl;

	return 0;
}

char* Operator::getName()
{
	return ID.name;
}

// Get ID number, mostly for comparison
int Operator::GetIDnumber()
{
	return ID.number;
}

char* Operator::getAddress()
{
	return ID.address;
}

char* Operator::getCity()
{
	return ID.city;
}

char* Operator::getState()
{
	return ID.state;
}

int Operator::getZip()
{
	return ID.zip;
}

int Operator::AddService()
{
	//ADD SERVICE TO DATABASE

	return 0;
}

// Get Member data
ident Operator::get_ident(int IDnumber)
{
	// For when we have a data structure to search through
	if (ID.number != IDnumber)
		throw "Not an existing ID member!";

	return ID;
}