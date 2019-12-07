#include "Manager.h"

// Default Constructor
Manager::Manager(): Operator() { }

// ID# Constructor
Manager::Manager(int ID): Operator(ID) { }

// ID Constructor
Manager::Manager(char* aName, int aID, char* aAddress, char* aCity, char* aState, int aZip):
            Operator(aName, aID, aAddress, aCity, aState, aZip, true) { }

// Destructor
Manager::~Manager() { }



// Wrapper for interactive mode.
// Opens DB, passes as arg to InteractiveMode(DB).
// Called from ChocAnMain.cpp
int Manager::EnterInteractiveMode() {

    // Open DB:
    int RetInt = 0;
    ChocAnDB * database = new ChocAnDB(RetInt);

    return InteractiveMode(*database);
}

// When enter interactive mode, we're be doing things to this
int Manager::InteractiveMode(ChocAnDB & database)
{
	ident To_Add;
	char choice;
	int IDnum;
	bool isInteractive = true;
	std::string user_input;
	ident sql_ret;
	int retInt = 0;
	 // Entering interactive mode
	 // Prompt for options within interactive mode
	 
	std::cout << " You can:";
	while (isInteractive == true)
	{
		std::cout << "\n\tAdd a user\t\t\t(Enter 'A')\n";
		std::cout << "\tEdit a user\t\t\t(Enter 'E')\n";
		std::cout << "\tRemove a user\t\t\t(Enter 'R')\n";
		std::cout << "\tAdd a new service key\t\t(Enter 'S')\n";
		std::cout << "\tExit interactive mode\t\t(Enter 'X')\n";
		std::cout << "$";	// To prompt user to enter, common practice for command or console program

		std::cin >> choice;
		std::cin.ignore(100, '\n');
		choice = toupper(choice);

		while (choice != 'A' && choice != 'E'
			&& choice != 'R' && choice != 'X' && choice != 'S') {
			std::cout << "\nPlease select from the above options.\n";
			std::cout << "$";
			std::cin >> choice;
			std::cin.ignore(100, '\n');
			choice = toupper(choice);
		}

		bool valid = false;
		int svc_code = 0;
		float fee = 0.0;
		int error = 0;
		std::string s_name;
        char type = 'a';

        switch (choice)
		{
		case 'A':
			
			char input[MAX_NAME];
			
			std::cout << "Enter User's NAME: ";
			std::getline(std::cin, To_Add.name, '\n');
			To_Add.name.resize(MAX_NAME);

			To_Add.number = 0;

			std::cout << "Enter User's ADDRESS: ";
			std::getline(std::cin, To_Add.address, '\n');
			To_Add.address.resize(200);

			std::cout << "Enter user's CITY: ";
			std::getline(std::cin, To_Add.city, '\n');
			To_Add.city.resize(MAX_CITY);
			
			std::cout << "Enter User's STATE as intials (XX): ";
			std::getline(std::cin, To_Add.state, '\n');
			To_Add.state.resize(2);
			
			do
			{
				std::cout << "Enter User's ZIP CODE: ";
				if (!isdigit(std::cin.peek()))
				{
					valid = false;
					std::cout << "ERROR: Not a number\n\n";
				}
				else
				{
					std::cin >> To_Add.zip;
					if (To_Add.zip < 00000 || To_Add.zip > 99999)
					{
						valid = false;
						std::cout << "ERROR: Invalid Zip Code\n\n";
					}
					else
						valid = true;
				}
				std::cin.ignore(100, '\n');
			} while (valid == false);
				char member_type;
			do
			{
				std::cout << "Enter the type of user: \t (p - provider) (m - member)\n";
				std::cout << "$";
				std::cin >> member_type;
				std::cin.ignore(100, '\n');
				member_type = toupper(member_type);
				if (member_type == 'P')	// Add a Provider
					AddProvider(To_Add, database);
				else if (member_type == 'M')	// Add a Member
					AddMember(To_Add, database);
				else if (member_type != 'M' && member_type != 'P')
				{
					std::cout << "Please type a valid letter either 'P' or 'M' \n";
				}
			} while (member_type != 'P' && member_type != 'M');

			
			break;
			// ----- END ADD USER -----

		case 'E':
			IDnum = 0;
			char type;
			valid = false;
			do
			{
				std::cout << "Enter an ID for edit: ";
				if(!isdigit(std::cin.peek()))
					std::cout << "Is not a number.\n";
				else
				{
					std::cin >> IDnum;
					if (IDnum <= 0 || IDnum > MAX_ID)
						std::cout << "Is not a valid ID.\n";
				}
				if (IDnum >= MIN_MANAGER && IDnum <= MAX_MANAGER) //They are a manager
				{
					type = 'g';
					sql_ret = database.GetUser(type, IDnum, retInt);
					if (sql_ret.number != 0)
						valid = true;
				}
				if (IDnum >= MIN_PROVIDER && IDnum <= MAX_PROVIDER)//They are Provider
				{
					type = 'p';
					sql_ret = database.GetUser(type, IDnum, retInt);
					if (sql_ret.number != 0)
						valid = true;
				}
				if (IDnum >= MIN_MEMBER && IDnum <= MAX_ID)//They are a member
				{
					type = 'm';
					sql_ret = database.GetUser(type, IDnum, retInt);
					if(sql_ret.number!=0)
						valid = true;
				}

				std::cin.ignore(100, '\n');
			} while (valid == false);

			std::cout << "\nPlease type which data of member ID: ";
			std::cout << IDnum;
			std::cout << " That you would like to change";
			do {
				std::cout << " You can:\n";
				std::cout << "\tChange member's Name\t(Enter 'N')\n";
				std::cout << "\tChange member's Address\t(Enter 'A')\n";
				std::cout << "\tChange member's City\t(Enter 'C')\n";
				std::cout << "\tChange member's State\t\t(Enter 'S')\n";
				std::cout << "\tChange member's Zip\t\t\t(Enter 'Z')\n";
				std::cout << "\tDone editing user\t\t\t(Enter 'X')\n";
				std::cout << "$";
				do {
					
					//make sure its len = 1
					do {
						
						
						std::getline(std::cin, user_input, '\n');
						To_Add.name.resize(INPUT_BUFFER);
						if (strlen(user_input.c_str()) != 1) {
							std::cout << "Input is not 1 char in length (and it should be)\n";
						}
					} while (strlen(user_input.c_str()) != 1);
					choice = toupper(user_input[0]);
					//make sure its one of the valid choices
					if (choice != 'N' && choice != 'A'
						&& choice != 'C' && choice != 'S' && choice != 'Z' && choice != 'X') {
						std::cout << "Please select from the above options.\n";
					}
				} while (choice != 'N' && choice != 'A'
					&& choice != 'C' && choice != 'S' && choice != 'Z' && choice != 'X');
				if (choice == 'N') 
				{
					std::cout << "Enter User's NAME: ";
					std::getline(std::cin, To_Add.name, '\n');
					To_Add.name.resize(MAX_NAME);
					valid = true;
				}
				if (choice == 'A') 
				{

					std::cout << "Enter User's ADDRESS: ";
					std::getline(std::cin, To_Add.address, '\n');
					To_Add.address.resize(200);
					valid = true;
				}
				if (choice == 'C') 
				{
					
					std::cout << "Enter user's CITY: ";
					std::getline(std::cin, To_Add.city, '\n');
					To_Add.city.resize(MAX_CITY);
					valid = true;
				}
				if (choice == 'S') 
				{
					
					std::cout << "Enter User's STATE as intials (XX): ";
					std::getline(std::cin, To_Add.state, '\n');
					To_Add.state.resize(2);
					valid = true;

				}
				if (choice == 'Z')
				{

					do
					{
						std::cout << "Enter User's ZIP CODE: ";
						if (!isdigit(std::cin.peek()))
						{
							valid = false;
							std::cout << "ERROR: Not a number\n\n";
						}
						else
						{
							std::cin >> To_Add.zip;
							if (To_Add.zip < 97000 || To_Add.zip > 97999)
							{
								valid = false;
								std::cout << "ERROR: Invalid Zip Code\n\n";
							}
							else
								valid = true;
						}
						std::cin.ignore(100, '\n');
					} while (valid == false);
				}
			} while (choice != 'X');
			EditUser(To_Add,IDnum,database);

			break;

		case 'R':
			IDnum = 0;
			do
			{
				std::cout << "Enter the ID of the user to be removed: ";
				if (!isdigit(std::cin.peek()))
					std::cout << "Is not a number.\n";
				else
				{
					std::cin >> IDnum;
					if (IDnum <= 0 || IDnum > MAX_ID)
						std::cout << "Is not a valid ID.\n";
					else
						valid = true;
				}
				std::cin.ignore(100, '\n');
			} while (valid == false);

			// get the type of user to remove
			if(IDnum <= MAX_MANAGER){
			    type = 'g';
			}else if(IDnum <= MAX_PROVIDER){
			    type = 'p';
			} else{
			    type = 'm';
			}
            // remove the user
            database.RmUser(type, IDnum, error);
			break;

		case 'X':
			std::cout << "Exiting Interactive Mode. . .\n\n";
			isInteractive = false;
			break;

        case 'S':
            std::cout << "Enter service type: ";
			std::getline(std::cin, s_name, '\n');
			s_name.resize(MAX_NAME);
			do
			{
				std::cout << "Enter service code: ";
				if (!isdigit(std::cin.peek()))
				{
					std::cout << "ERROR: Not a number\n\n";
					valid = false;
				}
				else
				{
					std::cin >> svc_code;
					if (svc_code <= 0 || svc_code > MAX_SERVICE)
						std::cout << "ERROR: Invalid Service code\n\n";
					else
						valid = true;
				}
				std::cin.ignore(100, '\n');
			} while (valid == false);      
			do
			{
				std::cout << "Enter service fee: ";
				if (!isdigit(std::cin.peek()))
					std::cout << "ERROR: Not a number\n\n";
				else
					std::cin >> fee;
				std::cin.ignore(100, '\n');
				if (fee <= 0 || fee > MAX_FEE)
					std::cout << "ERROR: Invalid Service Fee\n\n";
			} while (fee <= 0 || fee > MAX_FEE);

            database.AddServ(svc_code, s_name.c_str(), fee, error); // write service to db
            break;

		default:
			std::cout << "If you are reading this prompt, please let the dev team know\n\n";
			break;
		}
	}

	return 0;
}

