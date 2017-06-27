#include "cp.h"

void cp(int nargs, char *args[]){
  FILE *fpin,*fpout;
  char buf[SIZE * 8];

  fpin = fopen(args[1], "r");
  if(fpin == NULL){
    perror(args[1]);
    exit(EXIT_FAILURE);
  }

  fpout = fopen(args[2], "w");
  if(fpout == NULL){
    perror(args[2]);
    exit(EXIT_FAILURE);
  }

  while(fgets(buf, SIZE * 8, fpin) != NULL){
    fputs(buf, fpout);
  }

  fclose(fpin);
  fclose(fpout);
}
