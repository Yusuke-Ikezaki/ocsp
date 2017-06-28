#include "command.h"

//#define BUFSIZE 512

void cp(int nargs, char *args[]){
  FILE *fpin,*fpout;
  char buf[BUFSIZE];

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

  while(fgets(buf, BUFSIZE, fpin) != NULL){
    fputs(buf, fpout);
  }

  fclose(fpin);
  fclose(fpout);
}
