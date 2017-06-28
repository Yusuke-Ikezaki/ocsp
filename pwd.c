#include "command.h"

#define PATHSIZE 128

void pwd(int nargs){
  char pathname[PATHSIZE];
  getcwd(pathname, PATHSIZE);
  fprintf(stdout, "%s\n", pathname);
}
