//Database header file
//Download SQLite from the developer at https://sqlite.org/download.html

#include "User.h"
#include <sys/stat.h>

#ifdef SQLITE3_H
#include <sqlite3.h>
#else
#include <sqlite/sqlite3.h>
#endif // sqlite3.h

#include <iostream>

class ChocAnDB {
public:
    ChocAnDB();
    ~ChocAnDB();
    int AddUser();
    int ModUser();
    int RmUser();
    User* GetUser();

protected:
    const char* file = "ChocAnDB_File.db";  //DB file name
    sqlite3* DB;                            //DB object
    sqlite3_stmt* STMT;                     //DB statement
    int OpenDB();
};
