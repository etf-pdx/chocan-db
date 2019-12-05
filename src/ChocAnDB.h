//Database header file
//Download SQLite from the developer at https://sqlite.org/download.html

#include "Operator.h"
#include "SQL_exstention.cpp"
#include <cstring>
#include <sys/stat.h>
#include "sqlite/sqlite3.h"
#include <iostream>

//TODO: maybe change timezone from GMT to PST.


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

    int RmUser(char type, int UserID, int &RetInt);
    /*Remove user by ID
     *type char switch
     * 'm' - Member
     * 'p' - provider
     * 'g' - manager
     */

    int ReNewServ(int MembID, int &RetInt);
    //adds 30 days to a member status

    int AddServ(int ServCD, const char* ServNm, float fee, int &RetInt);
    //Add a service to the Provider directory

    int AddRecd(int MembID, int ProvID, int ServCD, char* comm, char* datetime, int &RetInt);
    /*Add a sevice to a memeber
     * Date of service format should be "YYYY-MM-DD HH:MM"
     */

    ident GetUser(char type, int UserID, int &RetInt);
    /*will return mangar/provider/member information through ident.
     *      *type char switch
     * 'm' - member
     * 'p' - provider
     * 'g' - manager
     *
     * return int:
     * 0 = ok
     * 1 = user not found
     *
     */

    //TODO: return reports.
    IDList* MBList(int &RenInt);

    Form* ProvDir(int &RetInt);
    //will return the full list of services
    //and return in a Form vetor

    ServRep* GetServRep(char type, int UserID, int &RetInt);
    //TODO: write report to file.
    /*will return provider/member service report.
    *      *type char switch
    * 'm' - member
    * 'p' - provider
    *
    * return int:
    * 0 = ok
    * 1 = user not found
    *
    */

protected:
    const char* file = "ChocAnDB_File.db";  //DB file name
    const char* test = "TestDB_File.db";    //DB file name
    char* ErrMsg;                           //SQL Error message
    sqlite3* DB;                            //DB object
    sqlite3_stmt* STMT;                     //DB statement
    int OpenDB(int RetInt);                           //DB initializer
    char* prepUser(char type,const ident UserID);


};
