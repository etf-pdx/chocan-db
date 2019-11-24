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
                  "VALUES"
                  "       ("
                  "        '%s',"
                  "        '%s',"
                  "        '%s',"
                  "        '%s',"
                  "        '%d'"
                  "       );",UserID.name,UserID.address,UserID.city,UserID.state,UserID.zip);
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

//add a service to a member
int ChocAnDB::AddServ(ident &UserID, int ProvID, char* ServNm, float fee, char* comm, char* datetime, int &RetInt){
    RetInt = 0;
    char Buff[1024];
    char *Stmt = nullptr;
    RetInt = ChkFrm(datetime);
    if (RetInt)
        return -1;
    sprintf(Buff, "INSERT INTO SERVICE"
                  "("
                  "SERVICE_PROVIDED,"
                  "SERVICE_LOGGED,"
                  "SERVICE_NAME,"
                  "PROVIDER_ID,"
                  "MEMBER_NAME,"
                  "MEMBER_ID,"
                  "FEE,"
                  "COMMENT"
                  ")"
                  "VALUES"
                  "("
                  "DATETIME('%s'),"
                  "CURRENT_TIMESTAMP,"
                  "'%s',"
                  "'%d',"
                  "'%s',"
                  "'%d',"
                  "ROUND('%f',2),"
                  "'%s'"
                  ");",
            datetime, ServNm, ProvID, UserID.name, UserID.number, fee, comm);
    Stmt = new char[strlen(Buff)+1];
    strcpy(Stmt,Buff);
    RetInt = sqlite3_exec(DB,Stmt,nullptr,nullptr,&ErrMsg);
    if (RetInt != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "SERVICE TABLE FAILED:\t" << ErrMsg;
        return 4;
    }
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
                         "VALUES ("
                         "100000000,"
                         "'NAME',"
                         "'ADDRESS',"
                         "'CITY',"
                         "'AA',"
                         "00000);";

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
                         "VALUES ("
                         "200000000,"
                         "'NAME',"
                         "'ADDRESS',"
                         "'CITY',"
                         "'AA',"
                         "00000);";

    //TODO: Add managers database
    //TODO: Add active vs suspended members

    const char *actvTB = "create table IF NOT EXISTS ACTIVE("
                         "    START_DATE DATE NOT NULL, "
                         "    MONTHS_PAID INT,"
                         "    MEMBER_ID INT(9) NOT NULL, "
                         "    FOREIGN KEY (MEMBER_ID)"
                         "        REFERENCES MEMBER"
                         ");";


    const char *ServTB = "create table IF NOT EXISTS SERVICE (" //If Table does not exist it will be created
                         "    SERVICE_PROVIDED DATE NOT NULL ,"
                         "    SERVICE_LOGGED   DATE NOT NULL ,"
                         "    SERVICE_NAME     TEXT(20) NOT NULL ,"
                         "    PROVIDER_ID      INT(9) NOT NULL ,"
                         "    MEMBER_NAME      TEXT(25) NOT NULL ,"
                         "    MEMBER_ID        INT(9) NOT NULL ,"
                         "    FEE              REAL CHECK (FEE < 1000),"
                         "    COMMENT          TEXT(100),"
                         //Foreign key links to a primary key
                         "    FOREIGN KEY(MEMBER_ID)        REFERENCES MEMBER,"
                         "    FOREIGN KEY(PROVIDER_ID)      REFERENCES PROVIDER"
                         ");";
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

    //check for member table
    exit = sqlite3_exec(DB,MembTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
        return 2;
    }

    //check for provider table
    exit = sqlite3_exec(DB,PrvdTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "PROVIDER TABLE FAILED:\t" << ErrMsg;
        return 3;
    }

    //check for service table
    exit = sqlite3_exec(DB,ServTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "SERVICE TABLE FAILED:\t" << ErrMsg;
        return 4;
    }

    std::cout << "\t-COMPLETE-\n";
    return 0;
}
