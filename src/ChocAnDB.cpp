//
// Created by CBunt on 11/8/2019.
//

#include "ChocAnDB.h"

#define UNDEFINED           -1
#define DB_OK               0// Successful result
#define DB_FAILED           1
#define MEMBER_FAILED       2
#define PROVIDER_FAILED     3
#define MANAGER_FAILED      4
#define SERVICE_FAILED      5
#define RECORD_FAILED       6
#define STATUS_FAILED       7


//tsw- fixing warning. RetInt not defined before it is passed.
//don't think any time we want to create db without passing in an int
//unused. commenting out for now.
/*
ChocAnDB::ChocAnDB() { 
    ChocAnDB(0); 
}
*/

ChocAnDB::ChocAnDB(int &RetInt) {
    RetInt = 0;
    DB = nullptr;
    STMT = nullptr;
    ErrMsg = nullptr;
    RetInt = OpenDB(RetInt);
}

ChocAnDB::ChocAnDB(char t, int &RetInt) {
    DB = nullptr;
    STMT = nullptr;
    ErrMsg = nullptr;
    RetInt = OpenDB(1);
}

ChocAnDB::~ChocAnDB() {
    sqlite3_finalize(STMT);
    sqlite3_close(DB);
    DB = nullptr;
    STMT = nullptr;
    delete(ErrMsg);
}

int ChocAnDB::AddUser(char type, ident UserID, int &RetInt) {
    RetInt = DB_OK;
    char buff[1024];
    int IDnum;
    char *stmt = prepUser(type, UserID);
    std::cout << "UPDATING DATABASE:";

    switch (type) {
        case 'm' :
            RetInt = sqlite3_exec(DB, stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
                return RetInt = MEMBER_FAILED;
            }
            delete stmt;
            IDnum = sqlite3_last_insert_rowid(DB);
            stmt = "\0";
            buff[0] = '\0';
            sprintf(buff, "INSERT INTO STATUS (START_DATE, MONTHS_PAID, MEMBER_ID)"
                          "VALUES (CURRENT_DATE,1,%d);",IDnum);
            stmt = new char(strlen(buff)+1);
            strcpy(stmt,buff);
            RetInt = sqlite3_exec(DB, stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
                return RetInt = MEMBER_FAILED;
            }
            break;

        case 'p' :
            RetInt = sqlite3_exec(DB, stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "PROVIDER TABLE FAILED:\t" << ErrMsg;
                return RetInt = PROVIDER_FAILED ;
            }
            IDnum = sqlite3_last_insert_rowid(DB);
            break;
        case 'g':
            RetInt = sqlite3_exec(DB, stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "MANAGER TABLE FAILED:\t" << ErrMsg;
                return RetInt = MANAGER_FAILED;
            }
            IDnum = sqlite3_last_insert_rowid(DB);
            break;
        default:
            return UNDEFINED;
    }
    std::cout << "\t-UPDATE SUCCESSFUL-\n" << "\tID NUMBER:\t" << IDnum << std::endl;
    delete(stmt);
    return IDnum;
}

int ChocAnDB::ModUser(char type, ident UserID, int &RetInt) {
    char* Stmt;
    Stmt = ModPrep(UserID);
    switch(type){
        case 'm':
            RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
                return RetInt = MEMBER_FAILED;
            }
            break;
        case 'p':
            RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "PROVIDER TABLE FAILED:\t" << ErrMsg;
                return RetInt = PROVIDER_FAILED ;
            }
            break;
        case 'g':
            RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "MANAGER TABLE FAILED:\t" << ErrMsg;
                return RetInt = MANAGER_FAILED;
            }
            break;
        default:
            return RetInt = UNDEFINED ;
    }
    return RetInt = DB_OK;
}

