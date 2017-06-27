#include "rm.h"

void rm(int nargs, char *args[]){
  int i;
  for(i = 1; i < nargs; i++)
    remove(args[i]);
}
