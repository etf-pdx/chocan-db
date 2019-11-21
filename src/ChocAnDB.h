//Database header file
//Download SQLite from the developer at https://sqlite.org/download.html

#include "User.h"
#include <sys/stat.h>
#include "sqlite/sqlite3.h"
#include <iostream>

class ChocAnDB {
public:
    ChocAnDB();
    ChocAnDB(int &RetInt);
    ~ChocAnDB();
    /*Add User both
     *            */
    int AddUser(char type,ident &UserID, int &RetInt);
    //int ModUser();
    //int RmUser();
    int MkServ(ident &UserID, int ProvID, char* ServNm, float fee, char* comm, char* datetime, int &RetInt);
    //User* GetUser();

protected:
    const char* file = "ChocAnDB_File.db";  //DB file name
    char* ErrMsg;                           //SQL Error message
    sqlite3* DB;                            //DB object
    sqlite3_stmt* STMT;                     //DB statement
    int OpenDB();                           //DB initializer
    int RetInt = 0;                         //return error code.
    int ChkFrm(char* datetime);             //This will check formatting return 0 if correct
};
