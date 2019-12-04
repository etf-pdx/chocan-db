// Header file for users and its members

#include "ChocAnDB.h"

// User class, is an operator
class User : public Operator
{
public:
	User();
	User(int ID);
	User(Service To_Add);
	User(User& To_Add);
	~User();

protected:
	int Display_Service(Service*);

	Service* My_Service;  // AS - We no longer need a service list, right? DB finds all srvcs assoc'd w/ a User, returns vector?
};

// Provider class, is a user
class Provider : public User
{
public:
	Provider();
	Provider(int ID);
	Provider(Provider& To_Add);
	Provider(ident& To_Add);
	~Provider();

	int Get_Report(int Provider_ID);
	int validateMemberID(int Member_ID) const;

protected:

};

// Member class, is a user
class Member : public User
{
public:
	Member();
	Member(int ID);
	Member(Member& To_Add);
	Member(ident& To_Add);
	~Member();

	int Get_Report(int Member_ID);
protected:

};
