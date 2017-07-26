#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFSIZE 64

int main(int args, char *argv[]){
  char str[] = "out.txt";
  pid_t pid;
  int status;
  int fd[2];

  if(args != 3){
    perror("./lsgrep dir name");
    exit(EXIT_FAILURE);
  }

  if(pipe(fd) < 0){
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if(pid == 0){
    close(fd[1]);
    read(fd[0], str, sizeof(str));
    close(fd[0]);
    execlp("grep", "grep", argv[2], str, NULL);
  } else if(pid > 0){
    close(fd[0]);
    if((fd[1] = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
      perror("open failed");
      exit(EXIT_FAILURE);
    }

    close(1);

    if(dup(fd[1]) != 1){
      perror("dup failed");
      close(fd[1]);
      exit(EXIT_FAILURE);
    }

    pid = fork();
    if(pid == 0)
      execlp("ls", "ls", "-l", argv[1], NULL);
    write(fd[1], str, sizeof(str));
    close(fd[1]);
    wait(&status);
  } else{
    perror("fork");
    exit(EXIT_FAILURE);
  }
}
