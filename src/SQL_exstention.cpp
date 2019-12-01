//
//Static functions used to write back data from SQL DB
//

//Test template

static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char *) data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

static int FillID(ident *data, int argc, char **argv, char **azColName){
    ident *Ret = data;

    Ret->number = atoi(argv[0]);
    Ret->name = new char[strlen(argv[1]+1)];
    strcpy(Ret->name, argv[1]);
    Ret->address = new char[strlen(argv[2]+1)];
    strcpy(Ret->address, argv[2]);
    Ret->city = new char[strlen(argv[3]+1)];
    strcpy(Ret->city, argv[3]);
    Ret->state = new char[strlen(argv[4]+1)];
    strcpy(Ret->state, argv[4]);
    Ret->zip = atoi(argv[5]);

    return 0;
}

static int GetStat(int* Ret, int argc, char **argv, char **azColName){
/*    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }*/

    *Ret= atoi(argv[0]);

    return 0;
}

static int SVlist(Form *Ret, int argc, char **argv, char **azColName) {
    char *buff1 = new char ('\n');
    char *buff2 = new char ('\n');
    char *ret = nullptr;
    try {

          for (int i = 0; i < argc; i++) {
            sprintf(buff1,"%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            strcat(buff2,buff1);
        } //TODO: fix formating so ret does not chop the ends
          strcpy(buff1,buff2);
          ret = new char[strlen(buff1)+1];
          strcpy(ret,buff1);
          Ret->emplace_back(ret);
    }
    catch (...) {
        // abort select on failure, don't let exception propogate thru sqlite3 call-stack
        return 1;
    }
    //delete(buff1);
    //delete(buff2);
    //delete(ret);
    return 0;
}

/*
int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
    List* records = static_cast<List*>(p_data);
    try {
        records->emplace_back(p_fields, p_fields + num_fields);
    }
    catch (...) {
        // abort select on failure, don't let exception propogate thru sqlite3 call-stack
        return 1;
    }
    return 0;
}*/
