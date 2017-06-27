#include "command.h"

void unknown(char *arg){
  /* 未知コマンドの対応 */
  printf("unknown command: %s\n", arg);
}
