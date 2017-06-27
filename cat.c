#include "command.h"

void cat(int nargs, char *args[]){
  FILE *fp;
  char buf[SIZE * 8];

  fp = fopen(args[1], "r");
  if(fp == NULL){
    perror(args[1]);
    exit(EXIT_FAILURE);
  }

  while(fgets(buf, SIZE * 8, fp) != NULL){
    fputs(buf, stdout);
  }

  fclose(fp);
}
