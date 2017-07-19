#include "command.h"

/* ディレクトリの移動 */
void cd(int nargs, char *args[]){
  /* 引数がない場合 */
  if(nargs == 1){
    puts("There are no arguments"); return;
  }
  /* 引数が多い場合 */
  else if(nargs > 2){
    puts("Too many arguments"); return;
  }

  /* 作業ディレクトリの変更 */
  if(chdir(args[1]) == -1)
    puts("No such directory");
}
