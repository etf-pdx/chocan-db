#include <stdio.h> 
#include <assert.h>
#include "..\src\Service.h"

class ServiceTest
{
public:
	ServiceTest();
	~ServiceTest();

	int StartTest();
	int DoTest(Service*);
private:

};