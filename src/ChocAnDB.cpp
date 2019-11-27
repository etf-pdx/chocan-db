//
// Created by CBunt on 11/8/2019.
//

#include "ChocAnDB.h"
#define SQLITE_OK           0   // Successful result
ChocAnDB::ChocAnDB(){ ChocAnDB(RetInt); }
ChocAnDB::ChocAnDB(int &RetInt)
{
    DB = nullptr;
    STMT = nullptr;
    ErrMsg = nullptr;
    RetInt = OpenDB();
}

ChocAnDB::~ChocAnDB()
{
    //trent- The sqlite3_finalize() function is called to delete a [prepared statement].
    //will be used elsewhere.
    //sqlite3_finalize();

    //trent- successful sqlite3_close() call deallocates all so no need for delete.
    //learn how to handle SQLITE_API objects because sucessful function call rets SQLITE_OK
    sqlite3_finalize(STMT);
    sqlite3_close(DB);
    DB = nullptr;
    STMT = nullptr;
}


int ChocAnDB::AddUser(char type, ident UserID, int &RetInt) {
    RetInt = 0;
    char *Stmt = prepUser(type, UserID);
    std::cout << "UPDATING DATABASE:";

    switch (type) {
        case 'm' :
            RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != SQLITE_OK) {
                std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
                return RetInt = 2;
            } break;

        case 'p' :
            RetInt = sqlite3_exec(DB,Stmt,nullptr,nullptr,&ErrMsg);
            if (RetInt != SQLITE_OK){
                std::cout << "\t-FAILED-\n" <<  "PROVIDER TABLE FAILED:\t" << ErrMsg;
                return 3;
            } break;
        case 'g':
            //TODO: fill in manager
        default:
            return -1;
    }

    int IDnum = sqlite3_last_insert_rowid(DB);
    std::cout << "\t-UPDATE SUCCESSFUL-\n" << "\tID NUMBER:\t" << IDnum << std::endl;

    return IDnum;
}

char* ChocAnDB::prepUser(char type, ident UserID){
    char Stmt[1024];
    char *ret = nullptr;
    sprintf(Stmt, "    ("
                  "     NAME,"
                  "     ADDRESS,"
                  "     CITY,"
                  "     STATE,"
                  "     ZIP"
                  "    )"
                  "        VALUES ("
                  "        '%s','%s','%s','%s','%d');",
                  UserID.name,UserID.address,UserID.city,UserID.state,UserID.zip);
    switch (type) {
        case 'm' :
            ret = new char[strlen(Stmt)+19];
            strcpy(ret, "INSERT INTO MEMBER");
            strcat(ret, Stmt);
            break;
        case 'p' :
            ret = new char[strlen(Stmt)+21];
            strcpy(ret, "INSERT INTO PROVIDER");
            strcat(ret, Stmt);
            break;
        case 'g' :
            ret = new char[strlen(Stmt)+20];
            strcpy(ret, "INSERT INTO MANAGER");
            strcat(ret, Stmt);
            break;
        default:
            return nullptr;
    }

    return ret;
}

int ChocAnDB::AddServ(int ServCD, char *ServNm, float fee, int &RetInt) {
    RetInt = 0;
    char Buff[1024];
    char *Stmt = nullptr;
    std::cout << "UPDATING DATABASE:";
    sprintf(Buff, "INSERT OR IGNORE INTO SERVICE ("
                  "SERVICE_CODE, SERVICE_NAME, FEE)"
                  "VALUES ( '%d','%s',ROUND('%f',2)"
                  ");",ServCD,ServNm,fee);
    Stmt = new char[strlen(Buff)+1];
    strcpy(Stmt,Buff);
    RetInt = sqlite3_exec(DB,Stmt,nullptr,nullptr,&ErrMsg);
    if (RetInt != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "SERVICE TABLE FAILED:\t" << ErrMsg;
        return 5;
    }
    int SVnum = sqlite3_last_insert_rowid(DB);
    std::cout << "\t-UPDATE SUCCESSFUL-\n" << "\tSERVICE CODE:\t" << SVnum << std::endl;

    return SVnum;
}

//add a service to a member
int ChocAnDB::AddRecd(ident &UserID, int ProvID, int ServCD, char* comm, char* datetime, int &RetInt){
    RetInt = 0;
    char Buff[1024];
    char *Stmt = nullptr;
    RetInt = ChkFrm(datetime);
    if (RetInt)
        return -1;
    std::cout << "UPDATING DATABASE:";
    sprintf(Buff, "INSERT INTO RECORD ("
                  "SERVICE_PROVIDED,"
                  "SERVICE_LOGGED,"
                  "SERVICE_CODE,"
                  "PROVIDER_ID,"
                  "MEMBER_NAME,"
                  "MEMBER_ID,"
                  "COMMENT)"
                  "VALUES ("
                  "DATETIME('%s'),"
                  "CURRENT_TIMESTAMP,"
                  "'%d','%d','%s','%d','%s');",
            datetime, ServCD, ProvID, UserID.name, UserID.number, comm);
    Stmt = new char[strlen(Buff)+1];
    strcpy(Stmt,Buff);
    RetInt = sqlite3_exec(DB,Stmt,nullptr,nullptr,&ErrMsg);
    if (RetInt != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "SERVICE TABLE FAILED:\t" << ErrMsg;
        return 4;
    }

    std::cout << "\t-UPDATE SUCCESSFUL-\n" << "\tSERVICE CODE:\t" << ServCD << std::endl;

    return 0;
}

