#include "command.h"

void ln(int nargs, char *args[]){
  if(strcmp(args[1], "-s") == 0) symlink(args[2], args[3]);
  else link(args[1], args[2]);
}
