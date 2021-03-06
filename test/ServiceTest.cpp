#include "ServiceTest.h"

[Fact]
int ServiceTest::StartTest()
{
	// Step 1: Arrange
	Service* GoodData = new Service("Name", 1234567, "09-12-2019", "09-12-2019", 123456789, 987654321, 999.99, "Comments");
	Service* BadData = new Service("This is a really long name", 0, "Wrong format date", "Wrong format date", 0, 0, 0.0, "Comments");
	Service* EmptyData = NULL;

	// Step 2: Act

	// Step 3: Assert
	assert(EmptyData == NULL);
	assert(GoodData != NULL);
	assert(BadData == NULL);				// Exception handler requires implementation in Constructor
	assert(GoodData->getName(1234567) == "Name");

	// Cleaning Up
	if (!GoodData)
		delete[] GoodData;
	if (!BadData)
		delete[] BadData;
	if (!EmptyData)
		delete[] EmptyData;

	return 0;
}

ServiceTest::ServiceTest(){}
ServiceTest::~ServiceTest(){}