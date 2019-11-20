//Database header file
//Download SQLite from the developer at https://sqlite.org/download.html

#include "User.h"
#include <sys/stat.h>
#include "sqlite/sqlite3.h"
#include <iostream>

class ChocAnDB {
public:
    ChocAnDB(int &RetInt);
    ~ChocAnDB();
    //int AddUser();
    //int ModUser();
    //int RmUser();
    //User* GetUser();

protected:
    const char* file = "ChocAnDB_File.db";  //DB file name
    char* ErrMsg;                           //SQL Error message
    sqlite3* DB;                            //DB object
    sqlite3_stmt* STMT;                     //DB statement
    int OpenDB();                           //DB initializer
    int RetInt = 0;                         //return error code.
};
