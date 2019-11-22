//
// Created by CBunt on 11/20/2019.
//

#include "DBtester.h"
DBtester::DBtester() {
    HappyID.name = "Happy";
    HappyID.address = "777 Lucky lane";
    HappyID.city = "Disney";
    HappyID.state = "HP";
    HappyID.zip = 73137;
}

DBtester::~DBtester() {
    delete(HappyID.name);
    delete(HappyID.address);
    delete(HappyID.city);
    delete(HappyID.state);
}

int DBtester::test(){
    int RetInt = 0;     //Return value
    int Scratch;
    //building time object
    time_t rawtime;
    struct tm *ptm;
    time(&rawtime);
    ptm = gmtime(&rawtime);

    //building file object
    FILE *log;
    log = fopen("TEST.LOG","w");

    //begin testing
    ChocAnDB *DB;
    fprintf(log, "TESTING CHOCAN DATABASE: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
    //Opening DB
    DB = new ChocAnDB(RetInt);
    if (RetInt == 0){
        fprintf(log,"PASSED DATABASE FILE OPENED: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
    }
    else
        fprintf(log,"FAILED DATABASE FILE OPENED: %02d:%02d:%02d\t ERRORCODE: %d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec, RetInt);
    //Add member
    Scratch = DB->AddUser('M',HappyID,RetInt);
    if (RetInt == 0){
        fprintf(log,"PASSED DATABASE ADD MEMBER: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
        fprintf(log, "\t--USER WAS ASSINGED ID NUMBER: %d\n",Scratch);
    }
    else
        fprintf(log,"FAILED DATABASE ADD MEMBER: %02d:%02d:%02d\t ERRORCODE: %d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec, RetInt);
    delete DB;
    fprintf(log, "TEST COMPLETE: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
    fclose(log);
    return RetInt;
}
