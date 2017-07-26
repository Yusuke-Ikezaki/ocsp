#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  /* 整数値 */
  long int n;
  /* 双方向パイプ */
  int fd1[2], fd2[2];
  /* プロセスID */
  pid_t pid;

  /* 双方向パイプの作成 */
  if((pipe(fd1) < 0) || (pipe(fd2) < 0)){
    /* 作成失敗 */
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  /* フォーク */
  pid = fork();
  if(pid < 0){
    /* フォーク失敗 */
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if(pid == 0){
    /* 子プロセス */
    /* fd1の書き込みを閉じる */
    close(fd1[1]);
    /* fd2の読み込みを閉じる */
    close(fd2[0]);

    /* fd1からの読み込み */
    read(fd1[0], &n, sizeof(n));
    /* fd1の読み込みを閉じる */
    close(fd1[0]);

    /* 読み込んだ整数値の2乗を出力 */
    long int squared = n * n;
    printf("child : %d * %d = %d\n", n, n, squared);

    /* fd2への書き込み */
    write(fd2[1], &squared, sizeof(n));
    /* fd2の書き込みを閉じる */
    close(fd2[1]);
  } else{
    /* 親プロセス */
    /* fd1の読み込みを閉じる */
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
