#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int args, char *argv[]){
  pid_t pid;
  int status;
  int fd[2];

  if(args != 3){
    perror("./lsgrep dir name");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if(pid == 0){
    execlp("ls", "ls", "-l", argv[1], NULL);
    execlp("grep", "grep", argv[2], NULL);
  } else if(pid > 0){
    wait(&status);
  } else{
    perror("fork");
    exit(EXIT_FAILURE);
  }
}
