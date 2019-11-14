#include "Manager.h"

Manager::Manager()
{
	Member = NULL;
}

Manager::~Manager()
{
	if (Member)
		delete Member;
}

int Manager::AddProvider(Provider& To_Add)
{
	// First person in the system
	if(!person)
		person = new Provider(To_Add);


	return 0;
}

int Manager::AddMember()
{
	// First person in the system
	if(!person)
		person = new Member(To_Add);

	if (!person)
		return -1;
	return 0;
}