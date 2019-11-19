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
	~Operator();
	int Display_Member(int IDnumber);
	int GetIDnumber();
	int HashFormula(int IDnumber);

protected:
	ident get_ident(int IDnumber);

	ident ID;
};