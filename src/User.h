// Header file for users and its members

#include "ChocAnDB.h"
#include <string>

// User class, is an operator
class User : public Operator
{
public:
	User();
	User(int ID);
	User(Service To_Add);
	User(User& To_Add);
	virtual ~User();

    virtual int Get_Report(int ID) = 0;
    virtual int Write_Report(int ID) = 0;

	bool dateFormatCheck(std::string input_date);

protected:
	int Display_Service(Service*);
	bool yesorno();

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

	int Get_Report(int ID);
	int Write_Report(int ID);

	// Requirements Doc: 4.3.1 Requesting a Provider Directory:
	static void displayProviderDirectory();
	// Requirements Doc: 4.3.2 Requesting ID Verification:
	int memberID_Verify();
	//Requirements document: 4.3.3 Logging a Service:
	int logService();

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

	int Get_Report(int ID);
	int Write_Report(int ID);
protected:

};
