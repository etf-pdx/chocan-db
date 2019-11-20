//Database header file

#include "User.h"

#ifdef SQLITE3_H
#include <sqlite3.h>
#else
#include <winsqlite/winsqlite3.h>
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
    const char* file = "ChocAnDB_File.db";
    sqlite3* DB;
    int OpenDB();
};

