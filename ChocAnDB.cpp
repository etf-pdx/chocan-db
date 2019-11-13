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
    sqlite3_finalize();
    sqlite3_close(DB);
    delete DB;
    DB = NULL;
}

int ChocAnDB::OpenDB()
{
    squlite3_open(file, &DB);
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
               ")"
