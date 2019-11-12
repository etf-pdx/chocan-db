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
	int display_ID(int ID);

protected:
        //trent- dont understand what the functionality of this is yet
        //takes an int.. from the using class that wants the operator with that ID
        //but that sounds like querying functionality like-
        //query db searching with a ID and have it return the data to create a operator obj with.
        //this either already has it, and the obj has been found and it exists here, 
        //or we're asking an operator with a different ID, and it should return some sort of failure
        //very well could be missing something
	//ident get_ID(int ID);

        //changing to a super simple wrapper for now
	ident get_ID();
	ident ID;
};
