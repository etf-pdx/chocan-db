#include "User.h"

class Manager: public Operator
{
public:
	Manager();
	Manager(char* aName, int aID, char* aAddress, char* aCity, char* aState, int aZip);
	~Manager();

	char* getName(Operator* person);
	int getID(Operator* person);
	char* getAddress(Operator* person);
	char* getCity(Operator* person);
	char* getState(Operator* person);
	int getZip(Operator* person);
	//int AddUser(User*);
	int OptionSelect();
	int InteractiveMode();

protected:
	int AddProvider(ident& To_Add);
	int AddMember(ident& To_Add);

	Operator** person;   // Not sure what this is doing...
};