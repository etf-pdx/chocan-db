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

static int SVlist(void *Ret, int argc, char **argv, char **azColName) {
    char *buff;

    char *ret = new char('\0');
    for (int i = 0; i < argc; i++) {
        sprintf(buff,"%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        strcat(ret,buff);
    }

    strcat(reinterpret_cast<char(*)>(Ret),ret);

    return 0;
}

