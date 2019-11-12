// Implementation of Operator class

#include "Operator.h"

Operator::Operator()
{
	
}

Operator::~Operator()
{

}

int Operator::display_ID(int ID)
{
	if (ID < 0)
		return -1;

	indent current_ID = get_ID(ID);

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