#include "command.h"

/* ファイルの削除 */
void rm(int nargs, char *args[]){
  /* 引数がない場合 */
  if(nargs == 1){
    puts("There are no arguments"); return;
  }

  /* 引数のファイルを削除 */
  int i;
  for(i = 1; i < nargs; i++)
    if(remove(args[i]) == -1)
      printf("Couldn't remove %s\n", args[i]);
}
