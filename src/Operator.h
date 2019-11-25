// Header file for operator
#include <iostream>

struct ident
{
	char *name;
	int number;
	char *address;
	char *city;
	char *state;
	int zip;
};

class Operator
{
public:
	Operator();
	Operator(char* aName, int aNumber, char* aAddress, char* aCity, char* aState, int aZip);
	~Operator();
	
	//Get functions
	char* getName();
	int GetIDnumber();
	char* getAdress();
	char* getCity();
	char* getState();
	int getZip();

	int Display_Member(int IDnumber);
	int HashFormula(int IDnumber);

protected:
	ident get_ident(int IDnumber);

	ident ID;
};