#include "User.h"
#include <string>

class Manager: public Operator
{
public:
	Manager();
	Manager(int ID);
	Manager(char* aName, int aID, char* aAddress, char* aCity, char* aState, int aZip);
	~Manager();

	int OptionSelect(ChocAnDB & database);
	int EnterInteractiveMode();

	int Write_Report(int ID);

protected:
    int InteractiveMode(ChocAnDB & database);
	int AddProvider(ident& To_Add, ChocAnDB & database);
	int AddMember(ident& To_Add, ChocAnDB & database);
	int EditUser(ident& To_Add, int IDnum, ChocAnDB& database);
};
