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
	// Step 1: Arrange
	/*

	Manager* goodData = new Manager("Name", 1234567, "Address", "City", "State", 333);
	Manager* badData = new Manager("Name", 1234567, "Address", "City", "State", 333);
	Manager* emptyData = new Manager();

	// Step 2: Act


	// Step 3: Assert
	Assert::AreEqual(myName, goodData->getName());
			Assert::AreEqual(myAddress, goodData->getAddress());
			Assert::AreEqual(myNumber, goodData->getNumber());
	

	// Cleaning Up
	if (GoodData)
		delete GoodData;
	if (NextData)
		delete NextData;
	if (EmptyData)
		delete EmptyData;
	*/
	return 0;
}