// Create new instance of provider
//If return -1 == UNDEFINED
int Manager::AddProvider(ident& To_Add, ChocAnDB & database)
{
	char type = 'p';
	int retInt = 0;
	int result;
	// ADD PROVIDER TO DATABASE
	result = database.AddUser(type, To_Add, retInt);
	return result;
}

// Create new instance of member
int Manager::AddMember(ident& To_Add, ChocAnDB & database)
{
	char type = 'm';
	int retInt = 0;
	int result;
	// ADD MEMBER TO DATABASE
	result = database.AddUser(type, To_Add, retInt);
	return result;
	
}

int Manager::EditUser(ident& To_Add,int IDnum, ChocAnDB& database)
{
	char type;
	int retInt = 0;
	
	if (IDnum >= MIN_MANAGER && IDnum <= MAX_MANAGER) //They are a manager
	{
		type = 'g';
		if (database.ModUser(type, IDnum, retInt) == 0)
		{
			std::cout << "USER SUCCESSFULLY EDITED";
			return 1;
		}
	}

	if (IDnum >= MIN_PROVIDER && IDnum <= MAX_PROVIDER)//They are Provider
	{
		type = 'p';
		if (database.ModUser(type, IDnum, retInt) == 0)
		{
			std::cout << "USER SUCCESSFULLY EDITED";
			return 1;
		}
	}
	if (IDnum >= MIN_MEMBER && IDnum <= MAX_ID)//They are a member
	{
		type = 'm';
		if (database.ModUser(type, IDnum, retInt) == 0)
		{
			std::cout << "USER SUCCESSFULLY EDITED";
			return 1;
		}
	}
	std::cout << "UNABLE TO EDIT";
	return 0;
}


int Manager::Write_Report(int ID)
{
	std::ofstream out;

	out.open("ManagerReport.txt");
	if (out.fail())
		return -1;

	// Get Manager
	int RetInt = 0;
	ChocAnDB* database = new ChocAnDB(RetInt);
	Form* directory = database->ProvDir(RetInt);
	int count = 0;

	for (auto var : *directory) {
		// Input everything into a temp ptr
		// If Provider ID matched, write it into report
		// If Provider ID is not match, delete and move on

		// ----- CURRENTLY WRITING EVERY SERVICE -----
		if (count == 0)
			out << "PROVIDER ID: " << var << std::endl;
		else if (count == 1)
			out << "PROVIDER NAME: " << var << std::endl;
		else if (count == 2)
			out << "ADDRESS: " << var << std::endl;
		else if (count == 3)
			out << "CITY: " << var << std::endl;
		else if (count == 4)
			out << "STATE: " << var << std::endl;
		else if (count == 5)
			out << "ZIP: " << var << std::endl;

		++count;
		count = count % 6;
	}

	delete database;
	delete directory;
	out.close();
	return 0;
}
