// Header file for operator

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
	int display_ID();
	ident get_ID();

protected:
	ident ID;
};