//TODO: build function to ensure datetime char* fits format
//This will check formatting return 0 if correct
int ChocAnDB::ChkFrm(char *datetime) {
    return 0;
}

int ChocAnDB::OpenDB() {
    const char *MembTB = "create table IF NOT EXISTS MEMBER ("  //If Table does not exist it will be created
                         "    ID      INTEGER CHECK (ID < 199999999)" //
                         "                      primary key AUTOINCREMENT ,"                 //Primary key makes ID's unique
                         "    NAME    TEXT(25) NOT NULL ,"
                         "    ADDRESS TEXT(25) NOT NULL ,"
                         "    CITY    TEXT(14) NOT NULL ,"
                         "    STATE   TEXT(2) NOT NULL ,"
                         "    ZIP     INT(5) NOT NULL "
                         "); INSERT OR IGNORE INTO MEMBER"
                         "(ID,NAME,ADDRESS,CITY,STATE,ZIP) "
                         "        VALUES ("
                         "        100000000,"
                         "        'NAME',"
                         "        'ADDRESS',"
                         "        'CITY',"
                         "        'AA',"
                         "        00000);";

    const char *PrvdTB = "create table IF NOT EXISTS PROVIDER ("//If Table does not exist it will be created
                         "    ID      INTEGER CHECK (ID < 299999999)"
                         "                      primary key AUTOINCREMENT,"                 //Primary key makes ID's unique
                         "    NAME    CHARACTER(25) NOT NULL ,"
                         "    ADDRESS CHARACTER(25) NOT NULL ,"
                         "    CITY    CHARACTER(14) NOT NULL ,"
                         "    STATE   CHARACTER(2) NOT NULL ,"
                         "    ZIP     INT(5) NOT NULL "
                         "); INSERT OR IGNORE INTO PROVIDER"
                         "(ID,NAME,ADDRESS,CITY,STATE,ZIP)"
                         "        VALUES ("
                         "        200000000,"
                         "        'NAME',"
                         "        'ADDRESS',"
                         "        'CITY',"
                         "        'AA',"
                         "        00000);";

    const char *MgmrTB = "create table MANAGER ("
                         "    ID      INTEGER"
                         "        primary key autoincrement,"
                         "    NAME    CHARACTER(25) not null,"
                         "    ADDRESS CHARACTER(25),"
                         "    CITY    CHARACTER(14),"
                         "    STATE   CHARACTER(2),"
                         "    ZIP     INT(5),"
                         "    check (ID < 99999999)"
                         ");INSERT OR IGNORE INTO MANAGER"
                         "(ID,NAME,ADDRESS,CITY,STATE,ZIP)"
                         "        VALUES ("
                         "        0,"
                         "        'NAME',"
                         "        'ADDRESS',"
                         "        'CITY',"
                         "        'AA',"
                         "        00000);";
    //TODO: Maintenance active vs suspended members

    const char *actvTB = "create table IF NOT EXISTS ACTIVE("
                         "    START_DATE DATE NOT NULL, "
                         "    MONTHS_PAID INT,"
                         "    MEMBER_ID INT(9) NOT NULL, "
                         "    FOREIGN KEY (MEMBER_ID)"
                         "        REFERENCES MEMBER);";


    const char *RecdTB = "create table IF NOT EXISTS RECORD (" //If Table does not exist it will be created
                         "    SERVICE_PROVIDED DATE NOT NULL ,"
                         "    SERVICE_LOGGED   DATE NOT NULL ,"
                         "    SERVICE_CODE     INT(6) NOT NULL,"
                         "    PROVIDER_ID      INT(9) NOT NULL ,"
                         "    MEMBER_NAME      TEXT(25) NOT NULL ,"
                         "    MEMBER_ID        INT(9) NOT NULL ,"
                         "    COMMENT          TEXT(100),"
                         //Foreign key links to a primary key
                         "    FOREIGN KEY(MEMBER_ID)        REFERENCES MEMBER,"
                         "    FOREIGN KEY(PROVIDER_ID)      REFERENCES PROVIDER,"
                         "    FOREIGN KEY(SERVICE_CODE)     REFERENCES SERVICE);";

    const char *ServTB = "create table IF NOT EXISTS SERVICE ("
                         "    SERVICE_CODE INTEGER NOT NULL "
                         "        primary key,"
                         "    SERVICE_NAME TEXT(20) NOT NULL, "
                         "    FEE          REAL CHECK (FEE < 1000));";

    int exit = 0;
    std::cout << "PREPARING DATABASE:";
    //trent- error checking? possible ret values for this open func?.
    //learn how to handle return val in meaningful way for errors

    //Open the DB file (new/existing)
    exit = sqlite3_open(file, &DB);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" << "FILE FAILED TO OPEN\n";
        return 1;
    }

    //initialize member table
    exit = sqlite3_exec(DB,MembTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
        return 2;
    }

    //initialize provider table
    exit = sqlite3_exec(DB,PrvdTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "PROVIDER TABLE FAILED:\t" << ErrMsg;
        return 3;
    }

    //initialize manager table
    exit = sqlite3_exec(DB,MgmrTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "SERVICE TABLE FAILED:\t" << ErrMsg;
        return 4;
    }

    //initialize service table
    exit = sqlite3_exec(DB,ServTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "SERVICE TABLE FAILED:\t" << ErrMsg;
        return 5;
    }

    exit = sqlite3_exec(DB,RecdTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "RECORD TABLE FAILED:\t" << ErrMsg;
        return 6;
    }

    std::cout << "\t-COMPLETE-\n";
    return 0;
}
