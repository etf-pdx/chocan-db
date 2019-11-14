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

int Operator::Display_Member(int IDnumber)
{
	if (IDnumber < 0)
		return -1;

	indent current_ID = get_indent(IDnumber);

	/*
	 * We might need to make ID a char array so that
	 * we can see if the first number is a certain number
	 * to identify is it a member, provider, or manager
	 */
        // trent- thinking int is best for db usage. 
        // and atoi() can be used when a 1st digit check is needed.
	if (ID < 100000000)	// if we decide to stick with int
		std::cout << "Manager Name: ";
	else if (ID < 200000000)
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

// Get Member data
indent Operator::get_indent(int IDnumber)
{
	// For when we have a data structure to search through
	if (ID.number != IDnumber)
		return NULL;

	return ID;
}