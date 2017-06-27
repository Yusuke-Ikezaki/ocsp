#include "command.h"

void echo(int nargs, char *args[]){
  /* 引数をそのまま出力 */
  int i;
  for(i = 1; i < nargs; i++){
    printf("%s ", args[i]);
  }
  printf("\n");
}
