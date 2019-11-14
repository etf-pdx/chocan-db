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

int Operator::Display_Member(int ID)
{
	if (ID < 0)
		return -1;

	indent current_ID = get_ID(ID);
	if (!current_ID)
	{
		cout << "Wrong ID Number.\n";
		return -2;
	}

	/*
	 * We might need to make ID a char array so that
	 * we can see if the first number is a certain number
	 * to identify is it a member, provider, or manager
	 */
	if (ID < 100000000)	// if we decide to stick with int
		cout << "Manager Name: ";
	else if (ID < 200000000)
		cout << "Provider Name: ";
	else
		cout << "Member Name: ";

	cout << current_ID.name << endl;
	cout << "Address: " << current_ID.address << endl;
	cout << "State: " << current_ID.state << endl;
	cout << "City: " << current_ID.city << endl;
	cout << "Zip Code: " << current_ID.zip << endl;

	return 0;
}

indent Operator::get_ID(int IDnumber)
{
	/*
	 * Get ID number here, changes once data structure is
	 * developed
	 */

	if (IDnumber > 0)
		continue;
	if (ID.number == IDnumber)
		return ID;
	
	return null;
}