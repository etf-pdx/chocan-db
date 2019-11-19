#include "Manager.h"

// Default Constructor
Manager::Manager()
{
	person = NULL;
}

// Destructor
Manager::~Manager()
{
	if (person)
		delete person;
}

// List of options available to manager
int Manager::OptionSelect()
{
	/*
	char Input [1001];
	std::cout << "List options of things to do here.\n";
	std::cin.get(input, 10001, \n);
	std::cin.ignore(1000);

	// Identifying input here
	Case 1:	Get reports
	Case 2: Ineteractive mode
	*/
	return 0;
}

// When enter interactive mode, we're be doing things to this
int Manager::InteractiveMode()
{
	/*
	 * Entering interactive mode
	 * Prompt for options within interactive mode
	 */

	// Option for Add a user
	/*
	if(User chose to add a member)
	{
		// GetInformation();
		// Compare IDnumber inputted to see if it's a
		// Provider or a Member.
		if(Provider)
		{
			if(AddProvider(To_Add)
			{
				std::cout << "Add Provider failed\n";
				return -1;
			}
		}
		else if(Member)
		{
			if(AddMember(To_Add)
			{
				std::cout << "Add Member failed\n";
				return -1;
			}
		}
	}

	// Option for edit a member

	// Option for remove a member
	 */
	return 0;
}

// Create new instance of provider
int Manager::AddProvider(Provider& To_Add)
{
	// First person in the system
	if(!person)
		person = new Provider(To_Add);

	return 0;
}

// Create new instance of member
int Manager::AddMember(Member& To_Add)
{
	// First person in the system
	if(!person)
		person = new Member(To_Add);

	if (!person)
		return -1;
	return 0;
}