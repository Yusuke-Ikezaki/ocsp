#include "command.h"

void mkdir(int nargs, char *args[]){
  /* 引数がない場合 */
  if(nargs == 1){
    puts("There are no arguments"); return;
  }

  int i;
  for(i = 1; i < nargs; i++)
    if(mkdir(args[i], S_IRUSR) == -1);
}
