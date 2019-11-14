//
// Created by CBunt on 11/8/2019.
//

#include "ChocAnDB.h"

ChocAnDB::ChocAnDB()
{
    OpenDB();
}

ChocAnDB::~ChocAnDB()
{
    //trent- The sqlite3_finalize() function is called to delete a [prepared statement].
    //will be used elsewhere.
    //sqlite3_finalize();

    //trent- successful sqlite3_close() call deallocates all so no need for delete.
    //learn how to handle SQLITE_API objects because sucessful function call rets SQLITE_OK
    sqlite3_close(DB);
    //delete DB;
    DB = NULL;
}

int ChocAnDB::OpenDB()
{
    //trent- error checking? possible ret values for this open func?.
    //learn how to handle return val in meaningful way for errors 
    return sqlite3_open(file, &DB);
}

char *MembTB = "create table MEMBER\n"
               "(\n"
               "    ID      INT\n"
               "        primary key,\n"
               "    NAME    TEXT,\n"
               "    ADDRESS TEXT,\n"
               "    CITY    TEXT,\n"
               "    STATE   char(2),\n"
               "    ZIP     INT\n"
               ")";


char *PrvdTB = "create table PROVIDER\n"
               "(\n"
               "    ID      INT\n"
               "        primary key,\n"
               "    NAME    TEXT,\n"
               "    ADDRESS TEXT,\n"
               "    CITY    TEXT,\n"
               "    STATE   char(2),\n"
               "    ZIP     INT\n"
               ")";


char *ServTB = "create table SERVICE\n"
               "(\n"
               "    SERVICE_PROVIDED DATE,\n"
               "    SERVICE_LOGGED   DATE,\n"
               "    SERVICE_NAME     DATE,\n"
               "    PROVIDER_ID      INT,\n"
               "    MEMBER_NAME      TEXT,\n"
               "    MEMBER_ID        INT\n"
               "        references MEMBER,\n"
               "    FEE              DECIMAL\n"
               ")";
