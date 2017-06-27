#include "command.h"

void pwd(int nargs){
  char pathname[SIZE * 8];
  getcwd(pathname, SIZE * 8);
  fprintf(stdout, "%s\n", pathname);
}
