#include "User.h"

class Manager
{
public:
	Manager();
	Manager(char* aName, int aID, char* aAddress, char* aCity, char* aState, int aZip);
	~Manager();

	char
	// int AddUser(User*);
	int OptionSelect();
	int InteractiveMode();

protected:
	int AddProvider(Provider& To_Add);
	int AddMember(Member& To_Add);

	Operator* person;
};