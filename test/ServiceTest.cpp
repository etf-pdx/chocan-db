#include "ServiceTest.h"

int ServiceTest::StartTest()
{
	// Step 1: Arrange
	Service* GoodData = new Service("Name", 1234567, "09-12-2019", "09-12-2019", 123456789, 987654321, 999.99, "Comments");
	Service* NextData = new Service("This is a really long name", 0, "Wrong format date", "Wrong format date", 0, 0, 0.0, "Comments");
	Service* EmptyData = NULL;

	// Step 2: Act


	// Step 3: Assert
	assert(EmptyData == NULL);
	assert(GoodData != NULL);
	assert(NextData != NULL);
	assert(!GoodData->Display(GoodData));
	assert(!NextData->Display(NextData));
	//std::cout << "Setting Next Node\n";
	assert(!GoodData->setNext(NextData));
	assert(!GoodData->Display(GoodData));

	if (!GoodData)
		delete[] GoodData;
	if (!NextData)
		delete[] NextData;
	if (!EmptyData)
		delete[] EmptyData;

	return 0;
}

ServiceTest::ServiceTest(){}
ServiceTest::~ServiceTest(){}