char* ChocAnDB::ModPrep(const ident UserID) {
    char *buff1 = new char ('\0');
    char *buff2 = new char ('\0');
    char *ret = nullptr;
    if (UserID.name.c_str())
    {
        sprintf(buff1,"UPDATE MEMBER SET NAME = '%s' WHERE ID = '%d';",UserID.name.c_str(),UserID.number);
        strcat(buff2,buff1);
    }
    if (UserID.address.c_str())
    {
        sprintf(buff1,"UPDATE MEMBER SET ADDRESS = '%s' WHERE ID = '%d';",UserID.address.c_str(),UserID.number);
        strcat(buff2,buff1);
    }
    if (UserID.city.c_str())
    {
        sprintf(buff1,"UPDATE MEMBER SET CITY = '%s' WHERE ID = '%d';",UserID.city.c_str(),UserID.number);
        strcat(buff2,buff1);
    }
    if (UserID.state.c_str())
    {
        sprintf(buff1,"UPDATE MEMBER SET STATE = '%s' WHERE ID = '%d';",UserID.city.c_str(),UserID.number);
        strcat(buff2,buff1);
    }
    if (UserID.zip)
    {
        sprintf(buff1,"UPDATE MEMBER SET ZIP = '%d' WHERE ID = '%d';",UserID.zip,UserID.number);
        strcat(buff2,buff1);
    }
    strcpy(buff1,buff2);
    ret = new char[strlen(buff1)+1];
    strcpy(ret,buff1);
    return ret;
}

int ChocAnDB::RmUser(char type, int UserID, int &RetInt){
    RetInt = DB_OK;
    char Buff[1024];
    char *Stmt = nullptr;
    std::cout << "UPDATING DATABASE:";
    switch (type){
        case 'm':
            sprintf(Buff,"DELETE FROM MEMBER WHERE ID = %d",UserID);
            Stmt = new char[strlen(Buff) + 1];
            strcpy(Stmt, Buff);
            RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
                return RetInt = MEMBER_FAILED;
            }
            break;
        case 'p':
            sprintf(Buff,"DELETE FROM PROVIDER WHERE ID = %d",UserID);
            Stmt = new char[strlen(Buff) + 1];
            strcpy(Stmt, Buff);
            RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "PROVIDER TABLE FAILED:\t" << ErrMsg;
                return RetInt = PROVIDER_FAILED;
            }
            break;
        case 'g':
            sprintf(Buff,"DELETE FROM MANAGER WHERE ID = %d",UserID);
            Stmt = new char[strlen(Buff) + 1];
            strcpy(Stmt, Buff);
            RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
            if (RetInt != DB_OK) {
                std::cout << "\t-FAILED-\n" << "MANAGER TABLE FAILED:\t" << ErrMsg;
                return RetInt = MANAGER_FAILED;
            }
            break;
        default:
            return RetInt = UNDEFINED ;

    }
    return DB_OK;
}

char *ChocAnDB::prepUser(char type, ident UserID) {
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
            UserID.name.c_str(), UserID.address.c_str(), UserID.city.c_str(), UserID.state.c_str(), UserID.zip);
    switch (type) {
        case 'm' :
            ret = new char[strlen(Stmt) + 19];
            strcpy(ret, "INSERT INTO MEMBER");
            strcat(ret, Stmt);
            break;
        case 'p' :
            ret = new char[strlen(Stmt) + 21];
            strcpy(ret, "INSERT INTO PROVIDER");
            strcat(ret, Stmt);
            break;
        case 'g' :
            ret = new char[strlen(Stmt) + 20];
            strcpy(ret, "INSERT INTO MANAGER");
            strcat(ret, Stmt);
            break;
        default:
            return nullptr;
    }

    return ret;
}

int ChocAnDB::AddServ(int ServCD, const char *ServNm, float fee, int &RetInt) {
    RetInt = DB_OK;
    char Buff[1024];
    char *Stmt = nullptr;
    std::cout << "UPDATING DATABASE:";
    sprintf(Buff, "INSERT OR IGNORE INTO SERVICE ("
                  "SERVICE_CODE, SERVICE_NAME, FEE)"
                  "VALUES ( '%d','%s',ROUND('%f',2)"
                  ");", ServCD, ServNm, fee);
    Stmt = new char[strlen(Buff) + 1];
    strcpy(Stmt, Buff);
    RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
    if (RetInt != DB_OK) {
        std::cout << "\t-FAILED-\n" << "SERVICE TABLE FAILED:\t" << ErrMsg;
        return RetInt = SERVICE_FAILED;
    }
    int SVnum = sqlite3_last_insert_rowid(DB);
    std::cout << "\t-UPDATE SUCCESSFUL-\n" << "\tSERVICE CODE:\t" << SVnum << std::endl;

    return SVnum;
}

