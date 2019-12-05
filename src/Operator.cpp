// Implementation of Operator class

#include "Operator.h"

ident::ident()
{
	//tsw- strings have their own def constr to null str
    number = 0;
    zip = 0;
    status = false;
}

ident::ident(int ID)
{
    number = ID;
    zip = 0;
    status = false;
}

ident::ident(std::string aName, int aNumber, std::string aAddress, std::string aCity, std::string aState, int aZip, bool aStatus)
{
    name = aName;
    address = aAddress;
    city = aCity;
    state = aState;
    number = aNumber;
    zip = aZip;
    status = aStatus;
}

Operator::Operator()
{
	ID.number = 0;
	ID.zip = 0;
	
	//next = NULL;
}

Operator::Operator(int id_num)
{
    ID = ident(id_num);
}

Operator::Operator(std::string aName, int aNumber, std::string aAddress, std::string aCity, std::string aState, int aZip, bool aStatus)
{
	ID = ident(aName, aNumber, aAddress, aCity, aState, aZip, aStatus);
}

Operator::Operator(ident To_Add)
{
	ID.name = To_Add.name;
	ID.number = To_Add.number;
	ID.address = To_Add.address;
	ID.city = To_Add.city;
	ID.state = To_Add.state;
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
}

int Operator::displayID(int IDnumber)
{
	if (IDnumber < MIN_MANAGER)
		return -1;

	ident current_ID = get_ident(IDnumber);

	// Alex: changed these bounds--see Operator.h
	if (IDnumber <= MAX_MANAGER)
		std::cout << "Manager Name: ";
	else if (IDnumber <= MAX_PROVIDER)
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

std::string Operator::getName()
{
	return ID.name;
}

// Get ID number, mostly for comparison
int Operator::GetIDnumber()
{
	return ID.number;
}

std::string Operator::getAddress()
{
	return ID.address;
}

std::string Operator::getCity()
{
	return ID.city;
}

std::string Operator::getState()
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

ProviderReport::ProviderReport(const ServRep &initServRep) {
    servicesProvided = initServRep;
    providerID = 0;
    int numServices = 0;
    totalFee = 0.0;
}
