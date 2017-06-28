#include "command.h"

#define BUFSIZE 512 // バッファのサイズ

/* ファイルの内容を表示 */
void cat(int nargs, char *args[]){
  /* 引数が多い場合 */
  if(nargs > 2){
    puts("too many arguments"); return;
  }

  FILE *fp;
  char buf[BUFSIZE];

  /* ファイルを開く */
  fp = fopen(args[1], "r");
  /* ファイルがない場合 */
  if(fp == NULL){
    puts("No such file"); return;
  }

  /* 内容の出力 */
  while(fgets(buf, BUFSIZE, fp) != NULL){
    fputs(buf, stdout);
  }

  /* ファイルを閉じる */
  fclose(fp);
}
