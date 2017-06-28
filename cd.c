#include "command.h"

/* ディレクトリの移動 */
void cd(int nargs, char *args[]){
  /* 引数が多い場合 */
  if(nargs > 2){
    puts("too many arguments"); return;
  }

  /* 作業ディレクトリの変更 */
  if(chdir(args[1]) == -1) puts("No such directory");
}
