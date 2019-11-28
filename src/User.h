// Header file for users and its members

#include "Operator.h"

// User class, is an operator
class User : public Operator
{
public:
	User();
	User(Service To_Add);
	User(User& To_Add);
	~User();

protected:
	int Display_Service(Service*);

	Service* My_Service;
};

// Provider class, is a user
class Provider : public User
{
public:
	Provider();
	Provider(Provider& To_Add);
	Provider(ident& To_Add);
	~Provider();

	int Get_Report(int Provider_ID);

protected:

};

// Member class, is a user
class Member : public User
{
public:
	Member();
	Member(Member& To_Add);
	Member(ident& To_Add);
	~Member();

	int Get_Report(int Member_ID);
protected:

};
