//#include "ServiceTest.h"
#include "DBtester.h"

/*
 * To compile for VS2019
 * cl /EHsc ..\src\ChocAnDB.cpp ..\src\Service.cpp *.cpp
 */

// Unit Test Main
int main()
{

	// Testing Service
	//ServiceTest servicetest;
	//servicetest.StartTest();
	
	// Testing Database
	DBtester databaseTest;
	databaseTest.test();

	//Manager unit test 


	return 0;
}