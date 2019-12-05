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

void Provider::displayProviderDirectory() {
    int RetInt = 0;
    ChocAnDB * db = new ChocAnDB(RetInt);
    Form * directory = db->ProvDir(RetInt);
    for(auto var : *directory){
        std::cout << var;
    }
    std::cout << std::endl;
	delete db;
}

// Implementation of Member class
// Default Member constructor
Member::Member(): User()
{

}

Member::Member(int ID): User(ID)
{

}

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
Member::~Member()
{

}

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
    // TODO: Write the provider report to a file. If DB does this, make sure it's called in Provider::Get_Report()
    return 0;
}


// checkInMember() obtains a member ID via user input.
// It returns the valid member I.D. number.
// It returns 0 if the number is invalid
// or if the member is inactive or suspended,
// communicating member status to the user.
// Requirements Doc: 4.3.2    Requesting ID Verification:
int Provider::memberID_Verify() {
	int ID, memCheck;
	std::string user_input;
	ident sql_ret;
	int db_RetInt, query_RetInt = 0;
	ChocAnDB* db = new ChocAnDB(db_RetInt);

	// Get the member's ID:
	do {
		ID = -1;
		//tsw- not sure on what the correct mem id range is. will circle back.
		// AS - Member IDs are 300000000 - 999999999. See Definition.h, Operator.h
		while (ID <= MAX_PROVIDER || ID > MAX_ID) {     // MAX_PROVIDER == 299999999; MAX_ID == 999999999
			std::cout << "\nPlease enter the ChocAn member's nine digit ID number:\n";
			// tsw- protecting against bad input like mgr/prvdr ID input above
			// (not checking for a mem id that doesn't exist in db. thats below/later)
			std::cin >> user_input;
			std::cin.ignore(INPUT_BUFFER, '\n');
			try {
				ID = stoi(user_input);
			}
			catch (std::invalid_argument e) {
				std::cout << "Input is not a number.\n";
				ID = -1;
			}
			catch (std::out_of_range e) {
				std::cout << "\nInput is out of int's range.\n";
				ID = -1;
			}
			if (ID <= MAX_PROVIDER || ID > MAX_ID) {
				std::cout << "\nInput is not a valid member ID number.\n";
			}
			else {
				//valid input
				std::cout << "\nYou entered " << ID << ". Is that correct? Y/N\n";
			}
		}
	} while (!yesorno());
	// Validate the member's ID:
	std::cout << "\nContacting Chocaholics Anonymous...\n";
	sql_ret = db->GetUser('m', ID, query_RetInt);

	if (query_RetInt == false) {
		std::cout << "Member does not exist in DB \n";
		delete db;
		return -1;
	}
	if (sql_ret.status == false) {
		std::cout << "\nMember suspended\n";
		delete db;
		return -2;
	}
	delete db;
	return 0;
}

// logService() obtains the necessary info to
// log a service from the provider terminal.
// It returns 0 on failure, 1 on success.

//Requirements document: 4.3.3 Logging a Service:
int Provider::logService() {
	int memberID = 0;
	int serviceCode = 0;
    int db_ret_int = 0;
    std::string serviceDate, user_input;
	std::string comments;

	memberID = memberID_Verify();
	if (memberID < 0) 
		return 0;
	

	// Get the service date:
	do {
		std::cout << "Please enter the date the service was provided (MM-DD-YYYY)\n";
		std::cin >> serviceDate;
		std::cin.ignore(INPUT_BUFFER, '\n');
		if (!dateFormatCheck(serviceDate)) {
			std::cout << "Input is not in correct format. \n";
		}
	} while (!dateFormatCheck(serviceDate));

	// Get the service code:
	do {
		serviceCode = -1;
		while (serviceCode < 0 || serviceCode > MAX_SERVICE) {
			std::cout << "\nPlease enter the six digit service code.\n";
			std::cin >> user_input;
			std::cin.ignore(INPUT_BUFFER, '\n');
			try {
				serviceCode = stoi(user_input);
			}
			catch (std::invalid_argument e) {
				std::cout << "Input is not a number.\n";
				serviceCode = -1;
			}
			catch (std::out_of_range e) {
				std::cout << "\nInput is out of int's range.\n";
				serviceCode = -1;
			}
			if (serviceCode < 0 || serviceCode > MAX_SERVICE) {
				std::cout << "\nInvalid.\nPlease enter a valid six digit service code.\n";
			}
			else {
				std::cout << "\nYou entered " << serviceCode << ": " << std::endl;
				std::cout << "\nIs that correct? Y/N\n";
			}
		}
	} while (!yesorno());

	// Get comments:
	std::cout << "\nWould you like to record comments on this service? Y/N\n";
	if (yesorno()) {
		do {
			std::cout << "\nEnter your comments (" << MAX_COMMENT - 1 << " characters max)\n";
			std::cin >> comments;
			std::cin.ignore(INPUT_BUFFER, '\n');
			if (strlen(comments.c_str()) > MAX_COMMENT - 1) {
				std::cout << "Comment too long.\n";
			}
		} while (strlen(comments.c_str()) > MAX_COMMENT - 1);
	}

	// Record service:
    ChocAnDB * db = new ChocAnDB(db_ret_int);
    db->AddRecd(memberID, this->ID.number, serviceCode, comments.c_str(), serviceDate.c_str(), db_ret_int);
    delete db;
	return 1;
}

// Return the response to a yes or no question.
bool User::yesorno() {
	char choice;
	std::string user_input;

	do {
		//make sure its len = 1
		do {
			std::cin >> user_input;
			std::cin.ignore(INPUT_BUFFER, '\n');
			if (strlen(user_input.c_str()) != 1) {
				std::cout << "\nLooking for a 'Y' or 'N' here...\n";
			}
		} while (strlen(user_input.c_str()) != 1);
		choice = toupper(user_input[0]);
		//make sure its one of the valid choices
		if (choice != 'Y' && choice != 'N') {
			std::cout << "\nLooking for a 'Y' or 'N' here...\n";
		}
	} while (choice != 'Y' && choice != 'N');

	return choice == 'Y';
}

//tsw- make sure user inputs a well formatted date
//edge cases left unchecked- wont prevent 31 days in jan for example
bool User::dateFormatCheck(std::string input_date) {
	//month check
	if (strlen(input_date.c_str()) != 10)			return false;
	if (!isdigit(input_date[0]))					return false;
	if (!isdigit(input_date[1]))					return false;
	if (std::stoi(input_date.substr(0, 2)) < 1 ||
		std::stoi(input_date.substr(0, 2)) > 12)	return false;
	if (input_date[2] != '-')						return false;
	//day check
	if (!isdigit(input_date[3]))					return false;
	if (!isdigit(input_date[4]))					return false;
	if (std::stoi(input_date.substr(3, 2)) < 1 ||
		std::stoi(input_date.substr(3, 2)) > 31)	return false;
	if (input_date[5] != '-')						return false;
	//year check
	if (!isdigit(input_date[6]))					return false;
	if (!isdigit(input_date[7]))					return false;
	if (!isdigit(input_date[8]))					return false;
	if (!isdigit(input_date[9]))					return false;
	if (std::stoi(input_date.substr(6, 4)) < 1 ||
		std::stoi(input_date.substr(6, 4)) > 2019)	return false;

	return true;
}