#include "command.h"

/* ファイルの内容を先頭の10行まで表示 */
void head(int nargs, char *args[]){
  /* 引数が多い場合 */
  if(nargs > 2){
    puts("Too many arguments"); return;
  }

  FILE *fp;
  char c;

  /* ファイルを開く */
  fp = fopen(args[1], "r");
  /* ファイルがない場合 */
  if(fp == NULL){
    puts("No such file"); return;
  }

  /* 内容を10行まで出力 */
  int cnt = 0;
  while((c = fgetc(fp)) != EOF && cnt < 10){
    if(c == '\n') cnt++;
    fputc(c, stdout);
  }

  /* ファイルを閉じる */
  fclose(fp);
}
