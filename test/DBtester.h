//
// Created by CBunt on 11/20/2019.
// will fix later

#include <ctime>
#include <fstream>
#include "../src/ChocAnDB.h"
#include <iostream>

#define DBTESTER_H
class DBtester {
public:
	int test();
	DBtester();
	~DBtester();

private:
    ident HappyID;
    ident SadID;
    ident RetID;
};

