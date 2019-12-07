// Header file for services

#include <iostream>
#include "Definition.h"

class Service
{
public:
	Service();
	Service(char*, int, char*, char*, int, int, float, char*);
	Service(const Service* To_Add);
	~Service();

	int display();
    char* getName();
	int getServID();
	char* getProvDate();
	char* getLogDate();
	int getMemberID();
	int getProviderID();
	float getFee();
	char* getComments();

protected:
	char* service_name;
	int service_code;
	char* provided_date;
	char* logged_date;
	int memberID;
	int providerID;
	float service_fee;
	char* comments;
};