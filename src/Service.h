// Header file for services

#include <iostream>


class Service
{
public:
	Service();
	Service(char*, int, char*, char*, int, int, float, char*);
	Service(const Service* To_Add);
	~Service();

	int display(Service* current);

	Service* getNext();
    int setNext(const Service*);
    char* getName(int code);

protected:
	char* service_name;
	int service_code;
	char* provided_date;
	char* logged_date;
	int memberID;
	int providerID;
	float service_fee;
	char* comments;

	Service* next;

    void destroy(Service* current);
};