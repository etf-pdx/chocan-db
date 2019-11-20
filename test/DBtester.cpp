//
// Created by CBunt on 11/20/2019.
//

#include <time.h>
#include <fsteam>
#include <iostream>
#include "../src/ChocAnDB.h"

int main(){
    ofsteam log;
    log.open (TEST.LOG);
    ChocAnDB *DB;
    log << "TESTING CHOCAN DATABASE: %2d:%02d\n", (ptm->tm_hour+UTC)%24, ptm->tm_min);
    log << DB = new ChocAnDB;
    delete DB;
    log << "TEST COMPLETE: %2d:%02d\n", (ptm->tm_hour+UTC)%24, ptm->tm_min);
    log.close();
    return 0;
}