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

int ChocAnDB::AddUser(char type,ident &UserID, int &RetInt) {
    RetInt = 0;
    char *Stmt;
    Stmt = "INSERT INTO MEMBER\n"
           "    (\n"
           "     NAME,\n"
           "     ADDRESS,\n"
           "     CITY,\n"
           "     STATE,\n"
           "     ZIP\n"
           "    )\n"
           "VALUES\n"
           "       (\n"
           "        'name',\n"
           "        'address',\n"
           "        'city',\n"
           "        'state',\n"
           "        'zip'\n"
           "       )";
    std::cout << "PREPARING DATABASE:";
    RetInt = sqlite3_exec(DB,Stmt,nullptr,nullptr,&ErrMsg);
    if (RetInt != SQLITE_OK){
        std::cout << "\t-FAILED-\n" << "MEMBER TABLE FAILED:\t" << ErrMsg;
        return RetInt = 2;
    }
    return UserID.number = sqlite3_last_insert_rowid(DB);

}

//add a service to a member
int ChocAnDB::MkServ(ident &UserID, int ProvID, char* ServNm, float fee, char* comm, char* datetime, int &RetInt){
    RetInt = 0;
    char *Stmt;
    RetInt = ChkFrm(datetime);
    if (RetInt)
        return -1;
    sprintf(Stmt, "INSERT INTO SERVICE\n"
               "(\n"
               "SERVICE_PROVIDED,\n"
               "SERVICE_LOGGED,\n"
               "SERVICE_NAME,\n"
               "PROVIDER_ID,\n"
               "MEMBER_NAME,\n"
               "MEMBER_ID,\n"
               "FEE,\n"
               "COMMENT\n"
               ")\n"
               "VALUES\n"
               "(\n"
               "DATETIME('%s'),\n"
               "CURRENT_DATE,\n"
               "'s%',\n"
               "'d%',\n"
               "'s%',\n"
               "'%d',\n"
               "'%f',\n"
               "'%s'\n"
               ")",
               datetime, ServNm, ProvID, UserID.name, UserID.number, fee, comm);

    RetInt = sqlite3_exec(DB,Stmt,nullptr,nullptr,&ErrMsg);
    if (RetInt != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "SERVICE TABLE FAILED:\t" << ErrMsg;
        return 4;
    }
    return 0;
}


//This will check formatting return 0 if correct
int ChocAnDB::ChkFrm(char *datetime) {
    return 0;
}

int ChocAnDB::OpenDB() {
    const char *MembTB = "create table IF NOT EXISTS MEMBER (\n"  //If Table does not exist it will be created
                         "    ID      INT(9)"// DEFAULT 1000000000 CHECK (ID < 1999999999)\n" //
                         "                      primary key,\n"                 //Primary key makes ID's unique
                         "    NAME    TEXT(25) NOT NULL ,\n"
                         "    ADDRESS TEXT(25) NOT NULL ,\n"
                         "    CITY    TEXT(14) NOT NULL ,\n"
                         "    STATE   TEXT(2) NOT NULL ,\n"
                         "    ZIP     INT(5) NOT NULL \n"
                         ")";

    const char *PrvdTB = "create table IF NOT EXISTS PROVIDER (\n"//If Table does not exist it will be created
                         "    ID      INT(9) CHECK (ID > 200000000) CHECK (ID < 299999999)\n"
                         "                     NOT NULL primary key,\n"                 //Primary key makes ID's unique
                         "    NAME    TEXT(25) NOT NULL ,\n"
                         "    ADDRESS TEXT(25) NOT NULL ,\n"
                         "    CITY    TEXT(14) NOT NULL ,\n"
                         "    STATE   TEXT(2) NOT NULL ,\n"
                         "    ZIP     INT(5) NOT NULL \n"
                         ")";

    //Probably need to make manger table

    const char *ServTB = "create table IF NOT EXISTS SERVICE (\n" //If Table does not exist it will be created
                         "    SERVICE_PROVIDED DATE NOT NULL ,\n"
                         "    SERVICE_LOGGED   DATE NOT NULL ,\n"
                         "    SERVICE_NAME     TEXT(20) NOT NULL ,\n"
                         "    PROVIDER_ID      INT(9) NOT NULL ,\n"
                         "    MEMBER_NAME      TEXT(25) NOT NULL ,\n"
                         "    MEMBER_ID        INT(9) NOT NULL ,\n"
                         "    FEE              DECIMAL CHECK (FEE < 1000),\n"
                         "    COMMENT          TEXT(100),"
                         "    FOREIGN KEY(MEMBER_ID)\n"           //Foreign key links to a primary key
                         "        REFERENCES MEMBER\n"
                         ")";
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
    sqlite3_exec(DB,PrvdTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "PROVIDER TABLE FAILED:\t" << ErrMsg;
        return 3;
    }

    //check for service table
    sqlite3_exec(DB,ServTB,nullptr,nullptr,&ErrMsg);
    if (exit != SQLITE_OK){
        std::cout << "\t-FAILED-\n" <<  "SERVICE TABLE FAILED:\t" << ErrMsg;
        return 4;
    }

    std::cout << "\t-COMPLETE-\n";
    return 0;
}