int ChocAnDB::ReNewServ(int MembID, int &RetInt){
    RetInt = DB_OK;
    char Buff[1024];
    char *Stmt = nullptr;
    std::cout << "UPDATING DATABASE:";
    sprintf(Buff,"UPDATE STATUS SET MONTHS_PAID = MONTHS_PAID + 1 WHERE MEMBER_ID = %d",MembID);
    Stmt = new char[strlen(Buff) + 1];
    strcpy(Stmt, Buff);
    RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
    if (RetInt != DB_OK) {
        std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
        return RetInt = STATUS_FAILED ;
    }
    return DB_OK;
}

//add a service to a member
int ChocAnDB::AddRecd(int MembID, int ProvID, int ServCD, const char *comm, const char *datetime, int &RetInt) {
    RetInt = 0;
    char Buff[1024];
    char *Stmt = nullptr;
    if (RetInt)
        return -1;
    std::cout << "UPDATING DATABASE:";
    sprintf(Buff, "INSERT INTO RECORD"
                  "(SERVICE_PROVIDED,"
                  "SERVICE_LOGGED,"
                  "SERVICE_CODE,"
                  "PROVIDER_ID,"
                  "PROVIDER_NAME,"
                  "MEMBER_ID,"
                  "MEMBER_NAME,"
                  "COMMENT)"
                  "VALUES ("
                  "DATETIME('%s'),"
                  "CURRENT_DATE,"
                  "'%d','%d',"
                  "(SELECT NAME FROM PROVIDER WHERE PROVIDER_ID = '%d'),'%d',"
                  "(SELECT MEMBER_NAME FROM MEMBER WHERE MEMBER_ID = '%d'),'%s');",
                  datetime, ServCD, ProvID, ProvID, MembID, MembID, comm);
    Stmt = new char[strlen(Buff) + 1];
    strcpy(Stmt, Buff);
    RetInt = sqlite3_exec(DB, Stmt, nullptr, nullptr, &ErrMsg);
    if (RetInt != DB_OK) {
        std::cout << "\t-FAILED-\n" << "SERVICE TABLE FAILED:\t" << ErrMsg;
        return RetInt = SERVICE_FAILED;
    }

    std::cout << "\t-UPDATE SUCCESSFUL-\n" << "\tSERVICE CODE:\t" << ServCD << std::endl;

    return DB_OK;
}

ident ChocAnDB::GetUser(char type, int UserID, int &RetInt) {
    std::cout << "CALLING DATABASE:\t";
    RetInt = DB_OK;
    char buff[1024];
    ident *data = new ident;
    int *ID = new int(-1);
    char *Stmt;
    switch (type){
        case 'm':
            Stmt = new char[42];
            sprintf(buff,"SELECT * FROM MEMBER WHERE ID = %d",UserID);
            strcpy(Stmt,buff);

            RetInt = sqlite3_exec(DB, Stmt, reinterpret_cast<int (*)(void *, int, char **, char **)>(FillID), data, &ErrMsg);
            if(!data->number)
                RetInt = MEMBER_FAILED;
            delete(Stmt);
            if (RetInt)
                return *data;
            sprintf(buff,"SELECT CAST(julianday((SELECT START_DATE FROM STATUS WHERE MEMBER_ID = %d))"
                   "+ (30 * (SELECT MONTHS_PAID FROM STATUS WHERE MEMBER_ID = %d))"
                   "- (julianday('NOW'))AS INTEGER)",data->number,data->number);
            Stmt = new char[strlen(buff)+1];
            strcpy(Stmt,buff);
            RetInt = sqlite3_exec(DB, Stmt, reinterpret_cast<int (*)(void *, int, char **, char **)>(GetStat), ID, &ErrMsg);
            if (0 > *ID)
                data->status = false;
            if (0 <= *ID)
                data->status = true;
            std::cout << "-FOUND-\n" << "\tNAME:\t\t\t" << data->name << std::endl;
            break;
        case 'p':
            Stmt = new char[44];
            sprintf(buff,"SELECT * FROM PROVIDER WHERE ID = %d",UserID);
            strcpy(Stmt,buff);

            RetInt = sqlite3_exec(DB, Stmt, reinterpret_cast<int (*)(void *, int, char **, char **)>(FillID), data, &ErrMsg);
            if (RetInt != DB_OK)
                return *data;
            if(!data->number)
                RetInt = PROVIDER_FAILED;
            delete(Stmt);
            std::cout << "-FOUND-\n" << "\tNAME:\t\t\t" << data->name << std::endl;
            break;
        case 'g':
            Stmt = new char[43];
            sprintf(buff,"SELECT * FROM MANAGER WHERE ID = %d",UserID);
            strcpy(Stmt,buff);

            RetInt = sqlite3_exec(DB, Stmt, reinterpret_cast<int (*)(void *, int, char **, char **)>(FillID), data, &ErrMsg);
            if (RetInt != DB_OK)
                return *data;
            if(!data->number)
                RetInt = MANAGER_FAILED;
            delete(Stmt);
            std::cout << "-FOUND-\n" << "\tNAME:\t\t\t" << data->name << std::endl;
            break;
        default:
            RetInt = UNDEFINED;
    }

    RetInt = DB_OK;
    return *data;
}

