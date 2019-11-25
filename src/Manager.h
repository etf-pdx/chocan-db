#include "User.h"

class Manager: public Operator
{
public:
	Manager();
	Manager(char* aName, int aID, char* aAddress, char* aCity, char* aState, int aZip);
	~Manager();

	char* getName();
	int getID();
	char* getAddress();
	char* getCity();
	char* getState();
	int getZip();
	// int AddUser(User*);
	int OptionSelect();
	int InteractiveMode();

protected:
	int AddProvider(Provider& To_Add);
	int AddMember(Member& To_Add);

	Operator* person;   // Not sure what this is doing...
};