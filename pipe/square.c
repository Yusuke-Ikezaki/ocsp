#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  int n;
  int fd1[2], fd2[2];
  pid_t pid;

  if((pipe(fd1) < 0) || (pipe(fd2) < 0)){
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  pid = fork();
  if(pid < 0){
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if(pid == 0){
    close(fd1[1]);
    close(fd2[0]);
    read(fd1[0], &n, sizeof(n));
    close(fd1[0]);
    printf("child : %d * %d = %d\n", n, n, n * n);
    int squared = n * n;
    write(fd2[1], &squared, sizeof(n));
    close(fd2[1]);
  } else{
    close(fd1[0]);
    close(fd2[1]);
    printf("Parent > ");
    scanf("%d", &n);
    write(fd1[1], &n, sizeof(n));
    close(fd1[1]);
    read(fd2[0], &n, sizeof(n));
    close(fd2[0]);
    printf("parent : ans = %d\n", n);
  }

  return 0;
}