IDList* ChocAnDB::MBList(int &RetInt) {
    IDList * Ret = new IDList;
    const char* Stmt = "SELECT ID FROM MEMBER;";
    RetInt = sqlite3_exec(DB, Stmt, reinterpret_cast<int (*)(void*, int, char**, char**)>(IDlist), Ret, &ErrMsg);
    return Ret; 
} 

Form* ChocAnDB::ProvDir(int &RetInt) {
    Form* Ret = new Form;
	const char* Stmt = "SELECT * FROM SERVICE;";
	RetInt = sqlite3_exec(DB, Stmt, reinterpret_cast<int (*)(void*, int, char**, char**)>(SVlist), Ret, &ErrMsg);
	return Ret;
}

ServRep* ChocAnDB::GetServRep(char type, int UserID,int &RetInt) {
    std::string Stmt;
    ServRep *Ret = new ServRep;
    switch(type){
        case 'm':
            Stmt = "SELECT * FROM RECORD WHERE MEMBER_ID = " + UserID;
            break;
        case 'p':
            Stmt = "SELECT * FROM RECORD WHERE PROVIDER_ID = " + UserID;
        default:
            return nullptr;
    }
    RetInt = sqlite3_exec(DB, Stmt.c_str(), reinterpret_cast<int (*)(void *, int, char **, char **)>(GetRep), Ret, &ErrMsg);
    return Ret;
}

