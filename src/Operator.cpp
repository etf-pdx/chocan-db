// Implementation of Operator class

#include "Operator.h"

Operator::Operator()
{
	ID.name = NULL;
	ID.number = 0;
	ID.address = NULL;
	ID.city = NULL;
	ID.state = NULL;
	ID.zip = 0;
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
	if (IDnumber < LOW_MGR)
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

// Get ID number, mostly for comparison
int Operator::GetIDnumber()
{
	return ID.number;
}

int HashFormula(int IDnumber)
{
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