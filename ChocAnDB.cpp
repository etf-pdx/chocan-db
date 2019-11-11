//
// Created by veteran on 11/8/2019.
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