#include "Manager.h"

// Default Constructor
Manager::Manager(){}

Manager::Manager(char* aName, int aID, char* aAddress, char* aCity, char* aState, int aZip)
{
	
}

// Destructor
Manager::~Manager(){}

/* Not needed I think, operator would be called
char* Manager::getName()
{
	return 
}

int Manager::getID()
{
	return ->GetIDnumber();
}

char* Manager::getAddress()
{
	return person->getAddress();
}

char* Manager::getCity(Operator* person)
{
	return person->getCity();
}

char* Manager::getState(Operator* person)
{
	return person->getState();
}

int Manager::getZip(Operator* person)
{
	return person->getZip();
}
*/

// List of options available to manager
int Manager::OptionSelect()
{
	int choice;

	std::cout << "\n\tGenerate Report\t\t(Enter'R')\n";
	std::cout << "\tEnter Interactive Mode (Manager Only)\t\t(Enter 'I')\n";
	std::cout << "$";	// To prompt user to enter, common practice for command or console program

	std::cin >> choice;
	std::cin.ignore(100, '\n');
	choice = toupper(choice);

	while (choice != 'R' && choice != 'I') {
		std::cout << "\nPlease select from the above options.\n";
		std::cin >> choice;
		std::cin.ignore(100, '\n');
		choice = toupper(choice);
	}

	switch (choice)
	{
	case 'R':
		/* Generate Report Here
		 *	1. Get operator ID Number
		 *	2. Run that class's report
		 *	3. ???
		 *	4. Profit
		 */
		break;
	case 'I':
		InteractiveMode();
		break;
	default:
		break;
	}
	return 0;
}

// When enter interactive mode, we're be doing things to this
int Manager::InteractiveMode()      // Alex: This UI stuff should be implemented in ChocAnMain.cpp.
{                                   //       Very little should be going on in this file.
	char choice;                     //       For interactive mode stuff, main() should be calling DB
	int IDnum;
	bool isInteractive = true;
	/*                              //       and DB should be calling methods of Provider and Member classes.
	 * Entering interactive mode
	 * Prompt for options within interactive mode
	 */
	std::cout << " You can:";
	while (isInteractive == true)
	{
		std::cout << "\n\tAdd a user\t\t(Enter'A')\n";
		std::cout << "\tEdit a user\t\t(Enter 'E')\n";
		std::cout << "\tRemove a user\t\t(Enter 'R')\n";
		std::cout << "\tExit interactive mode\t\t(Enter 'X')\n";
		std::cout << "$";	// To prompt user to enter, common practice for command or console program

		std::cin >> choice;
		std::cin.ignore(100, '\n');
		choice = toupper(choice);

		while (choice != 'A' && choice != 'E'
			&& choice != 'R' && choice != 'X') {
			std::cout << "\nPlease select from the above options.\n";
			std::cin >> choice;
			std::cin.ignore(100, '\n');
			choice = toupper(choice);
		}


		switch (choice)
		{
		case 'A':				// Someone put in checks plz, it's 3am, I'm tired...
			
			char input[100];
			ident To_Add;
		
			std::cout << "Enter User's NAME: ";
			std::cin.get(To_Add.name,100,'\n');
			std::cin.ignore(100, '\n');

			std::cout << "Enter User's ID: ";
			std::cin >> To_Add.number;
			std::cin.ignore(100, '\n');
			while (std::!cin)
			{
				std::cout << "Input has to be numbers. Try again. '\n' Enter user's ID:";
				std::cin >> To_Add.number;
			}
			while (To_Add.number < 0 || To_Add.number > MAX_ID)
			{
				std::cout << "Invalid ID number. Try again. '\n Enter user's ID: ";
				std::cin >> To_Add.number;
			}

			std::cout << "Enter User's ADDRESS: ";
			std::cin.get(To_Add.address);
			std::cin.ignore(100, '\n');
			
			std::cout << "Enter user's CITY: ";
			std::cin.get(To_Add.city);
			std::cin.ignore(100, '\n');
			
			std::cout << "Enter User's STATE: ";
			std::cin.get(To_Add.state);
			std::cin.ignore(100, '\n');
			
			std::cout << "Enter User's ZIP CODE: ";
			std::cin >> To_Add.zip;
			std::cin.ignore(100, '\n');

			if (To_Add.number > MAX_MANAGER&& To_Add.number <= MAX_PROVIDER)	// Add a Provider
				AddProvider(To_Add);
			else if (To_Add.number > MAX_PROVIDER&& To_Add.number <= MAX_ID)	// Add a Member
				AddMember(To_Add);
			break;
		case 'E':
			IDnum = 0;
		wrongEditID:
			std::cout << "Enter an ID for edit: ";
			while (!isdigit(std::cin.peek()))
			{
				std::cout << "Is not a number.\n";
				std::cin.ignore(100, '\n');
			}
			std::cin >> IDnum;
			std::cin.ignore(100, '\n');
			if (IDnum <= 0 || IDnum > MAX_ID)
			{
				std::cout << "Invalid ID Number.\n";
				goto wrongEditID;
			}
			// Edit shenanigans here
			
			break;
		case 'R':
			IDnum = 0;
		wrongRemoveID:
			std::cout << "Enter an ID to be remove: ";
			while (!isdigit(std::cin.peek()))
			{
				std::cout << "Is not a number.\n";
				std::cin.ignore(100, '\n');
			}
			std::cin >> IDnum;
			std::cin.ignore(100, '\n');
			if (IDnum <= 0 || IDnum > MAX_ID)
			{
				std::cout << "Invalid ID Number.\n";
				goto wrongRemoveID;
			}
			// Remove shenanigans here
			break;
		case 'X':
			std::cout << "Exiting Interactive Mode. . .\n\n";
			isInteractive = false;
			break;
		default:
			std::cout << "If you this prompt, please let the dev team know\n\n";
			break;
		}
	}

	return 0;
}

// Create new instance of provider
int Manager::AddProvider(ident& To_Add)
{
	// ADD PROVIDER TO DATABASE

	return 0;
}

// Create new instance of member
int Manager::AddMember(ident& To_Add)
{
	// ADD MEMBER TO DATABASE

	return 0;
}