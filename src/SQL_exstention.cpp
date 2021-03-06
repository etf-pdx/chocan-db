//
//Static functions used to write back data from SQL DB
//
#include <stdio.h>
#include "Operator.h"


static int FillID(ident *data, int argc, char **argv, char **azColName){

    data->number = atoi(argv[0]);
    data->name = argv[1];
    data->address = argv[2];
    data->city = argv[3];
    data->state = argv[4];
    data->zip = atoi(argv[5]);

    return 0;
}

static int GetStat(int* Ret, int argc, char **argv, char **azColName){
    try {
        *Ret= atoi(argv[0]);
        return 0;
    }
    catch (...) {
        // abort select on failure, don't let exception propogate thru sqlite3 call-stack
        return -1;
    }
    return 0;
}


static int IDlist(IDList *Ret, int argc, char **argv, char **azColName) {
    try {
        int *ret = new int(atoi(argv[0]));
        Ret->emplace_back(ret);
    }
    catch (...) {
        // abort select on failure, don't let exception propogate thru sqlite3 call-stack
        return -1;
    }
    return 0;
}

static int SVlist(Form *Ret, int argc, char **argv, char **azColName) {
    char buff1[1024];
    char buff2[1024];
    buff1[0] = '\0';
    buff2[0] = '\0';
    char *ret = nullptr;
    try {

          for (int i = 0; i < argc; i++) {
            sprintf(buff1,"%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            strcat(buff2,buff1);
        } //TODO: fix formating so ret does not chop the ends
          strcpy(buff1,buff2);
          ret = new char[strlen(buff1)+1];
          strcpy(ret,buff1);
          Ret->emplace_back(ret);
    }
    catch (...) {
        // abort select on failure, don't let exception propogate thru sqlite3 call-stack
        return -1;
    }
//    delete buff1;//TODO: deletes error out?
//    delete buff2;
//    delete ret;
    return 0;
}

static int GetRep(ServRep *Ret, int argc, char **argv, char **azColName){
    ServiceReport *tmp = new ServiceReport;
    tmp->dateProvided = argv[0];
    tmp->dateLogged = argv[1];
    tmp->serviceCode = atoi(argv[2]);
    tmp->providerNumber = atoi(argv[3]);
    tmp->providerName = argv[4];
    tmp->memberName = argv[6];
    tmp->memberNumber = atoi(argv[5]);
    tmp->fee = atof(argv[8]);
    try {
        Ret->emplace_back(tmp);
    }
    catch (...){
        return -1;
    }
    return 0;
}
