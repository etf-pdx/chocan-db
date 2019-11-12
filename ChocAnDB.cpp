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
    //learn how to handle return val
    return sqlite3_open(file, &DB);
}
