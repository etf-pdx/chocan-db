#include "User.h"

class Manager: public Operator
{
public:
	Manager();
	~Manager();

	// int AddUser(User*);
	int OptionSelect();
	int InteractiveMode();

protected:
	int AddProvider(Provider& To_Add);
	int AddMember(Member& To_Add);

	Operator* person;   // Not sure what this is doing...
};