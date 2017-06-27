#include "mv.h"

void mv(int nargs, char *args[]){
  rename(args[1], args[2]);
}
