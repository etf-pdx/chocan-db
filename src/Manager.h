#include "User.h"

class Manager: public Operator
{
public:
	Manager();
	Manager(char* aName, int aID, char* aAddress, char* aCity, char* aState, int aZip);
	~Manager();

	int OptionSelect();
	int InteractiveMode();

protected:
	int AddProvider(ident& To_Add);
	int AddMember(ident& To_Add);
};