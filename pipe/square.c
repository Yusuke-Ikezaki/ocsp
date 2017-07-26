#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
  /* 整数値 */
  int n;
  /* 整数値の2乗 */
  long int squared;
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

    /* 整数値をfd1から読み込む */
    read(fd1[0], &n, sizeof(n));
    /* fd1の読み込みを閉じる */
    close(fd1[0]);

    /* 読み込んだ整数値の2乗を出力 */
    squared = n * n;
    printf("child : %d * %d = %ld\n", n, n, squared);

    /* fd2への書き込み */
    write(fd2[1], &squared, sizeof(n));
    /* fd2の書き込みを閉じる */
    close(fd2[1]);
  } else{
    /* 親プロセス */
    /* fd1の読み込みを閉じる */
    close(fd1[0]);
    /* fd2の書き込みを閉じる */
    close(fd2[1]);

    /* 整数値の入力 */
    printf("Parent > ");
    scanf("%d", &n);

    /* 整数値をfd1へ書き込む */
    write(fd1[1], &n, sizeof(n));
    /* fd1の書き込みを閉じる */
    close(fd1[1]);

    /* 整数値の2乗をfd2から読み込む */
    read(fd2[0], &squared, sizeof(n));
    /* fd2の読み込みを閉じる */
    close(fd2[0]);

    /* 整数値の2乗を出力 */
    printf("parent : ans = %ld\n", squared);
  }

  return 0;
}
