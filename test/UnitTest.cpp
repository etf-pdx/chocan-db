#include <stdio.h> 
#include <assert.h>
#include "ServiceTest.h"

// Unit Test Main
int main()
{
	// Step 1: Arrange
	ServiceTest test;

	int BadResult = 0;
	int GoodResult = 0;

	Service* GoodData = new Service("Name", 1234567, "09-12-2019", "09-12-2019", 123456789, 987654321, 999.99, "Comments");
	Service* BadData = new Service("This is a really long name" , 0, "Wrong format date", "Wrong format date", 0, 0, 0.0, "Comments");

	// Step 2: Act
	GoodResult = test.DoTest(GoodData);
	BadResult = test.DoTest(BadData);


	// Step 3: Assert
	assert(BadResult == -1);	// Should error out
	assert(GoodResult == 0);	// Should be fine

	return 0;
}