#include "command.h"

/* カレントディレクトリまでのパスを表示 */
void pwd(int nargs){
  /* 引数が多い場合 */
  if(nargs > 1){
    puts("Too many arguments"); return;
  }

  /* パスの出力 */
  char pathname[PATHSIZE];
  getcwd(pathname, PATHSIZE);
  printf("%s\n", pathname);
}
