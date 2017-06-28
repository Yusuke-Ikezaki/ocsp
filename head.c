#include "command.h"

void head(int nargs, char *args[]){
  FILE *fp;
  char c;

  fp = fopen(args[1], "r");
  if(fp == NULL){
    perror(args[1]);
    exit(EXIT_FAILURE);
  }

  int cnt = 0;
  while((c = fgetc(fp)) != EOF && cnt < 10){
    if(c == '\n') cnt++;
    fputc(c, stdout);
  }

  fclose(fp);
}
