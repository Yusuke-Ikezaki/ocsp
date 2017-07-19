#include "command.h"

/* ファイル名の変更 */
void mv(int nargs, char *args[]){
  /* 引数が少ない場合 */
  if(nargs < 3){
    puts("Too few arguments"); return;
  }
  /* 引数が多い場合 */
  else if(nargs > 3){
    puts("Too many arguments"); return;
  }

  /* 名前の変更 */
  if(rename(args[1], args[2]) == -1)
    puts("Couldn't rename");
}
