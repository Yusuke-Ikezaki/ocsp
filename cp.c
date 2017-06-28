#include "command.h"

/* ファイルのコピー */
void cp(int nargs, char *args[]){
  /* 引数が多い場合 */
  if(nargs > 3){
    puts("Too many arguments"); return;
  }

  FILE *fpin,*fpout;
  char buf[BUFSIZE];

  /* コピー元ファイルを開く */
  fpin = fopen(args[1], "r");
  /* ファイルがない場合 */
  if(fpin == NULL){
    puts("No such file"); return;
  }

  /* コピー先ファイルを開く */
  fpout = fopen(args[2], "w");
  /* ファイルがない場合 */
  if(fpout == NULL){
    puts("No such file");
  }

  /* 内容のコピー */
  while(fgets(buf, BUFSIZE, fpin) != NULL){
    fputs(buf, fpout);
  }

  /* コピー元ファイルを閉じる */
  fclose(fpin);
  /* コピー先ファイルを閉じる */
  fclose(fpout);
}
