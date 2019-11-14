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
	int Display_Member(int ID);

protected:
	ident get_indent(int IDnumber);
	ident ID;
};