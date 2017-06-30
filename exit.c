#include "command.h"

/* プログラムを終了する */
void Exit(int nargs){
  if(nargs == 1) exit(0);
  else puts("Too many arguments");
}