int ChocAnDB::OpenDB(int RetInt) {
    const char *MembTB = "create table IF NOT EXISTS MEMBER ("  //If Table does not exist it will be created
                         "    ID      INTEGER CHECK (ID < 999999999)"
                         "                      primary key AUTOINCREMENT ,"                 //Primary key makes ID's unique
                         "    NAME    TEXT(25) NOT NULL ,"
                         "    ADDRESS TEXT(25) NOT NULL ,"
                         "    CITY    TEXT(14) NOT NULL ,"
                         "    STATE   TEXT(2) NOT NULL ,"
                         "    ZIP     INT(5) NOT NULL "
                         "); INSERT OR IGNORE INTO MEMBER"
                         "(ID,NAME,ADDRESS,CITY,STATE,ZIP) "
                         "        VALUES ("
                         "        300000000,"
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

    const char *MgmrTB = "create table IF NOT EXISTS MANAGER ("
                         "    ID      INTEGER CHECK (ID < 199999999)"
                         "        primary key autoincrement,"
                         "    NAME    CHARACTER(25) not null,"
                         "    ADDRESS CHARACTER(25),"
                         "    CITY    CHARACTER(14),"
                         "    STATE   CHARACTER(2),"
                         "    ZIP     INT(5)"
                         ");INSERT OR IGNORE INTO MANAGER"
                         "(ID,NAME,ADDRESS,CITY,STATE,ZIP)"
                         "        VALUES ("
                         "        100000000,"
                         "        'NAME',"
                         "        'ADDRESS',"
                         "        'CITY',"
                         "        'AA',"
                         "        00000);";

    const char *StatTB = "create table IF NOT EXISTS STATUS("
                         "    STATUS_ID        INT PRIMARY KEY     NOT NULL, "
                         "    START_DATE       DATE NOT NULL, "
                         "    MONTHS_PAID      INT,"
                         "    MEMBER_ID        INT(9) NOT NULL, "
                         "    FOREIGN KEY (MEMBER_ID)"
                         "        REFERENCES MEMBER);";

    const char *RecdTB = "create table IF NOT EXISTS RECORD (" //If Table does not exist it will be created
                         "    RECORD_ID        INT PRIMARY KEY     NOT NULL, "
                         "    SERVICE_PROVIDED DATE NOT NULL ,"
                         "    SERVICE_LOGGED   DATE NOT NULL ,"
                         "    SERVICE_CODE     INT(6) NOT NULL,"
                         "    PROVIDER_ID      INT(9) NOT NULL,"
                         "    PROVIDER_NAME    TEXT(25) NOT NULL,"
                         "    MEMBER_ID        INT(9) NOT NULL ,"
                         "    MEMBER_NAME      TEXT(25) NOT NULL,"
                         "    COMMENT          TEXT(100)," //Foreign key links to a primary key
                         "    FOREIGN KEY(MEMBER_ID)        REFERENCES MEMBER,"
                         "    FOREIGN KEY(PROVIDER_ID)      REFERENCES PROVIDER,"
                         "    FOREIGN KEY(SERVICE_CODE)     REFERENCES SERVICE);";
    
    const char *ServTB = "create table IF NOT EXISTS SERVICE ("
                         "    SERVICE_CODE INTEGER NOT NULL "
                         "        primary key,"
                         "    SERVICE_NAME TEXT(20) NOT NULL, "
                         "    FEE          REAL CHECK (FEE < 1000));";

    int exit = DB_OK;
    std::cout << "PREPARING DATABASE:";
    //trent- error checking? possible ret values for this open func?.
    //learn how to handle return val in meaningful way for errors

    //Open the DB file (new/existing)
    switch (RetInt) {
        case 0:
            exit = sqlite3_open(file, &DB);
            break;
        case 1:
            exit = sqlite3_open(test, &DB);
            break;
        default:
            exit = sqlite3_open(file, &DB);
            break;
    }
    if (exit != DB_OK) {
        std::cout << "\t-FAILED-\n" << "FILE FAILED TO OPEN\n";
        return DB_FAILED;
    }

    //initialize member table
    exit = sqlite3_exec(DB, MembTB, nullptr, nullptr, &ErrMsg);
    if (exit != DB_OK) {
        std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
        return MEMBER_FAILED ;
    }

    //initialize provider table
    exit = sqlite3_exec(DB, PrvdTB, nullptr, nullptr, &ErrMsg);
    if (exit != DB_OK) {
        std::cout << "\t-FAILED-\n" << "PROVIDER TABLE FAILED:\t" << ErrMsg;
        return PROVIDER_FAILED;
    }

    //initialize manager table
    exit = sqlite3_exec(DB, MgmrTB, nullptr, nullptr, &ErrMsg);
    if (exit != DB_OK) {
        std::cout << "\t-FAILED-\n" << "MANAGER TABLE FAILED:\t" << ErrMsg;
        return MANAGER_FAILED;
    }

    //initialize service table
    exit = sqlite3_exec(DB, ServTB, nullptr, nullptr, &ErrMsg);
    if (exit != DB_OK) {
        std::cout << "\t-FAILED-\n" << "SERVICE TABLE FAILED:\t" << ErrMsg;
        return SERVICE_FAILED;
    }

    exit = sqlite3_exec(DB, RecdTB, nullptr, nullptr, &ErrMsg);
    if (exit != DB_OK) {
        std::cout << "\t-FAILED-\n" << "RECORD TABLE FAILED:\t" << ErrMsg;
        return RECORD_FAILED;
    }

    exit = sqlite3_exec(DB, StatTB, nullptr, nullptr, &ErrMsg);
    if (exit != DB_OK) {
        std::cout << "\t-FAILED-\n" << "STATUS TABLE FAILED:\t" << ErrMsg;
        return STATUS_FAILED;
    }

    std::cout << "\t-COMPLETE-\n";
    return DB_OK;
}
