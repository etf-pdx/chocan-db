#include "User.h"

class Manager
{
public:
	Manager();
	~Manager();

	int AddProvider(Provider& To_Add);
	int AddMember(Member& To_Add);

protected:

	Operator* person;
};