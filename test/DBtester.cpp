//
// Created by CBunt on 11/20/2019.
//

#include <time.h>
#include <fstream>
#include "../src/ChocAnDB.h"

int main(){
  time_t rawtime;
  struct tm *ptm;
  time(&rawtime);
  ptm = gmtime(&rawtime);
  FILE *log;
  log = fopen("TEST.LOG","w");
  ChocAnDB *DB;
  fprintf(log, "TESTING CHOCAN DATABASE: %2d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min);
  DB = new ChocAnDB;
  delete DB;
  fprintf(log, "TEST COMPLETE: %2d:%02d\n", (ptm->tm_hour)%24, ptm->tm_min);
  fclose(log);
  return 0;
}
