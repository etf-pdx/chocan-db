#include "ServiceTest.h"

int ServiceTest::DoTest(Service* TestData)
{
	if (!TestData)
		return -1;

	return 0;
}

int ServiceTest::StartTest()
{
	// Step 1: Arrange
	int BadResult = 0;
	int GoodResult = 0;

	Service* GoodData = new Service("Name", 1234567, "09-12-2019", "09-12-2019", 123456789, 987654321, 999.99, "Comments");
	Service* BadData = new Service("This is a really long name", 0, "Wrong format date", "Wrong format date", 0, 0, 0.0, "Comments");

	// Step 2: Act
	GoodResult = DoTest(GoodData);
	BadResult = DoTest(BadData);


	// Step 3: Assert
	assert(BadResult == -1);	// Should error out
	assert(GoodResult == 0);	// Should be fine

	delete[] GoodData;
	delete[] BadData;

	return 0;
}

ServiceTest::ServiceTest(){}
ServiceTest::~ServiceTest(){}