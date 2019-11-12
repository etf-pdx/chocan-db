// Implementation of Operator class

#include "Operator.h"

Operator::Operator()
{
	
}

Operator::~Operator()
{

}

ident Operator::get_ID(){
    return ID;
}

int Operator::display_ID(int ID)
{
	if (ID < 0)
		return -1;

	ident current_ID = get_ID();

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
