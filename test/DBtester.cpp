//
// Created by CBunt on 11/20/2019.
//

#include "DBtester.h"
DBtester::DBtester() {
    HappyID.number = NULL;
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
    DB = new ChocAnDB('t',RetInt);
    if (RetInt == 0){
        fprintf(log,"PASSED DATABASE FILE OPENED: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
    }
    else
        fprintf(log,"FAILED DATABASE FILE OPENED: %02d:%02d:%02d\t ERRORCODE: %d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec, RetInt);
    //Add member
    Scratch = DB->AddUser('m',HappyID,RetInt);
    if (RetInt == 0){
        fprintf(log,"PASSED DATABASE ADD MEMBER: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
        fprintf(log, "\t--USER WAS ASSINGED ID NUMBER: %d\n",Scratch);
    }
    else
        fprintf(log,"FAILED DATABASE ADD MEMBER: %02d:%02d:%02d\t ERRORCODE: %d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec, RetInt);

    //Add provider
    Scratch = DB->AddUser('p',HappyID,RetInt);
    if (RetInt == 0){
        fprintf(log,"PASSED DATABASE ADD PROVIDER: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
        fprintf(log, "\t--USER WAS ASSINGED ID NUMBER: %d\n",Scratch);
    }
    else
        fprintf(log,"FAILED DATABASE ADD PROVIDER: %02d:%02d:%02d\t ERRORCODE: %d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec, RetInt);

    //TODO:write manager test
    //Add service
    DB->AddServ(598470,"Dietitian", 125.75,RetInt);
    if (RetInt == 0)
        fprintf(log,"PASSED DATABASE ADD SERVICE: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
    else
        fprintf(log,"FAILED DATABASE ADD SERVICE: %02d:%02d:%02d\t ERRORCODE: %d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec, RetInt);

    //Create a record
    HappyID.number = 100000001;
    DB->AddRecd(HappyID,200000001,598470,"Relaxing","2019-11-11",RetInt);
    if (RetInt == 0)
        fprintf(log,"PASSED DATABASE ADD RECORD: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
    else
        fprintf(log,"FAILED DATABASE ADD RECORD: %02d:%02d:%02d\t ERRORCODE: %d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec, RetInt);

   // RetID = DB->GetUser(HappyID.number,RetInt);
    //if ()


    delete DB;
    fprintf(log, "TEST COMPLETE: %02d:%02d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min, ptm->tm_sec);
    fclose(log);
    return RetInt;
}
