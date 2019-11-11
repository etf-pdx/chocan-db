//Database header file

#include "User.h"
#include "sqlite3.h"
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


#endif //CHOCAN_CS320_07_CHOCANDB_H
