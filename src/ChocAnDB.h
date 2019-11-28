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
    ChocAnDB(char t,int&RetInt);
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
    ident& GetUser(int UserID, int &RetInt);
    /*will return mangar/provider/member information through ident.
     * return int:
     * 0 = ok
     * 1 = user not found
     *
     */
    //TODO: return reports.
    char* ProvDir();
    //will return the full list of services

protected:
    const char* file = "ChocAnDB_File.db";  //DB file name
    const char* test = "TestDB_File.db";  //DB file name
    char* ErrMsg;                           //SQL Error message
    sqlite3* DB;                            //DB object
    sqlite3_stmt* STMT;                     //DB statement
    int OpenDB(int RetInt);                           //DB initializer
    int ChkFrm(char* datetime);             //This will check formatting return 0 if correct
    char* prepUser(char type,const ident UserID);
    //this function returns the requested info from the database
    int callback(void *data, int argc, char **argv, char **azColName);
};
