#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 32

int main(){
  pid_t pid;
  int status;
  char buf[BUFSIZE];

  while(1){
    printf("finger> ");
    fgets(buf, sizeof(char) * BUFSIZE, stdin);
    strtok(buf, "\n");
    if(strcmp(buf, "exit") == 0) break;
    
    pid = fork();
    if(pid < 0){
      perror("fork");
      exit(EXIT_FAILURE);
    }

    if(pid == 0){
      if(strcmp(buf, "\n") == 0) execlp("finger", "finger", NULL);
      else execlp("finger", "finger", buf, NULL);
    } else{
      wait(&status);
    }
  }
}
