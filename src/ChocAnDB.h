//Database header file
//Download SQLite from the developer at https://sqlite.org/download.html

#include "Manager.h"
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
     * provide userdata in an ident struct with no ID number. The assigned ID number
     * will be printed and returned.
     */

    //int ModUser();
    //int RmUser();
    int AddServ(int ServCD, char* ServNm, float fee, int &RetInt);
    int AddRecd(ident &UserID, int ProvID, int ServCD, char* comm, char* datetime, int &RetInt);
    /*Add a sevice to a memeber
     * Date of service format should be "YYYY-MM-DD"
     *
     */
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
