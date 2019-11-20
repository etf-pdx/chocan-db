//
// Created by CBunt on 11/8/2019.
//

#include "ChocAnDB.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwritable-strings"

ChocAnDB::ChocAnDB()
{
    DB = NULL;
    STMT = NULL;
    OpenDB();
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
    DB = NULL;
    STMT = NULL;
}



int ChocAnDB::OpenDB() {
    const char *MembTB = "create table IF NOT EXISTS MEMBER (\n"  //If Table does not exist it will be created
                         "    ID      INT\n"
                         "        primary key,\n"                 //Primary key makes ID's unique
                         "    NAME    TEXT,\n"
                         "    ADDRESS TEXT,\n"
                         "    CITY    TEXT,\n"
                         "    STATE   char(2),\n"
                         "    ZIP     INT\n"
                         ")";

    const char *PrvdTB = "create table IF NOT EXISTS PROVIDER (\n"//If Table does not exist it will be created
                         "    ID      INT\n"
                         "        primary key,\n"                 //Primary key makes ID's unique
                         "    NAME    TEXT,\n"
                         "    ADDRESS TEXT,\n"
                         "    CITY    TEXT,\n"
                         "    STATE   char(2),\n"
                         "    ZIP     INT\n"
                         ")";

    const char *ServTB = "create table IF NOT EXISTS SERVICE (\n" //If Table does not exist it will be created
                         "    SERVICE_PROVIDED DATE,\n"
                         "    SERVICE_LOGGED   DATE,\n"
                         "    SERVICE_NAME     TEXT,\n"
                         "    PROVIDER_ID      INT,\n"
                         "    MEMBER_NAME      TEXT,\n"
                         "    MEMBER_ID        INT,\n"
                         "    FEE              DECIMAL,\n"
                         "    FOREIGN KEY(MEMBER_ID)\n"           //Foreign key links to a primary key
                         "        references MEMBER\n"
                         ")";

    std::cout << "PREPARING DATABASE:";
    //trent- error checking? possible ret values for this open func?.
    //learn how to handle return val in meaningful way for errors

    //Open the DB file (new/existing)
    if (sqlite3_open(file, &DB)) {
        std::cout << "\t-FAILED-\n";
        return 1;
    }

    //check for member table
    if (sqlite3_prepare_v2(DB,MembTB,-1,&STMT,NULL)){
        std::cout << "\t-FAILED-\n";
        return 1;
    }
    if (sqlite3_step(STMT)){
        std::cout << "\t-FAILED-\n";
        return 1;
    }

    //check for provider table
    if (sqlite3_prepare_v2(DB,PrvdTB,-1,&STMT,NULL)){
        std::cout << "\t-FAILED-\n";
        return 1;
    }
    if (sqlite3_step(STMT)){
        std::cout << "\t-FAILED-\n";
        return 1;
    }

    //check for service table
    if (sqlite3_prepare_v2(DB,ServTB,-1,&STMT,NULL)){
        std::cout << "\t-FAILED-\n";
        return 1;
    }
    if (sqlite3_step(STMT)){
        std::cout << "\t-FAILED-\n";
        return 1;
    }

    std::cout << "\t-COMPLETE-\n";
    return 0;
}

#pragma clang diagnostic pop