#include "command.h"

/* 引数をそのまま出力 */
void echo(int nargs, char *args[]){
  /* 引数がない場合 */
  if(nargs == 1) return;

  int i;
  for(i = 1; i < nargs - 1; i++){
    printf("%s ", args[i]);
  }
  printf("%s\n", args[nargs - 1]);
}
