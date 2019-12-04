#include "User.h"

class Manager: public Operator
{
public:
	Manager();
	Manager(int ID);
	Manager(char* aName, int aID, char* aAddress, char* aCity, char* aState, int aZip);
	~Manager();

	int OptionSelect(ChocAnDB & database);
	int EnterInteractiveMode();

protected:
    int InteractiveMode(ChocAnDB & database);
	int AddProvider(ident& To_Add, ChocAnDB & database);
	int AddMember(ident& To_Add, ChocAnDB & database);
};