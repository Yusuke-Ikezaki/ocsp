#include "command.h"

/* リンクの作成 */
void ln(int nargs, char *args[]){
  int i;

  /* シンボリックリンク */
  if(strcmp(args[1], "-s") == 0){
    /* 引数が少ない場合 */
    if(nargs < 4){
      puts("Too few arguments"); return;
    }

    for(i = 3; i < nargs; i++)
      if(symlink(args[2], args[i]) == -1)
	printf("couldn't create link to %s\n", args[i]);
  }
  /* ハードリンク */
  else{
    /* 引数が少ない場合 */
    if(nargs < 3){
      puts("Too few arguments"); return;
    }

    for(i = 2; i < nargs; i++)
      if(link(args[1], args[i]) == -1)
	printf("couldn't create link to %s\n", args[i]);
  }
}
