// Comment out the Header files contain classes you don't want to test

#include <iostream>
//#include "ServiceTest.h"
#include "DBtester.h"
// #include "ManagerTest.h"

/*
 * To compile for VS2019
 * cl /EHsc ..\src\ChocAnDB.cpp ..\src\Manager.cpp ..\src\Service.cpp *.cpp /Fe.\UnitTest.exe
 */

// Unit Test Main
int main()
{
	std::cout << "Starting Unit Test\n\n";
#ifdef SERVICETEST_H

	std::cout << "Starting Service Test\n\n";
	ServiceTest servicetest;
	servicetest.StartTest();

#endif // SERVICETEST_H

#ifdef DBTESTER_H


    std::cout << "Testing Database\n\n";
	DBtester databaseTest;
	databaseTest.test();

#endif // DBTESTER_H

#ifdef MANAGERTEST_H
	// Step 1: Arrange

	Manager* goodData = new Manager("Name", 123456789, "Address", "City", "State", 333);
	Manager* badData = new Manager("Name", 1234, "Address", "City", "State", "badData");
	Manager* emptyData = new Manager();

	// Step 2: Act


	// Step 3: Assert
		assert(emptyData == NULL);
			assert(goodData != NULL);
			assert(badData == NULL);				// Exception handler requires implementation in Constructor
			assert(!goodData->display());
			assert(badData->display());
			assert(emptyData->display());

	// Cleaning Up
	if (goodData)
		delete GoodData;
	if (NextData)
		delete NextData;
	if (EmptyData)
		delete EmptyData;

#endif // MANAGERTEST_H

	return 0;
}