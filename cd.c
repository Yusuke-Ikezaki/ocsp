#include "command.h"

void cd(int nargs, char *args[]){
  // カレントディレクトリ変更  
  chdir(args[1]);
}
