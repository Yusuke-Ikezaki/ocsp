#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int args, char *argv[]){
  /* lsの書き込み用ファイル */
  char *filename = "out.txt";
  /* プロセスID */
  pid_t pid;
  /* 子プロセスの状態 */
  int status;
  /* ファイルディスクリプタ */
  int fd;

  /* コマンドライン引数の確認 */
  if(args != 3){
    /* コマンド形式の間違い */
    perror("./lsgrep dir name");
    exit(EXIT_FAILURE);
  }

  /* フォーク */
  pid = fork();
  if(pid == 0){
    /* 子プロセス */
    /* filenameを開く */
    if((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1){
      /* オープン失敗 */
      perror("open failed");
      exit(EXIT_FAILURE);
    }

    /* 標準出力を閉じる */
    close(1);

    /* filenameを標準出力に割り当てる */
    if(dup(fd) != 1){
      /* 割り当て失敗 */
      perror("dup failed");
      close(fd);
      exit(EXIT_FAILURE);
    }

    /* ls -l dirの実行 */
    execlp("ls", "ls", "-l", argv[1], NULL);
  } else if(pid > 0){
    /* 親プロセス */
    /* 子プロセスを待つ */
    wait(&status);

    /* フォーク */
    pid = fork();
    if(pid == 0){
      /* 子プロセス */
      /* grep name filenameの実行 */
      execlp("grep", "grep", argv[2], filename, NULL);
    } else if(pid > 0){
      /* 親プロセス */
      /* 子プロセスを待つ */
      wait(&status);
    } else{
      /* フォーク失敗 */
      perror("fork");
      exit(EXIT_FAILURE);
    }
  } else{
    /* フォーク失敗 */
    perror("fork");
    exit(EXIT_FAILURE);
  }

  /* filenameの消去 */
  if(remove(filename) != 0){
    /* 消去失敗 */
    perror("remove");
    exit(EXIT_FAILURE);
  }
}
