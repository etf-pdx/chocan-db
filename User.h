// Header file for users and its members

#include "Operator.h"

// User class, is an operator
class User : public Operator
{
public:
	User();
	~User();
protected:
	char* service_name;
	char* information;
};

// Provider class, is a user
class Provider : public User
{
public:
	Provider();
	~Provider();

	int Get_Report();

protected:

};

// Member class, is a user
class Member : public User
{
public:
	Member();
	~Member();

	int Get_Report(int ID);
protected:

};