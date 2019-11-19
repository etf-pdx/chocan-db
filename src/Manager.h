#include "User.h"

class Manager
{
public:
	Manager();
	~Manager();

	int OptionSelect();
	int InteractiveMode();

protected:
	int AddProvider(Provider& To_Add);
	int AddMember(Member& To_Add);

	Operator* person;
};