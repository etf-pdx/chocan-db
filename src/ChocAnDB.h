//Database header file
//Download SQLite from the developer at https://sqlite.org/download.html

#include "User.h"
#include <cstring>
#include <sys/stat.h>
#include "sqlite/sqlite3.h"
#include <iostream>
//TODO: Add database functionality for active/expired users.
class ChocAnDB {
public:
    ChocAnDB();
    ChocAnDB(int &RetInt);
    ~ChocAnDB();

    int AddUser(char type, ident UserID, int &RetInt);
    /*Add Members, providers, and managers
     *type char switch
     * 'm' - Member
     * 'p' - provider
     * 'g' - manager
     * provided userdate in an ident struct with no ID number. The assigned ID number
     * will be printed and returned.
     */

    //int ModUser();
    //int RmUser();
    int AddServ(ident &UserID, int ProvID, char* ServNm, float fee, char* comm, char* datetime, int &RetInt);
    //ident* GetUser(int IDnum);

    //TODO: return reports.

protected:
    const char* file = "ChocAnDB_File.db";  //DB file name
    char* ErrMsg;                           //SQL Error message
    sqlite3* DB;                            //DB object
    sqlite3_stmt* STMT;                     //DB statement
    int OpenDB();                           //DB initializer
    int ChkFrm(char* datetime);             //This will check formatting return 0 if correct
    char* prepUser(char type,const ident UserID);
};
